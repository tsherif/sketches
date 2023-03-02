#define SOGL_IMPLEMENTATION_WIN32
#define CREATE_OPENGL_WINDOW_IMPLEMENTATION
#define CGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define _USE_MATH_DEFINES
#include "../../lib/c/create-opengl-window.h"
#include "../../lib/c/simple-opengl-loader.h"
#include "../../lib/c/cgltf.h"
#include "../../lib/c/HandmadeMath.h"
#include "../../lib/c/gl-utils.h"
#include "../../lib/c/gltf-utils.h"
#include "../../lib/c/stb_image.h"
#include "../../lib/c/utils.h"
#include "../../lib/c/windows-utils.h"
#include "../../lib/c/camera.h"

#include "../../lib/gl-utils/cpp/buffer.h"
#include "../../lib/gl-utils/cpp/program.h"
#include "../../lib/gl-utils/cpp/vertex-array.h"
#include "../../lib/gl-utils/cpp/renderable.h"

#include <windowsx.h>
#include <vector>
#include <map>
#include <string>
#include <array>

#define WIDTH 1024
#define HEIGHT 1024

struct {
    float x;
    float y;
    float lastX = -1.0f;
    float lastY = -1.0f;
    float wheelDelta;
    bool leftButtonDown;
    bool rightButtonDown;
} mouse;

struct GL_Buffers {
    GLuint vao;
    GLuint indexBuffer;
    GLuint positionBuffer;
    GLuint normalBuffer;
    GLuint tangentBuffer;
    GLuint uvBuffer;
};

struct Object {
    GLTF_Mesh mesh;
    Renderable renderable;
    hmm_mat4 transform;
};

const std::string MODEL_DIR("../../models/antique-camera/glTF");

#define ORBIT_SCALE 0.1f
#define PAN_SCALE 0.01f
#define ZOOM_SCALE 1.0f

std::vector<Object> objects;
std::map<uint32_t, GLuint> textures;

static LRESULT CALLBACK messageHandler(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_MBUTTONDOWN: 
        case WM_MBUTTONUP:
        case WM_MOUSEMOVE: {
            mouse.x = (float) GET_X_LPARAM(lParam); 
            mouse.y = (float) GET_Y_LPARAM(lParam); 
            mouse.leftButtonDown = (wParam & MK_LBUTTON) != 0;
            mouse.rightButtonDown = (wParam & MK_RBUTTON) != 0;
            return 0;
        } break;
        case WM_MOUSEWHEEL: {
            mouse.wheelDelta = (float) GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
        } break;
        case WM_CLOSE: {
            PostQuitMessage(0);
            return 0;
        } break;
    }

    return DefWindowProc(window, message, wParam, lParam);
}

VertexArray createVertexArray(Object& object) {
    
    Buffer positionBuffer = Buffer()
        .init()
        .data(object.mesh.positions, object.mesh.vec3ArrayByteLength);

    Buffer normalBuffer = Buffer()
        .init()
        .data(object.mesh.normals, object.mesh.vec3ArrayByteLength);

    Buffer tangentBuffer = Buffer()
        .init()
        .data(object.mesh.tangents, object.mesh.vec3ArrayByteLength);

    Buffer uvBuffer = Buffer()
        .init()
        .data(object.mesh.uvs, object.mesh.vec2ArrayByteLength);
    
    Buffer indexBuffer = Buffer()
        .init(GL_ELEMENT_ARRAY_BUFFER)
        .data(object.mesh.indices, object.mesh.indicesByteLength);
    
    
    return VertexArray()
        .init()
        .vertexBuffer(0, positionBuffer, GL_FLOAT, 3)
        .vertexBuffer(1, normalBuffer, GL_FLOAT, 3)
        .vertexBuffer(2, tangentBuffer, GL_FLOAT, 3)
        .vertexBuffer(3, uvBuffer, GL_FLOAT, 2)
        .indexBuffer(indexBuffer, GL_UNSIGNED_SHORT);
}

