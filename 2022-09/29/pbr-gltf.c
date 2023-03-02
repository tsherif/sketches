#define SOGL_MAJOR_VERSION 4
#define SOGL_MAJOR_VERSION 4
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
    GLuint vao;
    GLuint indexBuffer;
    GLuint positionBuffer;
    GLuint normalBuffer;
    GLuint tangentBuffer;
    GLuint uvBuffer;
} GL_Buffers;


typedef struct {
    GLTF_Mesh mesh;
    GL_Buffers buffers;
    hmm_mat4 transform;
} Object;

#define ORBIT_SCALE 0.1f
#define PAN_SCALE 0.01f
#define ZOOM_SCALE 1.0f
#define MAX_OBJECTS 64
#define MAX_TEXTURES 128

struct {
    GLuint textures[MAX_TEXTURES];
    int32_t count;
} textures;

struct {
    Object objects[MAX_OBJECTS];
    int32_t count;
} objects;

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

void initMeshBuffers(Object* object) {
    glGenVertexArrays(1, &object->buffers.vao);
    glBindVertexArray(object->buffers.vao);

    GLuint vbos[5] = { 0 };
    glGenBuffers(5, vbos);
    object->buffers.indexBuffer = vbos[0];
    object->buffers.positionBuffer = vbos[1];
    object->buffers.normalBuffer = vbos[2];
    object->buffers.tangentBuffer = vbos[3];
    object->buffers.uvBuffer = vbos[4];

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->buffers.indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, object->mesh.indicesByteLength, object->mesh.indices, GL_STATIC_DRAW);

    attributeBufferData(& (AttributeBufferDataOpts) {
        .vbo = object->buffers.positionBuffer,
        .attributeIndex = 0,
        .data = object->mesh.positions,
        .dataByteLength = object->mesh.positionsByteLength,
        .type = GL_FLOAT,
        .vectorSize = 3
    });

    attributeBufferData(& (AttributeBufferDataOpts) {
        .vbo = object->buffers.normalBuffer,
        .attributeIndex = 1,
        .data = object->mesh.normals,
        .dataByteLength = object->mesh.normalsByteLength,
        .type = GL_FLOAT,
        .vectorSize = 3
    });

    attributeBufferData(& (AttributeBufferDataOpts) {
        .vbo = object->buffers.tangentBuffer,
        .attributeIndex = 2,
        .data = object->mesh.tangents,
        .dataByteLength = object->mesh.tangentsByteLength,
        .type = GL_FLOAT,
        .vectorSize = 3
    });

    attributeBufferData(& (AttributeBufferDataOpts) {
        .vbo = object->buffers.uvBuffer,
        .attributeIndex = 3,
        .data = object->mesh.uvs,
        .dataByteLength = object->mesh.uvsByteLength,
        .type = GL_FLOAT,
        .vectorSize = 2
    });

    glBindVertexArray(0);
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

    Buffer bufferData = { 0 };
    snprintf(filePath, 1024, "%s/%s", MODEL_DIR, gltf_data->buffers[0].uri);
    loadBinFile(filePath, &bufferData);


    for (int32_t i = 0; i < gltf_data->nodes_count; ++i) {
        Object* object = objects.objects + i;
        cgltf_node* node = gltf_data->nodes + i;
        parseGLTF(node->mesh, gltf_data->images, &bufferData, &object->mesh);
        initMeshBuffers(object);
        object->transform = parseTransform(node);
        
        int32_t colorTextureIndex = object->mesh.material.colorTexture;
        int32_t normalTextureIndex = object->mesh.material.normalTexture;
        int32_t metalicRoughnessTextureIndex = object->mesh.material.metallicRoughnessTexture;
        if (!textures.textures[colorTextureIndex]) {
            snprintf(filePath, 1024, "%s/%s", MODEL_DIR, gltf_data->images[colorTextureIndex].uri);
            textures.textures[colorTextureIndex] = createTexture(filePath, true);
        }

        if (!textures.textures[normalTextureIndex]) {
            snprintf(filePath, 1024, "%s/%s", MODEL_DIR, gltf_data->images[normalTextureIndex].uri);
            textures.textures[normalTextureIndex] = createTexture(filePath, false);
        }

        if (!textures.textures[metalicRoughnessTextureIndex]) {
            snprintf(filePath, 1024, "%s/%s", MODEL_DIR, gltf_data->images[metalicRoughnessTextureIndex].uri);
            textures.textures[metalicRoughnessTextureIndex] = createTexture(filePath, false);
        }

        ++objects.count;
    }

    Buffer vsSource = { 0 };
    loadTextFile("vs.glsl", &vsSource);

    Buffer fsSource = { 0 };
    loadTextFile("fs.glsl", &fsSource);

    GLuint program = createProgram((const char *) vsSource.data, (const char *) fsSource.data, OutputDebugStringA);

    if (!program) {
        return 1;
    }

    glUseProgram(program);

    hmm_mat4 projMatrix = HMM_Perspective(60.0f, (float) WIDTH / HEIGHT, 1.0f, 100.0f);

    Camera camera = {
        .position = { 0.0f, 4.0f, 15.0f },
        .target = { 0.0f, 4.0f, 0.0f },
        .up = { 0.0f, 1.0f, 0.0f }
    };
    camera_buildMatrix(&camera);
    float zoom = HMM_LengthVec3(HMM_SubtractVec3(camera.position, camera.target));
    float minZoom = zoom * 0.1f;
    float maxZoom = zoom * 10.0f;

    GLuint projLocation = glGetUniformLocation(program, "proj");
    GLuint viewLocation = glGetUniformLocation(program, "view");
    GLuint worldLocation = glGetUniformLocation(program, "world");
    GLuint eyeLocation = glGetUniformLocation(program, "eyePosition");
    GLuint lightLocation0 = glGetUniformLocation(program, "lightPositions[0]");
    GLuint lightLocation1 = glGetUniformLocation(program, "lightPositions[1]");
    GLuint lightLocation2 = glGetUniformLocation(program, "lightPositions[2]");
    GLuint lightLocation3 = glGetUniformLocation(program, "lightPositions[3]");
    GLuint texLocation = glGetUniformLocation(program, "colorMap");
    GLuint nmLocation = glGetUniformLocation(program, "normalMap");
    GLuint mrmLocation = glGetUniformLocation(program, "metallicRoughnessMap");

    glUniformMatrix4fv(projLocation, 1, GL_FALSE, (const GLfloat *) &projMatrix);
    glUniform3f(lightLocation0, 5.0f,  10.0f, 5.0f);
    glUniform3f(lightLocation1, -5.0f,  10.0f, 5.0f);
    glUniform3f(lightLocation2, 5.0f, 10.0f, -5.0f);
    glUniform3f(lightLocation3, -5.0f, 10.0f, -5.0f);
    glUniform1i(texLocation, 0);
    glUniform1i(nmLocation, 1);
    glUniform1i(mrmLocation, 2);

    ShowWindow(window, showWindow);
    HDC deviceContext = GetDC(window);
    MSG message = { 0 };

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
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
            zoom -= mouse.wheelDelta * ZOOM_SCALE;

            if (zoom < minZoom) {
                zoom = minZoom;
            }

            if (zoom > maxZoom) {
                zoom = maxZoom;
            }

            camera_zoom(&camera, zoom);
        
            mouse.wheelDelta = 0.0f;
        }

        camera_buildMatrix(&camera);
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, (const GLfloat *) &camera.matrix);
        glUniform3fv(eyeLocation, 1, (const GLfloat *) &camera.position);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        for (int32_t i = 0; i < objects.count; ++i) {
            Object* object = objects.objects + i;
            GLuint colorTexture = textures.textures[object->mesh.material.colorTexture];
            GLuint normalTexture = textures.textures[object->mesh.material.normalTexture];
            GLuint metalicRoughnessTexture = textures.textures[object->mesh.material.metallicRoughnessTexture];

            glBindVertexArray(object->buffers.vao);
            
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, colorTexture);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, normalTexture);
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, metalicRoughnessTexture);

            glUniformMatrix4fv(worldLocation, 1, GL_FALSE, (const GLfloat *) &object->transform);
            glDrawElements(GL_TRIANGLES, object->mesh.elementCount, GL_UNSIGNED_SHORT, NULL);
        }

        SwapBuffers(deviceContext);            
    }

    return 0;
}



