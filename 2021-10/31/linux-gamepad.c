#include <stdint.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdio.h>
#include <linux/input.h>
#include <errno.h>
#include <unistd.h>

int32_t main() {
    int32_t gamepad = open("/dev/input/by-id/usb-_GAME_FOR_WINDOWS_1.02_4E12C2880000-event-joystick", O_RDONLY | O_NONBLOCK);

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
