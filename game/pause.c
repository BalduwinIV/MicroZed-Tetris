#include "pause.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../hardware/io_address.h"
#include "tools/font.h"
#include "tools/colors.h"
#include "graphics.h"

#define OPTIONS_NUM                 4
#define KNOB_DEAD_ZONE_VALUE        7
#define MAX_TEXT_WIDTH              245
#define TEXT_HEIGHT                 14
#define TEXT_PADDING_Y              6
#define TEXT_PADDING_X              20
#define MAX_VOLUME                  100

static int get_pause_position_x() {
    return 240 - ((TEXT_PADDING_X * 2 + MAX_TEXT_WIDTH) / 2);
}

static int get_pause_position_y() {
    return 160 - (OPTIONS_NUM * (TEXT_PADDING_Y * 2 + TEXT_HEIGHT) / 2);
}

unsigned char pause(unsigned short **screen, phys_addr_t *io, unsigned char *enable_audio, unsigned char *audio_volume) {
    int x = get_pause_position_x();
    int y = get_pause_position_y();

    draw_rect(screen, 0, 0, 479, 319, BLACK_RGB565);

    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 14 * 1000 * 1000};

    char audio_volume_str[6];

    int vote = 0;
    uint8_t green_knob_first_press = is_green_knob_pressed(io) ? 0 : 1;
    uint8_t green_knob_current_state_value = get_green_knob_value(io);
    uint8_t green_knob_previous_state_value = green_knob_current_state_value;
    uint8_t blue_knob_current_state_value = get_blue_knob_value(io);
    uint8_t blue_knob_previous_state_value = blue_knob_current_state_value;

    if (*audio_volume >= 96) {
        set_led_line_value(io, 0xffffffff);
    } else {
        set_led_line_value(io, 0xffffffff << (32 - (*audio_volume/3)));
    }

    if (*enable_audio) {
        set_led_rgb1_color(io, GREEN_RGB888);
        set_led_rgb2_color(io, GREEN_RGB888);
    } else {
        set_led_rgb1_color(io, RED_RGB888);
        set_led_rgb2_color(io, RED_RGB888);
    }

    while(1) {
        if (is_green_knob_pressed(io) && green_knob_first_press && (vote == CONTINUE || vote == GO_TO_MENU)) {
            green_knob_first_press = 0;
            break;
        }
        if (!green_knob_first_press && !is_green_knob_pressed(io)) {
            green_knob_first_press = 1;
        }

        /* Vote */
        green_knob_current_state_value = get_green_knob_value(io);
        if (green_knob_current_state_value - green_knob_previous_state_value > KNOB_DEAD_ZONE_VALUE) {
            if (green_knob_current_state_value - green_knob_previous_state_value < 4 * KNOB_DEAD_ZONE_VALUE) {
                vote--;
                if (vote < 0) {
                    vote = 0;
                }
            }
            green_knob_previous_state_value = green_knob_current_state_value;
        } else if (green_knob_current_state_value - green_knob_previous_state_value < -KNOB_DEAD_ZONE_VALUE) {
            if (green_knob_current_state_value - green_knob_previous_state_value > -(4 * KNOB_DEAD_ZONE_VALUE)) {
                vote++;
                if (vote >= OPTIONS_NUM) {
                    vote = OPTIONS_NUM-1;
                }
            }
            green_knob_previous_state_value = green_knob_current_state_value;
        }

        /* Paint background. */
        draw_rect(screen, x, y, x + 2 * TEXT_PADDING_X + MAX_TEXT_WIDTH, y + OPTIONS_NUM * (2 * TEXT_PADDING_Y + TEXT_HEIGHT), BLACK_RGB565);

        /* Draw rectangle with width: 20px + MAX_TEXT_WIDTH + 20px (20px is padding), and height: 6px + TEXT_HEIGHT + 6px (6px is padding). */
        /* Rectangles position depends on vote value. */
        draw_rect(screen, x, y + vote * (TEXT_HEIGHT + 2 * TEXT_PADDING_Y), x + 2 * TEXT_PADDING_X + MAX_TEXT_WIDTH, y + (vote + 1) * (TEXT_HEIGHT + 2 * TEXT_PADDING_Y), WHITE_RGB565);

        if (vote == CONTINUE) {
            draw_string(screen, x + TEXT_PADDING_X, y + TEXT_PADDING_Y, "CONTINUE", BLACK_RGB565, WHITE_RGB565);
        } else {
            draw_string(screen, x + TEXT_PADDING_X, y + TEXT_PADDING_Y, "CONTINUE", WHITE_RGB565, BLACK_RGB565);
        }

        if (vote == ENABLE_AUDIO) {
            if (is_green_knob_pressed(io) && green_knob_first_press) {
                green_knob_first_press = 0;
                if (*enable_audio) {
                    *enable_audio = 0;
                    set_led_rgb1_color(io, RED_RGB888);
                    set_led_rgb2_color(io, RED_RGB888);
                } else {
                    *enable_audio = 1;
                    set_led_rgb1_color(io, GREEN_RGB888);
                    set_led_rgb2_color(io, GREEN_RGB888);
                }
            }

            if (!green_knob_first_press && !is_green_knob_pressed(io)) {
                green_knob_first_press = 1;
            }
            draw_string(screen, x + TEXT_PADDING_X, y + 3 * TEXT_PADDING_Y + TEXT_HEIGHT, "ENABLE AUDIO", BLACK_RGB565, WHITE_RGB565);
        } else {
            draw_string(screen, x + TEXT_PADDING_X, y + 3 * TEXT_PADDING_Y + TEXT_HEIGHT, "ENABLE AUDIO", WHITE_RGB565, BLACK_RGB565);
        }
        draw_checkbox(screen, x + TEXT_PADDING_X + 210, y + 3 * TEXT_PADDING_Y + TEXT_HEIGHT + 2, *enable_audio);

        if (*audio_volume < 100) {
            audio_volume_str[0] = '<';
            audio_volume_str[1] = *audio_volume / 10 + '0';
            audio_volume_str[2] = *audio_volume % 10 + '0';
            audio_volume_str[3] = '>';
            audio_volume_str[4] = '\0';
        } else {
            audio_volume_str[0] = '<';
            audio_volume_str[1] = '1';
            audio_volume_str[2] = '0';
            audio_volume_str[3] = '0';
            audio_volume_str[4] = '>';
            audio_volume_str[5] = '\0';
        }
        if (vote == VOLUME_AUDIO) {
            if (is_green_knob_pressed(io) && green_knob_first_press) {
                green_knob_first_press = 0;
                set_audio_volume(io, *audio_volume);
            }

            if (!green_knob_first_press && !is_green_knob_pressed(io)) {
                green_knob_first_press = 1;
            }
            blue_knob_current_state_value = get_blue_knob_value(io);
            if (blue_knob_current_state_value - blue_knob_previous_state_value > KNOB_DEAD_ZONE_VALUE) {
                if (blue_knob_current_state_value - blue_knob_previous_state_value < 4 * KNOB_DEAD_ZONE_VALUE) {
                    (*audio_volume) -= 3;
                    if (*audio_volume > 100) {
                        *audio_volume = 0;
                    }
                }
                if (*audio_volume >= 96) {
                    set_led_line_value(io, 0xffffffff);
                } else {
                    set_led_line_value(io, 0xffffffff << (32 - (*audio_volume/3)));
                }
                set_audio_volume(io, *audio_volume);
                blue_knob_previous_state_value = blue_knob_current_state_value;
            } else if (blue_knob_current_state_value - blue_knob_previous_state_value < -KNOB_DEAD_ZONE_VALUE) {
                if (blue_knob_current_state_value - blue_knob_previous_state_value > -(4 * KNOB_DEAD_ZONE_VALUE)) {
                    (*audio_volume) += 3;
                    if (*audio_volume > MAX_VOLUME) {
                        *audio_volume = MAX_VOLUME;
                    }
                }
                if (*audio_volume >= 96) {
                    set_led_line_value(io, 0xffffffff);
                } else {
                    set_led_line_value(io, 0xffffffff << (32 - (*audio_volume/3)));
                }
                set_audio_volume(io, *audio_volume);
                blue_knob_previous_state_value = blue_knob_current_state_value;
            }
            draw_string(screen, x +TEXT_PADDING_X, y + 5 * TEXT_PADDING_Y + 2 * TEXT_HEIGHT, "VOLUME            ", BLACK_RGB565, WHITE_RGB565);
            if (*audio_volume < 100) {
                draw_string(screen, x + TEXT_PADDING_X + 189, y + 5 * TEXT_PADDING_Y + 2 * TEXT_HEIGHT, audio_volume_str, BLACK_RGB565, WHITE_RGB565);
            } else {
                draw_string(screen, x + TEXT_PADDING_X + 182, y + 5 * TEXT_PADDING_Y + 2 * TEXT_HEIGHT, audio_volume_str, BLACK_RGB565, WHITE_RGB565);
            }
        } else {
            draw_string(screen, x +TEXT_PADDING_X, y + 5 * TEXT_PADDING_Y + 2 * TEXT_HEIGHT, "VOLUME            ", WHITE_RGB565, BLACK_RGB565);
            if (*audio_volume < 100) {
                draw_string(screen, x + TEXT_PADDING_X + 189, y + 5 * TEXT_PADDING_Y + 2 * TEXT_HEIGHT, audio_volume_str, WHITE_RGB565, BLACK_RGB565);
            } else {
                draw_string(screen, x + TEXT_PADDING_X + 182, y + 5 * TEXT_PADDING_Y + 2 * TEXT_HEIGHT, audio_volume_str, WHITE_RGB565, BLACK_RGB565);
            }
        }

        if (vote == GO_TO_MENU) {
            draw_string(screen, x + TEXT_PADDING_X, y + 7 * TEXT_PADDING_Y + 3 * TEXT_HEIGHT, "GO TO MENU", BLACK_RGB565, WHITE_RGB565);
        } else {
            draw_string(screen, x + TEXT_PADDING_X, y + 7 * TEXT_PADDING_Y + 3 * TEXT_HEIGHT, "GO TO MENU", WHITE_RGB565, BLACK_RGB565);
        }

        lcd_display(io, screen);
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }

    return vote;
}
