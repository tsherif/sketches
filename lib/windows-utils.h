#ifndef WINDOWS_UTILS
#define WINDOWS_UTILS

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdint.h>
#include <stdbool.h>
#include <malloc.h> 
#include "utils.h"

void debugLog(const char* message) {
    OutputDebugStringA(message);  
    OutputDebugStringA("\n"); 
}

static bool loadFile(const char* fileName, Buffer* buffer, bool nullTerminate) {
    HANDLE file = CreateFileA(
      fileName,
      GENERIC_READ,
      FILE_SHARE_READ,
      NULL,
      OPEN_EXISTING,
      FILE_ATTRIBUTE_NORMAL,
      NULL
    );

    uint8_t* data = 0;
    LARGE_INTEGER fileSize = { 0 }; 
    
    if (file == INVALID_HANDLE_VALUE) {        
        debugLog("Unable to open file.");
        goto ERROR_NO_RESOURCES;
    }

    if (!GetFileSizeEx(file, &fileSize)) {
        debugLog("Unable to get file size.");
        goto ERROR_FILE_OPENED;
    }


    if (fileSize.HighPart != 0) {
        debugLog("File too large!");
        goto ERROR_FILE_OPENED;
    }

    int32_t allocation = fileSize.LowPart;

    if (nullTerminate) {
        allocation += 1;
    }

    DWORD bytesRead = 0;
    data = (uint8_t*) malloc(allocation);

    if (!data) {
        debugLog("Unable to allocate data.");
        goto ERROR_FILE_OPENED;
    }

    if (!ReadFile(file, data, fileSize.LowPart, &bytesRead, NULL)) {
        debugLog("Unable to read data.");
        goto ERROR_DATA_ALLOCATED;
    }

    if (nullTerminate) {
        data[allocation - 1] = 0;
    }

    buffer->data = data;
    buffer->size = allocation;
    CloseHandle(file);

    /////////////
    // Success!
    /////////////

    return true;

    ///////////////////
    // Error handling
    ///////////////////

    ERROR_DATA_ALLOCATED:
    free(data);

    ERROR_FILE_OPENED:
    CloseHandle(file);
    
    ERROR_NO_RESOURCES:
    return false;
}

bool loadBinFile(const char* fileName, Buffer* buffer) {
    return loadFile(fileName, buffer, false);
}

bool loadTextFile(const char* fileName, Buffer* buffer) {
    return loadFile(fileName, buffer, true);
}

#endif