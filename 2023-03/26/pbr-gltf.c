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

#include <windowsx.h>
#include <stdio.h>
#include <math.h>

#include "../../lib/c/buffer.h"
#include "../../lib/c/vertex-array.h"
#include "../../lib/c/program.h"
#include "../../lib/c/pipeline.h"

#define WIDTH 1024
#define HEIGHT 1024
#define MODEL_DIR "../../models/antique-camera/glTF"

struct {
    float x;
    float y;
    float lastX;
    float lastY;
    float wheelDelta;
    bool leftButtonDown;
    bool rightButtonDown;
} mouse = {
    .lastX = -1.0f,
    .lastY = -1.0f
};

typedef struct {
    GLTF_Mesh mesh;
    Pipeline pipeline;
    hmm_mat4 transform;
} Object;

#define TYPE Object
#define IMPLEMENTATION
#include "../../lib/c/vector.h"

#define TYPE VertexArray
#define IMPLEMENTATION
#include "../../lib/c/vector.h"

#define ORBIT_SCALE 0.1f
#define PAN_SCALE 0.01f
#define ZOOM_SCALE 1.0f
#define MAX_OBJECTS 64
#define MAX_TEXTURES 128

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

void initVertexArray(GLTF_Mesh* mesh, VertexArray* vao) {
    Buffer indexBuffer = Buffer_create(GL_ELEMENT_ARRAY_BUFFER);
    Buffer_data(&indexBuffer, mesh->indices, mesh->indicesByteLength);

    Buffer positionBuffer = Buffer_create(GL_ARRAY_BUFFER);
    Buffer_data(&positionBuffer, mesh->positions,  mesh->vec3ArrayByteLength);

    Buffer normalBuffer = Buffer_create(GL_ARRAY_BUFFER);
    Buffer_data(&normalBuffer, mesh->normals,  mesh->vec3ArrayByteLength);

    Buffer tangentBuffer = Buffer_create(GL_ARRAY_BUFFER);
    Buffer_data(&tangentBuffer, mesh->tangents,  mesh->vec3ArrayByteLength);

    Buffer uvBuffer = Buffer_create(GL_ARRAY_BUFFER);
    Buffer_data(&uvBuffer, mesh->uvs,  mesh->vec2ArrayByteLength);

    VertexArray_vertexBuffer(vao, &(VertexArray_VertexBufferOptions) {
        .index = 0,
        .buffer = &positionBuffer,
        .type = GL_FLOAT,
        .vecSize = 3
    });
    VertexArray_vertexBuffer(vao, &(VertexArray_VertexBufferOptions) {
        .index = 1,
        .buffer = &normalBuffer,
        .type = GL_FLOAT,
        .vecSize = 3
    });
    VertexArray_vertexBuffer(vao, &(VertexArray_VertexBufferOptions) {
        .index = 2,
        .buffer = &tangentBuffer,
        .type = GL_FLOAT,
        .vecSize = 3
    });
    VertexArray_vertexBuffer(vao, &(VertexArray_VertexBufferOptions) {
        .index = 3,
        .buffer = &uvBuffer,
        .type = GL_FLOAT,
        .vecSize = 2
    });

    VertexArray_indexBuffer(vao, &indexBuffer, GL_UNSIGNED_SHORT);
}

