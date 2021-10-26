#ifndef LINUX_UTILS
#define LINUX_UTILS

#include <fcntl.h>
#include <stdint.h>
#include <stdbool.h>
#include "utils.h"

void debugLog(const char* message) {
    int32_t length = 0;
    while(message[length]) {
        ++length;
    }

    write(STDERR_FILENO, message, length);
    write(STDERR_FILENO, "\n", 1);
}

bool loadBinFile(const char* fileName, Buffer* buffer) {
    int32_t fd = open(fileName, O_RDONLY);

    if (fd == -1) {
        debugLog("loadBinFile: Unable to open file.");
        return false;
    }

    int32_t size = lseek(fd, 0, SEEK_END);

    if (size == -1) {
        debugLog("loadBinFile: Unable to get file size.");
        return false;  
    }

    if (lseek(fd, 0, SEEK_SET) == -1) {
        debugLog("loadBinFile: Unable to reset file cursor.");
        return false;  
    }

    uint8_t* data = (uint8_t*) malloc(size);

    if (!data) {
        debugLog("loadBinFile: Unable to allocate data.");
        return false;  
    }

    if (read(fd, data, size) == -1) {
        debugLog("loadBinFile: Unable to read data.");
        free(data);
        return false; 
    }

    buffer->data = data;
    buffer->size = size;

    return true;
}

#endif
