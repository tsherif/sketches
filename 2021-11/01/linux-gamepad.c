#include <stdint.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdio.h>
#include <linux/input.h>
#include <errno.h>
#include <unistd.h>

bool testBit(uint8_t* bitField, int32_t bit) {
    int32_t byte = bit / 8;
    int32_t innerBit = bit % 8;

    return bitField[byte] & (1 << bit) != 0;
}

int32_t main() {
    int32_t gamepad = open("/dev/input/by-id/usb-_GAME_FOR_WINDOWS_1.02_4E12C2880000-event-joystick", O_RDONLY | O_NONBLOCK);

    if (gamepad == -1) {
        fprintf(stderr, "%s\n", "No gamepad found.");
        return 1;
    }

    char name[256] = { 0 };
    ioctl(gamepad, EVIOCGNAME(sizeof(name)), name);

    fprintf(stderr, "%s\n", name);

    uint8_t keyBits[(KEY_CNT + 7) / 8];
    ioctl(gamepad, EVIOCGBIT(EV_KEY, sizeof(keyBits)), keyBits);

    if (testBit(keyBits, BTN_GAMEPAD)) {
        fprintf(stderr, "It's a GAMEPAD!\n");
    }

    if (testBit(keyBits, BTN_A)) {
        fprintf(stderr, "Has A button!\n");
    }

    uint8_t absBits[(ABS_CNT + 7) / 8];
    ioctl(gamepad, EVIOCGBIT(EV_ABS, sizeof(absBits)), absBits);

    if (testBit(absBits, ABS_X)) {
        fprintf(stderr, "Has X axis!\n");
    }

    if (testBit(absBits, ABS_Y)) {
        fprintf(stderr, "Has Y axis!\n");
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
