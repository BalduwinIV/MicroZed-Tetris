#ifndef PAUSE_H
#define PAUSE_H

#include "../hardware/io_address.h"

#define CONTINUE        0
#define ENABLE_AUDIO    1
#define VOLUME_AUDIO    2
#define GO_TO_MENU      3

unsigned char pause(unsigned short **screen, phys_addr_t *io, unsigned char *enable_audio, unsigned char *audio_volume);

#endif
