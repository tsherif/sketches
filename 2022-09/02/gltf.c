#define SOGL_MAJOR_VERSION 4
#define SOGL_MAJOR_VERSION 4
#define SOGL_IMPLEMENTATION_WIN32
#define CREATE_OPENGL_WINDOW_IMPLEMENTATION
#define CGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define _USE_MATH_DEFINES
#include "../../lib/create-opengl-window.h"
#include "../../lib/simple-opengl-loader.h"
#include "../../lib/cgltf.h"
#include "../../lib/HandmadeMath.h"
#include "../../lib/utils.h"
#include "../../lib/windows-utils.h"
#include "../../lib/stb_image.h"

#include <stdio.h>
#include <math.h>

#define WIDTH 1024
#define HEIGHT 1024
#define MODEL_DIR "../../models/duck/glTF"

static LRESULT CALLBACK messageHandler(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CLOSE: {
            PostQuitMessage(0);
            return 0;
        } break;
    }

    return DefWindowProc(window, message, wParam, lParam);
}

int32_t WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int32_t showWindow) {
    
    CreateOpenGLWindowArgs args = { 0 };
    args.title = "GLTF Demo"; 
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
    cgltf_options options = { 0 };
    cgltf_data* gltf = NULL;

    snprintf(filePath, 1024, "%s/Duck.gltf", MODEL_DIR);
    
    if (cgltf_parse_file(& (cgltf_options) { 0 }, filePath, &gltf) != cgltf_result_success) {
        OutputDebugStringA("Failed to load model.\n");
        return 1;
    }

    Buffer bufferData = { 0 };
    snprintf(filePath, 1024, "%s/%s", MODEL_DIR, gltf->buffers[0].uri);
    loadBinFile(filePath, &bufferData);

    int32_t imageWidth, imageHeight, imageChannels;
    snprintf(filePath, 1024, "%s/%s", MODEL_DIR, gltf->images[0].uri);    
    uint8_t *imageData = stbi_load(filePath, &imageWidth, &imageHeight, &imageChannels, 0);
    
    cgltf_primitive* primitive = gltf->meshes[0].primitives;
    cgltf_accessor* indices = primitive->indices;

    int32_t indexOffset = (int32_t) (indices->offset + indices->buffer_view->offset);
    int32_t elementCount = (int32_t) indices->count; 
    int32_t indexByteLength = (int32_t) (elementCount * sizeof(uint16_t));

    int32_t positionOffset = 0; 
    int32_t positionByteLength = 0;
    int32_t normalOffset = 0; 
    int32_t normalByteLength = 0; 
    int32_t uvOffset = 0; 
    int32_t uvByteLength = 0; 

    for (int32_t i = 0; i < primitive->attributes_count; ++i) {
        cgltf_attribute* attribute = primitive->attributes + i;

        if (strEquals(attribute->name, "POSITION", sizeof("POSITION"))) {
            positionOffset = (int32_t) (attribute->data->offset + attribute->data->buffer_view->offset); 
            positionByteLength = (int32_t) (attribute->data->count * attribute->data->stride);
        } else if (strEquals(attribute->name, "NORMAL", sizeof("NORMAL"))) {
            normalOffset = (int32_t) (attribute->data->offset + attribute->data->buffer_view->offset); 
            normalByteLength = (int32_t) (attribute->data->count * attribute->data->stride);
        } else if (strEquals(attribute->name, "TEXCOORD_0", sizeof("TEXCOORD_0"))) {
            uvOffset = (int32_t) (attribute->data->offset + attribute->data->buffer_view->offset); 
            uvByteLength = (int32_t) (attribute->data->count * attribute->data->stride);
        }
    }

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbos[4] = { 0 };
    glGenBuffers(4, vbos);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexByteLength, bufferData.data + indexOffset, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
    glBufferData(GL_ARRAY_BUFFER, positionByteLength, bufferData.data + positionOffset, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbos[2]);
    glBufferData(GL_ARRAY_BUFFER, normalByteLength, bufferData.data + normalOffset, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vbos[3]);
    glBufferData(GL_ARRAY_BUFFER, uvByteLength, bufferData.data + uvOffset, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(2);

    GLuint texture = 0;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

    const char* vsSource =
    "#version 440\n"
    "layout(std140, column_major) uniform;\n"
    "layout(location=0) in vec4 position;\n"
    "layout(location=1) in vec3 normal;\n"
    "layout(location=2) in vec2 uv;\n"
    "uniform SceneUniforms {\n"
    "    mat4 viewProj;\n"
    "    vec4 eyePosition;\n"
    "    vec4 lightPosition;\n"
    "} uScene;\n"       
    "out  vec3 vPosition;\n"
    "out  vec2 vUV;\n"
    "out  vec3 vNormal;\n"
    "void main() {\n"
    "    vec4 worldPosition = vec4(position.xyz * 0.01, 1.0);\n"
    "    vPosition = position.xyz;\n"
    "    vUV = uv;\n"
    "    vNormal = normal;\n"
    "    gl_Position = uScene.viewProj * worldPosition;\n"
    "}\n";

    const char* fsSource = 
    "#version 440\n"
    "layout(std140, column_major) uniform;\n"
    "uniform SceneUniforms {\n"
    "    mat4 viewProj;\n"
    "    vec4 eyePosition;\n"
    "    vec4 lightPosition;\n"
    "} uScene;\n"
    "uniform sampler2D tex;\n"
    "in vec3 vPosition;\n"
    "in vec2 vUV;\n"
    "in vec3 vNormal;\n"
    "out vec4 fragColor;\n"
    "void main() {\n"
    "    vec3 color = texture(tex, vUV).rgb;\n"
    "    vec3 normal = normalize(vNormal);\n"
    "    vec3 eyeVec = normalize(uScene.eyePosition.xyz - vPosition);\n"
    "    vec3 incidentVec = normalize(vPosition - uScene.lightPosition.xyz);\n"
    "    vec3 lightVec = -incidentVec;\n"
    "    float diffuse = max(dot(lightVec, normal), 0.0);\n"
    "    float highlight = pow(max(dot(eyeVec, reflect(incidentVec, normal)), 0.0), 100.0);\n"
    "    float ambient = 0.1;\n"
    "    fragColor = vec4(color * (diffuse + highlight + ambient), 1.0);\n"
    "}\n";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vsSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fsSource, NULL);
    glCompileShader(fragmentShader);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);

    if (result != GL_TRUE) {
        OutputDebugStringA("Program failed to link!\n");
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
        char errorLog[1024];
        if (result != GL_TRUE) {
            OutputDebugStringA("Vertex shader failed to compile!\n");
            glGetShaderInfoLog(vertexShader, 1024, NULL, errorLog);
            OutputDebugStringA(errorLog);
        }
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
        if (result != GL_TRUE) {
            OutputDebugStringA("Fragment shader failed to compile!\n");
            glGetShaderInfoLog(fragmentShader, 1024, NULL, errorLog);
            OutputDebugStringA(errorLog);
        }

        return 1;
    }

    glUseProgram(program);

    hmm_mat4 projMatrix = HMM_Perspective((float) M_PI / 3.0f, (float) WIDTH / HEIGHT, 10.0f, 1000.0f);

    hmm_vec3 eyePosition = { 100.0f, 50.0f, 40.0f };
    hmm_vec3 eyeTarget = { 0.0f, 0.7f, 0.0f };
    hmm_vec3 eyeUp = { 0.0f, 1.0f, 0.0f };
    hmm_mat4 viewMatrix = HMM_LookAt(eyePosition, eyeTarget, eyeUp);

    hmm_mat4 viewProjMatrix = HMM_MultiplyMat4(projMatrix, viewMatrix);

    hmm_vec3 lightPosition = { 200.0f, 200.0f, -100.0f };

    float sceneUniformData[24] = { 0 };
    memcpy(sceneUniformData, &viewProjMatrix, sizeof(viewProjMatrix));
    memcpy(sceneUniformData + 16, &eyePosition, sizeof(eyePosition));
    memcpy(sceneUniformData + 20, &lightPosition, sizeof(lightPosition));

    GLuint sceneUniformBuffer = 0;
    glGenBuffers(1, &sceneUniformBuffer);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, sceneUniformBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(sceneUniformData), sceneUniformData, GL_STATIC_DRAW);

    GLuint texLocation = glGetUniformLocation(program, "tex");
    glUniform1i(texLocation, 0);

    ShowWindow(window, showWindow);
    HDC deviceContext = GetDC(window);
    MSG message = { 0 };

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
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

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_SHORT, NULL);

        SwapBuffers(deviceContext);            
    }

    return 0;
}



