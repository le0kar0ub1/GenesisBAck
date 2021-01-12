/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _GBA_SOUND_H_
# define _GBA_SOUND_H_

# include <genesisback.h>

# define SOUND_IOMEM_BASE 0x4000060

struct sound_iomem
{
    uint16_t  SOUND1CNT_L; /*Channel 1 Sweep register       (NR10) */
    uint16_t  SOUND1CNT_H; /*Channel 1 Duty/Length/Envelope (NR11, NR12) */
    uint16_t  SOUND1CNT_X; /*Channel 1 Frequency/Control    (NR13, NR14) */
    uint16_t  _reserved1; /*          Not used */
    uint16_t  SOUND2CNT_L; /*Channel 2 Duty/Length/Envelope (NR21, NR22) */
    uint16_t  _reserved2; /*          Not used */
    uint16_t  SOUND2CNT_H; /*Channel 2 Frequency/Control    (NR23, NR24) */
    uint16_t  _reserved3; /*          Not used */
    uint16_t  SOUND3CNT_L; /*Channel 3 Stop/Wave RAM select (NR30) */
    uint16_t  SOUND3CNT_H; /*Channel 3 Length/Volume        (NR31, NR32) */
    uint16_t  SOUND3CNT_X; /*Channel 3 Frequency/Control    (NR33, NR34) */
    uint16_t  _reserved4; /*          Not used */
    uint16_t  SOUND4CNT_L; /*Channel 4 Length/Envelope      (NR41, NR42) */
    uint16_t  _reserved5; /*          Not used */
    uint16_t  SOUND4CNT_H; /*Channel 4 Frequency/Control    (NR43, NR44) */
    uint16_t  _reserved6; /*          Not used */
    uint16_t  SOUNDCNT_L; /* Control Stereo/Volume/Enable   (NR50, NR51) */
    uint16_t  SOUNDCNT_H; /* Control Mixing/DMA Control */
    uint16_t  SOUNDCNT_X; /* Control Sound on/off           (NR52) */
    uint16_t  _reserved7; /*          Not used */
    uint16_t  SOUNDBIAS; /*  Sound PWM Control */
    uint8_t   _reserved8[6]; /*       Not used */
    uint16_t  WAVE_RAM[8]; /* Channel 3 Wave Pattern RAM (2 banks!!) */
    uint32_t  FIFO_A; /*   Channel A FIFO, Data 0-3 */
    uint32_t  FIFO_B; /*   Channel B FIFO, Data 0-3 */
};

#endif /* _GBA_SOUND_H_ */