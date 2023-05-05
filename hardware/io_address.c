#include "io_address.h"

#include <stdlib.h>
#include <stdio.h>

#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "mzapo_parlcd.h"

phys_addr_t *init_io() {
    phys_addr_t *io = (phys_addr_t *)malloc(sizeof(phys_addr_t));

    io->IO_MEM_BASE = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    if (io->IO_MEM_BASE == NULL) {
        fprintf(stderr, "Failed mapping SPILED_REG_BASE_PHYS.\n");
        exit(1);
    }

    io->LED_LINE = io->IO_MEM_BASE + SPILED_REG_LED_LINE_o;
    io->LED_RGB1 = io->IO_MEM_BASE + SPILED_REG_LED_RGB1_o;
    io->LED_RGB2 = io->IO_MEM_BASE + SPILED_REG_LED_RGB2_o;
    io->LED_RGB_DIRECT = io->IO_MEM_BASE + SPILED_REG_LED_KBDWR_DIRECT_o;
    io->KNOBS = io->IO_MEM_BASE + SPILED_REG_KNOBS_8BIT_o;
    io->KNOBS_DIRECT = io->IO_MEM_BASE + SPILED_REG_KBDRD_KNOBS_DIRECT_o;

    io->LCD_MEM_BASE = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    if (io->LCD_MEM_BASE == NULL) {
        fprintf(stderr, "Failed mapping PARLCD_REG_BASE_PHYS.\n");
        exit(1);
    }

    parlcd_hx8357_init(io->LCD_MEM_BASE);

    io->AUDIO_MEM_BASE = map_phys_address(AUDIOPWM_REG_BASE_PHYS, AUDIOPWM_REG_SIZE, 0);
    io->AUDIO_VOLUME = io->AUDIO_MEM_BASE + AUDIOPWM_REG_PWM_o;
    io->AUDIO_PERIOD = io->AUDIO_MEM_BASE + AUDIOPWM_REG_PWMPER_o;

    return io;
}

uint8_t get_red_knob_value(phys_addr_t *io) {
    return (*(volatile uint32_t *)(io->KNOBS) & 0x00ff0000) >> 16;
}

uint8_t is_red_knob_pressed(phys_addr_t *io) {
    return (*(volatile uint32_t *)(io->KNOBS) & 0x04000000) >> 26;
}

uint8_t get_green_knob_value(phys_addr_t *io) {
    return (*(volatile uint32_t *)(io->KNOBS) & 0x0000ff00) >> 8;
}

uint8_t is_green_knob_pressed(phys_addr_t *io) {
    return (*(volatile uint32_t *)(io->KNOBS) & 0x02000000) >> 25;
}

uint8_t get_blue_knob_value(phys_addr_t *io) {
    return *(volatile uint32_t *)(io->KNOBS) & 0x000000ff;
}

uint8_t is_blue_knob_pressed(phys_addr_t *io) {
    return (*(volatile uint32_t *)(io->KNOBS) & 0x01000000) >> 24;
}

void set_led_line_value(phys_addr_t *io, uint32_t value) {
    *(volatile uint32_t *)(io->LED_LINE) = value;
}

void set_led_rgb1_color(phys_addr_t *io, uint32_t color) {
    *(volatile uint32_t *)(io->LED_RGB1) = color;
}

void set_led_rgb2_color(phys_addr_t *io, uint32_t color) {
    *(volatile uint32_t *)(io->LED_RGB2) = color;
}

void lcd_display(phys_addr_t *io, uint16_t **screen) {
    parlcd_write_cmd(io->LCD_MEM_BASE, 0x2c);
    for (int y = 0; y < 320; y++) {
        for (int x = 0; x < 480; x++) {
            parlcd_write_data(io->LCD_MEM_BASE, screen[y][x]);
        }
    }
}

void set_audio_volume(phys_addr_t *io, unsigned int volume_level) {
    *(volatile uint32_t *)(io->AUDIO_VOLUME) = volume_level;
}

void set_audio_period(phys_addr_t *io, unsigned int period) {
    *(volatile uint32_t *)(io->AUDIO_PERIOD) = period;
}