GLuint createTexture(const char* filePath, bool srgb) {
    int32_t width, height, channels;
    uint8_t* data = stbi_load(filePath, &width, &height, &channels, 0);

    GLuint rgbFormat = srgb ? GL_SRGB8 : GL_RGB;
    GLuint rgbaFormat = srgb ? GL_SRGB8_ALPHA8 : GL_RGBA;

    GLuint texture = 0;
    glGenTextures(1, &texture);

    TextureData2DOpts opts = {};
    opts.texture = texture;
    opts.textureIndex = 0;
    opts.data = data;
    opts.width = width;
    opts.height = height;
    opts.format = channels == 3 ? GL_RGB : GL_RGBA;
    opts.internalFormat = channels == 3 ? rgbFormat : rgbaFormat;
    opts.type = GL_UNSIGNED_BYTE;
    textureData2D(&opts);

    stbi_image_free(data);

    return texture;
}

hmm_mat4 parseTransform(cgltf_node* node) {
    hmm_mat4 transform = HMM_Mat4d(1.0f);

    if (node->has_rotation) {
        hmm_mat4 rotation = HMM_QuaternionToMat4(
            HMM_Quaternion(node->rotation[0], node->rotation[1], node->rotation[2], node->rotation[3])
        );

        transform = HMM_MultiplyMat4(rotation, transform);
    }

    if (node->has_scale) {
        hmm_mat4 scale = HMM_Scale(
            HMM_Vec3(node->scale[0], node->scale[1], node->scale[2])
        );

        transform = HMM_MultiplyMat4(scale, transform);
    }

    if (node->has_translation) {
        hmm_mat4 translation = HMM_Translate(
            HMM_Vec3(node->translation[0], node->translation[1], node->translation[2])
        );

        transform = HMM_MultiplyMat4(translation, transform);
    }

    return transform;
}

