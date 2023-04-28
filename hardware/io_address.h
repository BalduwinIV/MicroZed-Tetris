#ifndef IO_ADDRESS_H
#define IO_ADDRESS_H

#include <stdint.h>

typedef struct {
    unsigned char *IO_MEM_BASE;
    unsigned char *LED_LINE;
    unsigned char *LED_RGB1;
    unsigned char *LED_RGB2;
    unsigned char *LED_RGB_DIRECT;
    unsigned char *KNOBS;
    unsigned char *KNOBS_DIRECT;
    unsigned char *LCD_MEM_BASE;
} phys_addr_t;

/* Maps addresses in memory and returns structure that contains them. */
phys_addr_t *init_io();

/* Returns red knobs value in range <0, 255> */
uint8_t get_red_knob_value(phys_addr_t *io);

/* Returns 1 if red knob is pressed, 0 otherwise */
uint8_t is_red_knob_pressed(phys_addr_t *io);

/* Returns green knobs value in range <0, 255> */
uint8_t get_green_knob_value(phys_addr_t *io);

/* Returns 1 if green knob is pressed, 0 otherwise */
uint8_t is_green_knob_pressed(phys_addr_t *io);

/* Returns blue knobs value in range <0, 255> */
uint8_t get_blue_knob_value(phys_addr_t *io);

/* Returns 1 if blue knob is pressed, 0 otherwise */
uint8_t is_blue_knob_pressed(phys_addr_t *io);

/* Sets 32-bit value to LED line. */
void set_led_line_value(phys_addr_t *io, uint32_t value);

/* Shows chosen color on LED RGB1. */
void set_led_rgb1_color(phys_addr_t *io, uint32_t color);

/* Shows chosen color on LED RGB2. */
void set_led_rgb2_color(phys_addr_t *io, uint32_t color);

/* Updates LCD display. */
void lcd_display(phys_addr_t *io, uint16_t **screen);

#endif
