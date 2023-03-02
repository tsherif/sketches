#define SOGL_MAJOR_VERSION 4
#define SOGL_MAJOR_VERSION 4
#define SOGL_IMPLEMENTATION_WIN32
#define CREATE_OPENGL_WINDOW_IMPLEMENTATION
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define _USE_MATH_DEFINES
#include "../../lib/c/create-opengl-window.h"
#include "../../lib/c/simple-opengl-loader.h"
#include "../../lib/c/tiny_gltf.h"
#include "../../lib/c/HandmadeMath.h"

#include <iostream>
#include <cmath>

#define WIDTH 1024
#define HEIGHT 1024

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

    tinygltf::Model model;
    tinygltf::TinyGLTF loader;
    std::string err;
    std::string warn;
    
    if (!loader.LoadASCIIFromFile(&model, &err, &warn, "../../models/duck/glTF/Duck.gltf")) {
        OutputDebugStringA("Failed to load model.\n");
        return 1;
    }

    tinygltf::Primitive& primitive = model.meshes[0].primitives[0];
    const std::vector<tinygltf::Accessor>& accessors = model.accessors;
    const std::vector<tinygltf::BufferView>& bufferViews = model.bufferViews;
    const tinygltf::Image& image = model.images[0];
    const tinygltf::Buffer& buffer = model.buffers[0];
    const uint8_t* bufferData = (uint8_t *) &buffer.data.front();

    const tinygltf::Accessor& indexAccessor = accessors[primitive.indices];
    const tinygltf::BufferView& indexBufferView = bufferViews[indexAccessor.bufferView];
    int32_t indexOffset = (int32_t) (indexAccessor.byteOffset + indexBufferView.byteOffset);
    int32_t indexByteLength = (int32_t) (indexAccessor.count * sizeof(uint16_t)); 
    int32_t elementCount = (int32_t) indexAccessor.count; 

    const tinygltf::Accessor& positionAccessor = accessors[primitive.attributes["POSITION"]];
    const tinygltf::BufferView& positionBufferView = bufferViews[positionAccessor.bufferView];
    int32_t positionOffset = (int32_t) (positionAccessor.byteOffset + positionBufferView.byteOffset);
    int32_t positionByteLength = (int32_t) (positionAccessor.count * 3 * sizeof(float)); 

    const tinygltf::Accessor& normalAccessor = accessors[primitive.attributes["NORMAL"]];
    const tinygltf::BufferView& normalBufferView = bufferViews[normalAccessor.bufferView];
    int32_t normalOffset = (int32_t) (normalAccessor.byteOffset + normalBufferView.byteOffset);
    int32_t normalByteLength = (int32_t) (normalAccessor.count * 3 * sizeof(float)); 

    const tinygltf::Accessor& uvAccessor = accessors[primitive.attributes["TEXCOORD_0"]];
    const tinygltf::BufferView& uvBufferView = bufferViews[uvAccessor.bufferView];
    int32_t uvOffset = (int32_t) (uvAccessor.byteOffset + uvBufferView.byteOffset);
    int32_t uvByteLength = (int32_t) (uvAccessor.count * 2 * sizeof(float));

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbos[4] = { 0 };
    glGenBuffers(4, vbos);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexByteLength, bufferData + indexOffset, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
    glBufferData(GL_ARRAY_BUFFER, positionByteLength, bufferData + positionOffset, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbos[2]);
    glBufferData(GL_ARRAY_BUFFER, normalByteLength, bufferData + normalOffset, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vbos[3]);
    glBufferData(GL_ARRAY_BUFFER, uvByteLength, bufferData + uvOffset, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(2);

    GLuint texture = 0;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image.image.front());
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

    const char* vsSource = R"GLSL(#version 440

    layout(std140, column_major) uniform;
    
    layout(location=0) in vec4 position;
    layout(location=1) in vec3 normal;
    layout(location=2) in vec2 uv;
    
    uniform SceneUniforms {
        mat4 viewProj;
        vec4 eyePosition;
        vec4 lightPosition;
    } uScene;       
    
    out  vec3 vPosition;
    out  vec2 vUV;
    out  vec3 vNormal;
    void main() {
        vec4 worldPosition = vec4(position.xyz * 0.01, 1.0);
        vPosition = position.xyz;
        vUV = uv;
        vNormal = normal;
        gl_Position = uScene.viewProj * worldPosition;
    }
    )GLSL";

    const char* fsSource = R"GLSL(#version 440

    layout(std140, column_major) uniform;

    uniform SceneUniforms {
        mat4 viewProj;
        vec4 eyePosition;
        vec4 lightPosition;
    } uScene;

    uniform sampler2D tex;
    
    in vec3 vPosition;
    in vec2 vUV;
    in vec3 vNormal;

    out vec4 fragColor;
    void main() {
        vec3 color = texture(tex, vUV).rgb;

        vec3 normal = normalize(vNormal);
        vec3 eyeVec = normalize(uScene.eyePosition.xyz - vPosition);
        vec3 incidentVec = normalize(vPosition - uScene.lightPosition.xyz);
        vec3 lightVec = -incidentVec;
        float diffuse = max(dot(lightVec, normal), 0.0);
        float highlight = pow(max(dot(eyeVec, reflect(incidentVec, normal)), 0.0), 100.0);
        float ambient = 0.1;

        fragColor = vec4(color * (diffuse + highlight + ambient), 1.0);
    }
    )GLSL";

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

    float sceneUniformData[24] = {};
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