int32_t WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int32_t showWindow) {
    
    CreateOpenGLWindowArgs args = { 0 };
    args.title = "PBR GLTF Demo"; 
    args.majorVersion = SOGL_MAJOR_VERSION; 
    args.minorVersion = SOGL_MINOR_VERSION;
    args.width = WIDTH;
    args.height = HEIGHT;
    args.winCallback = messageHandler;
    args.msaaSamples = 16;
    args.vsync = true;
    
    HWND window = createOpenGLWindow(&args);

    if (!sogl_loadOpenGL()) {
        OutputDebugStringA("The following OpenGL functions could not be loaded:\n");
        const char **failures = sogl_getFailures();
        while (*failures) {
            OutputDebugStringA(*failures);
            failures++;
        }
        OutputDebugStringA("Failed to load OpenGL functions.\n");
        return 1;
    }

    DataBuffer vsSource = { 0 };
    loadTextFile("pbr.vert", &vsSource);

    DataBuffer fsSource = { 0 };
    loadTextFile("pbr.frag", &fsSource);

    hmm_mat4 projMatrix = HMM_Perspective(60.0f, (float) WIDTH / HEIGHT, 1.0f, 100.0f);

    std::array<float, 3> light0 = { 5.0f,  10.0f, 5.0f };
    std::array<float, 3> light1 = { -5.0f,  10.0f, 5.0f };
    std::array<float, 3> light2 = { 5.0f, 10.0f, -5.0f };
    std::array<float, 3> light3 = { -5.0f, 10.0f, -5.0f };

    Program program = Program()
    .init(vsSource.cdata, fsSource.cdata, OutputDebugStringA);

    std::string filePath = MODEL_DIR + "/AntiqueCamera.gltf";
    cgltf_data* gltf_data = NULL;

    cgltf_options opts = {};
    if (cgltf_parse_file(&opts, filePath.c_str(), &gltf_data) != cgltf_result_success) {
        OutputDebugStringA("Failed to load model.\n");
        return 1;
    }

    DataBuffer bufferData = { 0 };
    filePath = MODEL_DIR + "/" + gltf_data->buffers[0].uri;
    loadBinFile(filePath.c_str(), &bufferData);

    for (int32_t i = 0; i < gltf_data->nodes_count; ++i) {
        cgltf_node* node = gltf_data->nodes + i;
        Object object =  {};

        parseGLTF(node->mesh, gltf_data->images, &bufferData, &object.mesh);
        object.transform = parseTransform(node);
        object.renderable
            .init(createVertexArray(object), program)
            .setMat4Uniform("proj", (const GLfloat *) &projMatrix)
            .setMat4Uniform("world", (const GLfloat *) &object.transform)
            .setVec3Uniform("lightPositions[0]", light0.data())
            .setVec3Uniform("lightPositions[1]", light1.data())
            .setVec3Uniform("lightPositions[2]", light2.data())
            .setVec3Uniform("lightPositions[3]", light3.data())
            .setIntUniform("colorMap", 0)
            .setIntUniform("normalMap", 1)
            .setIntUniform("metallicRoughnessMap", 2);

        int32_t colorTextureIndex = object.mesh.material.colorTexture;
        int32_t normalTextureIndex = object.mesh.material.normalTexture;
        int32_t metalicRoughnessTextureIndex = object.mesh.material.metallicRoughnessTexture;
        if (textures.count(colorTextureIndex) == 0) {
            filePath = MODEL_DIR + "/" + gltf_data->images[colorTextureIndex].uri;
            textures[colorTextureIndex] = createTexture(filePath.c_str(), true);
        }

        if (textures.count(normalTextureIndex) == 0) {
            filePath = MODEL_DIR + "/" + gltf_data->images[normalTextureIndex].uri;
            textures[normalTextureIndex] = createTexture(filePath.c_str(), false);
        }

        if (textures.count(metalicRoughnessTextureIndex) == 0) {
            filePath = MODEL_DIR + "/" + gltf_data->images[metalicRoughnessTextureIndex].uri;
            textures[metalicRoughnessTextureIndex] = createTexture(filePath.c_str(), false);
        }

        objects.push_back(object);
    }

    Camera camera = {};
    camera.position = { 0.0f, 4.0f, 15.0f };
    camera.target = { 0.0f, 4.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.minZoom = 2.0f;
    camera.maxZoom = 50.0f;
    camera_buildMatrix(&camera);

    ShowWindow(window, showWindow);
    HDC deviceContext = GetDC(window);
    MSG message = { 0 };

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    bool running = true;

    while (running) {
        while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessage(&message);

            if (message.message == WM_QUIT) {
                running = false; 
                break;
            }
        }

        if (mouse.leftButtonDown) {
            float lastX = mouse.lastX > -1.0f ? mouse.lastX : mouse.x;
            float lastY = mouse.lastY > -1.0f ? mouse.lastY : mouse.y;
            float dx = (lastX - mouse.x) * ORBIT_SCALE;
            float dy = (lastY - mouse.y) * ORBIT_SCALE;

            camera_orbit(&camera, dx, dy);
            
            mouse.lastX = mouse.x;
            mouse.lastY = mouse.y;
        } else if (mouse.rightButtonDown) {
            float lastX = mouse.lastX > -1.0f ? mouse.lastX : mouse.x;
            float lastY = mouse.lastY > -1.0f ? mouse.lastY : mouse.y;
            float dx = (lastX - mouse.x) * PAN_SCALE;
            float dy = (mouse.y - lastY) * PAN_SCALE;

            camera_pan(&camera, dx, dy);
            
            mouse.lastX = mouse.x;
            mouse.lastY = mouse.y;
        } else {
            mouse.lastX = -1.0f;
            mouse.lastY = -1.0f;
        }

        if (mouse.wheelDelta != 0.0f) {
            camera_zoom(&camera, -mouse.wheelDelta * ZOOM_SCALE);
            mouse.wheelDelta = 0.0f;
        }

        camera_buildMatrix(&camera);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        for (Object& object: objects) {
            GLuint colorTexture = textures[object.mesh.material.colorTexture];
            GLuint normalTexture = textures[object.mesh.material.normalTexture];
            GLuint metalicRoughnessTexture = textures[object.mesh.material.metallicRoughnessTexture];
            
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, colorTexture);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, normalTexture);
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, metalicRoughnessTexture);

            object.renderable
                .setMat4Uniform("view", (const GLfloat *) &camera.matrix)
                .setVec3Uniform("eyePosition", (const GLfloat *) &camera.position)
                .draw();
        }

        SwapBuffers(deviceContext);            
    }

    return 0;
}