GLuint createTexture(const char* filePath, bool srgb) {
    int32_t width, height, channels;
    uint8_t* data = stbi_load(filePath, &width, &height, &channels, 0);

    GLuint rgbFormat = srgb ? GL_SRGB8 : GL_RGB;
    GLuint rgbaFormat = srgb ? GL_SRGB8_ALPHA8 : GL_RGBA;

    GLuint texture = 0;
    glGenTextures(1, &texture);

    textureData2D(& (TextureData2DOpts) {
        .texture = texture,
        .textureIndex = 0,
        .data = data,
        .width = width,
        .height = height,
        .format = channels == 3 ? GL_RGB : GL_RGBA,
        .internalFormat = channels == 3 ? rgbFormat : rgbaFormat,
        .type = GL_UNSIGNED_BYTE
    });

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
    loadTextFile("vs.glsl", &vsSource);

    DataBuffer fsSource = { 0 };
    loadTextFile("fs.glsl", &fsSource);

    Program program = Program_create(& (Program_CreateOptions) {
        .vsSource = vsSource.cdata,
        .fsSource = fsSource.cdata,
        .logFn = OutputDebugStringA
    });

    if (!program.handle) {
        return 1;
    }

    uint32_t colorUnit = (uint32_t) Program_SamplerMap_get(&program.samplers, "colorMap");
    uint32_t normalUnit = (uint32_t) Program_SamplerMap_get(&program.samplers, "normalMap");
    uint32_t metallicRoughnessUnit = (uint32_t) Program_SamplerMap_get(&program.samplers, "metallicRoughnessMap");

    Vector_Object objects = Vector_Object_create();
    Vector_VertexArray vaos = Vector_VertexArray_create();
    GLuint textures[64] = { 0 };

    char filePath[1024] = { 0 };
    cgltf_data* gltf_data = NULL;

    snprintf(filePath, 1024, "%s/AntiqueCamera.gltf", MODEL_DIR);
    
    if (cgltf_parse_file(& (cgltf_options) { 0 }, filePath, &gltf_data) != cgltf_result_success) {
        OutputDebugStringA("Failed to load model.\n");
        return 1;
    }

    if (gltf_data->nodes_count > MAX_OBJECTS) {
        OutputDebugStringA("Too many nodes.\n");
        return 1;
    }

    if (gltf_data->images_count > MAX_TEXTURES) {
        OutputDebugStringA("Too many images.\n");
        return 1;
    }

    DataBuffer bufferData = { 0 };
    snprintf(filePath, 1024, "%s/%s", MODEL_DIR, gltf_data->buffers[0].uri);
    loadBinFile(filePath, &bufferData);


    for (int32_t i = 0; i < gltf_data->nodes_count; ++i) {
        Object object = { 0 };
        Vector_VertexArray_push(&vaos, VertexArray_create());
        VertexArray* vao = Vector_VertexArray_address(&vaos, i);
        cgltf_node* node = gltf_data->nodes + i;
        parseGLTF(node->mesh, gltf_data->images, &bufferData, &object.mesh);
        initVertexArray(&object.mesh, vao);
        object.pipeline = Pipeline_create(
            GL_TRIANGLES,
            vao,
            &program
        );
        object.transform = parseTransform(node);
        
        int32_t colorTextureIndex = object.mesh.material.colorTexture;
        int32_t normalTextureIndex = object.mesh.material.normalTexture;
        int32_t metalicRoughnessTextureIndex = object.mesh.material.metallicRoughnessTexture;
        if (!textures[colorTextureIndex]) {
            snprintf(filePath, 1024, "%s/%s", MODEL_DIR, gltf_data->images[colorTextureIndex].uri);
            textures[colorTextureIndex] = createTexture(filePath, true);
        }

        if (!textures[normalTextureIndex]) {
            snprintf(filePath, 1024, "%s/%s", MODEL_DIR, gltf_data->images[normalTextureIndex].uri);
            textures[normalTextureIndex] = createTexture(filePath, false);
        }

        if (!textures[metalicRoughnessTextureIndex]) {
            snprintf(filePath, 1024, "%s/%s", MODEL_DIR, gltf_data->images[metalicRoughnessTextureIndex].uri);
            textures[metalicRoughnessTextureIndex] = createTexture(filePath, false);
        }

        Vector_Object_push(&objects, object);
    }

    hmm_mat4 projMatrix = HMM_Perspective(60.0f, (float) WIDTH / HEIGHT, 1.0f, 100.0f);

    Camera camera = {
        .position = { 0.0f, 4.0f, 15.0f },
        .target = { 0.0f, 4.0f, 0.0f },
        .up = { 0.0f, 1.0f, 0.0f },
        .minZoom = 2.0f,
        .maxZoom = 50.0f
    };
    camera_buildMatrix(&camera);

    Program_setVecUniform(&program, "proj", &projMatrix);
    Program_setVecUniform(&program, "lightPosition1", (GLfloat[]) { 5.0f,  10.0f, 5.0f });
    Program_setVecUniform(&program, "lightPosition2", (GLfloat[]) { -5.0f,  10.0f, 5.0f });
    Program_setVecUniform(&program, "lightPosition3", (GLfloat[]) { 5.0f, 10.0f, -5.0f });
    Program_setVecUniform(&program, "lightPosition4", (GLfloat[]) { -5.0f, 10.0f, -5.0f });


    ShowWindow(window, showWindow);
    HDC deviceContext = GetDC(window);
    MSG message = { 0 };

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
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
        
        for (int32_t i = 0; i < Vector_Object_size(&objects); ++i) {
            Object object = Vector_Object_get(&objects, i);
            GLuint colorTexture = textures[object.mesh.material.colorTexture];
            GLuint normalTexture = textures[object.mesh.material.normalTexture];
            GLuint metalicRoughnessTexture = textures[object.mesh.material.metallicRoughnessTexture];

            glActiveTexture(GL_TEXTURE0 + colorUnit);
            glBindTexture(GL_TEXTURE_2D, colorTexture);
            glActiveTexture(GL_TEXTURE0 + normalUnit);
            glBindTexture(GL_TEXTURE_2D, normalTexture);
            glActiveTexture(GL_TEXTURE0 + metallicRoughnessUnit);
            glBindTexture(GL_TEXTURE_2D, metalicRoughnessTexture);

            Program_setVecUniform(object.pipeline.program, "view", &camera.matrix);
            Program_setVecUniform(object.pipeline.program, "eyePosition", &camera.position);
            Program_setVecUniform(object.pipeline.program, "world", &object.transform);
            Pipeline_draw(&object.pipeline);
        }

        SwapBuffers(deviceContext);            
    }

    return 0;
}



