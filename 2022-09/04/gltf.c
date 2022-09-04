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
#include "../../lib/gl-utils.h"
#include "../../lib/gltf-utils.h"
#include "../../lib/stb_image.h"
#include "../../lib/HandmadeMath.h"
#include "../../lib/utils.h"
#include "../../lib/windows-utils.h"

#include <windowsx.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 1024
#define HEIGHT 1024
#define MODEL_DIR "../../models/duck/glTF"

struct {
    int32_t x;
    int32_t y;
    int32_t lastX;
    int32_t lastY;
    bool buttonDown;
} mouse = {
    .lastX = -1,
    .lastY = -1
};

#define ORBIT_SCALE 0.1f

static LRESULT CALLBACK messageHandler(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_MBUTTONDOWN: 
        case WM_MBUTTONUP:
        case WM_MOUSEMOVE: {
            mouse.x = GET_X_LPARAM(lParam); 
            mouse.y = GET_Y_LPARAM(lParam); 
            mouse.buttonDown = (wParam & MK_LBUTTON) != 0;
            return 0;
        } break;
        case WM_CLOSE: {
            PostQuitMessage(0);
            return 0;
        } break;
    }

    return DefWindowProc(window, message, wParam, lParam);
}

static hmm_mat4 cameraRotation;
void orbitCamera(hmm_vec3* pEye, hmm_vec3* pLook, hmm_vec3* pUp, float x, float y) {
    hmm_vec3 eye = *pEye;
    hmm_vec3 look = *pLook;
    hmm_vec3 up = *pUp;

    eye = HMM_SubtractVec3(eye, look);
    hmm_vec3 axis = HMM_Cross(up, eye);
    axis = HMM_NormalizeVec3(axis);
    up = HMM_Cross(eye, axis);
    up = HMM_NormalizeVec3(up);

    // HMM_Rotate
    hmm_mat4 xRotation = HMM_Rotate(x, up);
    hmm_mat4 yRotation = HMM_Rotate(y, axis);
    hmm_mat4 rotation = HMM_MultiplyMat4(xRotation, yRotation);

    hmm_vec4 hEye = HMM_Vec4v(eye, 1.0f);
    hEye = HMM_MultiplyMat4ByVec4(rotation, hEye);
    eye = HMM_AddVec3(hEye.XYZ, look);

    *pEye = eye;
    *pLook = look;
    *pUp = up;
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
    cgltf_data* gltf_data = NULL;

    snprintf(filePath, 1024, "%s/Duck.gltf", MODEL_DIR);
    
    if (cgltf_parse_file(& (cgltf_options) { 0 }, filePath, &gltf_data) != cgltf_result_success) {
        OutputDebugStringA("Failed to load model.\n");
        return 1;
    }

    Buffer bufferData = { 0 };
    snprintf(filePath, 1024, "%s/%s", MODEL_DIR, gltf_data->buffers[0].uri);
    loadBinFile(filePath, &bufferData);

    int32_t imageWidth, imageHeight, imageChannels;
    snprintf(filePath, 1024, "%s/%s", MODEL_DIR, gltf_data->images[0].uri);    
    uint8_t *imageData = stbi_load(filePath, &imageWidth, &imageHeight, &imageChannels, 0);

    GLTF gltf = { 0 };
    parseGLTF(gltf_data, &bufferData, &gltf);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbos[4] = { 0 };
    glGenBuffers(4, vbos);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, gltf.indicesByteLength, gltf.indices, GL_STATIC_DRAW);

    attributeBufferData(& (AttributeBufferDataOpts) {
        .vbo = vbos[1],
        .attributeIndex = 0,
        .data = gltf.positions,
        .dataByteLength = gltf.positionsByteLength,
        .type = GL_FLOAT,
        .vectorSize = 3
    });

    attributeBufferData(& (AttributeBufferDataOpts) {
        .vbo = vbos[2],
        .attributeIndex = 1,
        .data = gltf.normals,
        .dataByteLength = gltf.normalsByteLength,
        .type = GL_FLOAT,
        .vectorSize = 3
    });

    attributeBufferData(& (AttributeBufferDataOpts) {
        .vbo = vbos[3],
        .attributeIndex = 2,
        .data = gltf.uvs,
        .dataByteLength = gltf.uvsByteLength,
        .type = GL_FLOAT,
        .vectorSize = 2
    });

    GLuint texture = 0;
    glGenTextures(1, &texture);

    textureData2D(& (TextureData2DOpts) {
        .texture = texture,
        .textureIndex = 0,
        .data = imageData,
        .width = imageWidth,
        .height = imageHeight,
        .format = GL_RGB,
        .type = GL_UNSIGNED_BYTE
    });

    const char* vsSource =
    "#version 440\n"
    "layout(std140, column_major) uniform;\n"
    "layout(location=0) in vec4 position;\n"
    "layout(location=1) in vec3 normal;\n"
    "layout(location=2) in vec2 uv;\n"
    "layout(std140, column_major) uniform SceneUniforms {\n"
    "    mat4 proj;\n"
    "    vec4 eyePosition;\n"
    "    vec4 lightPosition;\n"
    "};\n"       
    "uniform mat4 view;\n"
    "out  vec3 vPosition;\n"
    "out  vec2 vUV;\n"
    "out  vec3 vNormal;\n"
    "void main() {\n"
    "    vec4 worldPosition = vec4(position.xyz * 0.01, 1.0);\n"
    "    vPosition = position.xyz;\n"
    "    vUV = uv;\n"
    "    vNormal = normal;\n"
    "    gl_Position = proj * view * worldPosition;\n"
    "}\n";

    const char* fsSource = 
    "#version 440\n"
    "layout(std140, column_major) uniform SceneUniforms {\n"
    "    mat4 proj;\n"
    "    vec4 eyePosition;\n"
    "    vec4 lightPosition;\n"
    "};\n"
    "uniform sampler2D tex;\n"
    "in vec3 vPosition;\n"
    "in vec2 vUV;\n"
    "in vec3 vNormal;\n"
    "out vec4 fragColor;\n"
    "void main() {\n"
    "    vec3 color = texture(tex, vUV).rgb;\n"
    "    vec3 normal = normalize(vNormal);\n"
    "    vec3 eyeVec = normalize(eyePosition.xyz - vPosition);\n"
    "    vec3 incidentVec = normalize(vPosition - lightPosition.xyz);\n"
    "    vec3 lightVec = -incidentVec;\n"
    "    float diffuse = max(dot(lightVec, normal), 0.0);\n"
    "    float highlight = pow(max(dot(eyeVec, reflect(incidentVec, normal)), 0.0), 100.0);\n"
    "    float ambient = 0.1;\n"
    "    fragColor = vec4(color * (diffuse + highlight + ambient), 1.0);\n"
    "}\n";

    GLuint program = createProgram(vsSource, fsSource, OutputDebugStringA);

    if (!program) {
        return 1;
    }

    glUseProgram(program);

    hmm_mat4 projMatrix = HMM_Perspective((float) M_PI / 3.0f, (float) WIDTH / HEIGHT, 10.0f, 1000.0f);

    hmm_vec3 eyePosition = { 100.0f, 50.0f, 40.0f };
    hmm_vec3 eyeTarget = { 0.0f, 0.7f, 0.0f };
    hmm_vec3 eyeUp = { 0.0f, 1.0f, 0.0f };
    hmm_mat4 viewMatrix = HMM_LookAt(eyePosition, eyeTarget, eyeUp);

    hmm_vec3 lightPosition = { 200.0f, 200.0f, -100.0f };

    float sceneUniformData[24] = { 0 };
    memcpy(sceneUniformData, &projMatrix, sizeof(projMatrix));
    memcpy(sceneUniformData + 16, &eyePosition, sizeof(eyePosition));
    memcpy(sceneUniformData + 20, &lightPosition, sizeof(lightPosition));

    GLuint sceneUniformBuffer = 0;
    glGenBuffers(1, &sceneUniformBuffer);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, sceneUniformBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(sceneUniformData), sceneUniformData, GL_STATIC_DRAW);

    GLuint viewLocation = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, (const GLfloat *) &viewMatrix);

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

        if (mouse.buttonDown) {
            int32_t lastX = mouse.lastX > -1 ? mouse.lastX : mouse.x;
            int32_t lastY = mouse.lastY > -1 ? mouse.lastY : mouse.y;
            float dx = (lastX - mouse.x) * ORBIT_SCALE;
            float dy = (lastY - mouse.y) * ORBIT_SCALE;

            orbitCamera(&eyePosition, &eyeTarget, &eyeUp, dx, dy);
            viewMatrix = HMM_LookAt(eyePosition, eyeTarget, eyeUp);
            glUniformMatrix4fv(viewLocation, 1, GL_FALSE, (const GLfloat *) &viewMatrix);
            
            mouse.lastX = mouse.x;
            mouse.lastY = mouse.y;
        } else {
            mouse.lastX = -1;
            mouse.lastY = -1;
        }
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, gltf.elementCount, GL_UNSIGNED_SHORT, NULL);

        SwapBuffers(deviceContext);            
    }

    return 0;
}



