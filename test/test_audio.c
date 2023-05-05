#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "../hardware/mzapo_regs.h"
#include "../hardware/mzapo_phys.h"

#define E6      659.25511
#define B5      493.8833
#define C6      523.25113
#define D6      587.32954
#define A5      440.0
#define F6      698.45646
#define A6      880.0
#define G6      783.99087

double frequency[] = {
    E6, B5, C6, D6, C6, B5, A5, A5,
    C6, E6, D6, C6, B5, C6, D6, E6, 
    C6, A5, 
    A5, A5, B5, C6, D6, F6, A6, G6, 
    F6, E6, C6, E6, D6, C6, B5, B5, 
    C6, D6,
    E6, C6, A5, A5,

    A5, A5, B5, C6, D6, F6, A6, G6, 
    F6, E6, C6, E6, D6, C6, B5, B5, 
    C6, D6,
    E6, C6, A5, A5,
};
unsigned int duration[] = {
    406250, 203125, 203125, 406250, 203125, 203125, 406250, 203125, 
    203125, 406250, 203125, 203125, 609375, 203125, 406250, 406250, 
    406250, 406250, 
    203125, 203125, 203125, 203125, 609375, 203125, 406250, 203125, 
    203125, 609375, 203125, 406250, 203125, 203125, 203125, 203125, 
    203125, 406250, 
    406250, 406250, 406250, 406250,

    203125, 203125, 203125, 203125, 609375, 203125, 406250, 203125, 
    203125, 609375, 203125, 406250, 203125, 203125, 203125, 203125, 
    203125, 406250, 
    406250, 406250, 406250, 406250,
};

unsigned int get_period(double frequency);

int main() {
    struct timespec delay = {.tv_sec = 0, .tv_nsec = 10*1000};

    unsigned char *mem_base = map_phys_address(AUDIOPWM_REG_BASE_PHYS, AUDIOPWM_REG_SIZE, 0);

    *(volatile uint32_t *)(mem_base + AUDIOPWM_REG_PWM_o) = 50;
    for (int c = 0; c < 2; c++) {
        for (int i = 0; i < 62; i++) {
            *(volatile uint32_t *)(mem_base + AUDIOPWM_REG_PWMPER_o) = get_period(frequency[i]);
            printf("value = %d\n", get_period(frequency[i]));
            delay.tv_nsec = duration[i] * 1000;
            clock_nanosleep(CLOCK_MONOTONIC, 0, &delay, NULL);
        }
        *(volatile uint32_t *)(mem_base + AUDIOPWM_REG_PWMPER_o) = 0;
        delay.tv_sec = 1;
        clock_nanosleep(CLOCK_MONOTONIC, 0, &delay, NULL);
        delay.tv_sec = 0;
    }
    *(volatile uint32_t *)(mem_base + AUDIOPWM_REG_PWMPER_o) = 0;
    *(volatile uint32_t *)(mem_base + AUDIOPWM_REG_PWM_o) = 0;
}

unsigned int get_period(double frequency) {
    return (unsigned int)(100000000/frequency);
}
