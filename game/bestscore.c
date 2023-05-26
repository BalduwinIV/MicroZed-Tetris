#include "bestscore.h"

#include <stdio.h>
#include <stdlib.h>

unsigned int get_bestscore() {
    FILE *bestscore_f = fopen(BESTSCORE_FILENAME, "rb");
    if (!bestscore_f) {
        return 0;
    }
    unsigned int return_value = (getc(bestscore_f)) | (getc(bestscore_f) << 8) | (getc(bestscore_f) << 16) | (getc(bestscore_f) << 24);
    fclose(bestscore_f);
    printf("Best score is %d.\n", return_value);
    return return_value;
}

void set_bestscore(unsigned int value) {
    FILE *bestscore_f = fopen(BESTSCORE_FILENAME, "wb");
    if (!bestscore_f) {
        fprintf(stderr, "Error writing data to %s file.\n", BESTSCORE_FILENAME);
    } else {
        printf("Writing bestscore to file: (%d) %x %x %x %x.\n", value, (value & 0xff000000) >> 24, (value & 0x00ff0000) >> 16, (value & 0x0000ff00) >> 8, value & 0x000000ff);
        fputc(value & 0x000000ff, bestscore_f);
        fputc((value & 0x0000ff00) >> 8, bestscore_f);
        fputc((value & 0x00ff0000) >> 16, bestscore_f);
        fputc((value & 0xff000000) >> 24, bestscore_f);
    }
    fclose(bestscore_f);
}
