#define SOGL_MAJOR_VERSION 4
#define SOGL_MAJOR_VERSION 4
#define SOGL_IMPLEMENTATION_WIN32
#define CREATE_OPENGL_WINDOW_IMPLEMENTATION
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../lib/c/create-opengl-window.h"
#include "../../lib/c/simple-opengl-loader.h"
#include "../../lib/c/tiny_gltf.h"

#include <iostream>

static LRESULT CALLBACK messageHandler(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    return DefWindowProc(window, message, wParam, lParam);
}

int32_t WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int32_t showWindow) {
    
    CreateOpenGLWindowArgs args = { 0 };
    args.title = "GLTF Demo"; 
    args.majorVersion = SOGL_MAJOR_VERSION; 
    args.minorVersion = SOGL_MINOR_VERSION;
    args.width = 1024;
    args.height = 1024;
    args.winCallback = messageHandler;
    args.msaaSamples = 16;
    args.vsync = true;
    
    HWND window = createOpenGLWindow(&args);

    if (!sogl_loadOpenGL()) {
        std::cerr << "The following OpenGL functions could not be loaded:" << std::endl;
        const char **failures = sogl_getFailures();
        while (*failures) {
            std::cerr << *failures << std::endl;
            failures++;
        }
        std::cerr << "Failed to load OpenGL functions." << std::endl;
        return 1;
    }

    tinygltf::Model model;
    tinygltf::TinyGLTF loader;
    std::string err;
    std::string warn;
    
    if (!loader.LoadASCIIFromFile(&model, &err, &warn, "../../models/duck/glTF/Duck.gltf")) {
        std::cerr << "Failed to load model." << std::endl;
        std::cerr << "Error: " << err << std::endl;
        std::cerr << "Warning: " << warn << std::endl;
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

    ShowWindow(window, showWindow);
    HDC deviceContext = GetDC(window);
    MSG message = { 0 };

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

        glClear(GL_COLOR_BUFFER_BIT);

        SwapBuffers(deviceContext);            
    }

    return 0;
}



