#include <stdint.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdio.h>
#include <linux/input.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>

bool testBit(uint8_t* bitField, int32_t bit) {
    int32_t byte = bit / 8;
    int32_t innerBit = bit % 8;

    return bitField[byte] & (1 << bit) != 0;
}

bool endsWith(const char* s, const char* suffix) {
    const char* sp = s;
    int32_t sl = 0;
    const char* suffixP = suffix;
    int32_t suffixL = 0;

    while (*sp) {
        ++sp;
        ++sl;
    }

    while (*suffixP) {
        ++suffixP;
        ++suffixL;
    }

    if (sl < suffixL) {
        return false;
    }

    while (suffixL > 0) {
        if (*sp != *suffixP) {
            return false;
        }

        --sp;
        --suffixP;
        --suffixL;
    }

    return true;

}

char* concatStrings(char* dst, int32_t dstLen, const char* s1, const char* s2) {
    int32_t charsWritten = 0;
    while (*s1 && charsWritten < dstLen - 1) {
        dst[charsWritten] = *s1;
        ++s1;
        ++charsWritten;
    }

    while (*s2 && charsWritten < dstLen - 1) {
        dst[charsWritten] = *s2;
        ++s2;
        ++charsWritten;
    }

    dst[charsWritten] = '\0';

    return dst;
}

const char* INPUT_DIR = "/dev/input/by-id/";

int32_t main() {
    DIR* inputDir = opendir(INPUT_DIR);

    if (!inputDir) {
        fprintf(stderr, "Failed to open input dir\n");
        return 1;
    }


    int32_t gamepad = -1;
    struct dirent* entry = readdir(inputDir);

    while (entry) {
        if (endsWith(entry->d_name, "-event-joystick")) {
            char path[512];
            concatStrings(path, sizeof(path), INPUT_DIR,  entry->d_name);
            gamepad = open(path, O_RDONLY | O_NONBLOCK);

            uint8_t absBits[(ABS_CNT + 7) / 8];
            ioctl(gamepad, EVIOCGBIT(EV_ABS, sizeof(absBits)), absBits);

            uint8_t keyBits[(KEY_CNT + 7) / 8];
            ioctl(gamepad, EVIOCGBIT(EV_KEY, sizeof(keyBits)), keyBits);

            if (testBit(absBits, ABS_X) && testBit(absBits, ABS_Y) && testBit(keyBits, BTN_A)) {
                fprintf(stderr, "GAMEPAD checks out!!!!\n");
            } else {
                close(gamepad);
                gamepad = -1;
            }
        }
        entry = readdir(inputDir);
    }

    if (gamepad == -1) {
        fprintf(stderr, "%s\n", "No gamepad found.");
        return 1;
    }

    while (true) {
        struct input_event events[8];
        int32_t bytesRead = read(gamepad, events, sizeof(events));

        if (bytesRead < 0) {
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                continue;
            } else {
                fprintf(stderr, "%s\n", "Unexpected read error.");
                break; 
            }
        }

        int32_t numEvents = bytesRead / sizeof(struct input_event);

        for (int32_t i = 0; i < numEvents; ++i) {
            struct input_event* event = events + i;
            switch (event->type) {
                case EV_ABS: {
                    switch (event->code) {
                        case ABS_X: {
                            fprintf(stderr, "ABS_X: %d\n", event->value);
                        } break;
                        case ABS_Y: {
                            fprintf(stderr, "ABS_Y: %d\n", event->value);
                        } break;
                    }
                } break;
                case EV_KEY: {
                    switch (event->code) {
                        case BTN_A: {
                            fprintf(stderr, "BTN_A: %d\n", event->value);
                        } break;
                        case BTN_B: {
                            fprintf(stderr, "BTN_B: %d\n", event->value);
                        } break;
                        case BTN_X: {
                            fprintf(stderr, "BTN_X: %d\n", event->value);
                        } break;
                        case BTN_Y: {
                            fprintf(stderr, "BTN_Y: %d\n", event->value);
                        } break;
                    }
                } break;
            }
        }
    }
}
