/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _SOC_VIDEO_H_
# define _SOC_VIDEO_H_

# define VIDEO_IOMEM_BASE 0x4000000

struct video_iomem
{
    uint16_t dispctrl;    /* LCD Control */
    uint16_t _reserved1; /* Undocumented - Green Swap */
    uint16_t dispstat;   /* General LCD Status (STAT,LYC) */
    uint16_t vcount;     /* Vertical Counter (LY) */
    uint16_t bg0_ctrl;    /* BG0 Control */
    uint16_t bg1_ctrl;    /* BG1 Control */
    uint16_t bg2_ctrl;    /* BG2 Control */
    uint16_t bg3_ctrl;    /* BG3 Control */
    uint16_t bg0_xoff;   /* BG0 X-Offset */
    uint16_t bg0_yoff;   /* BG0 Y-Offset */
    uint16_t bg1_xoff;   /* BG1 X-Offset */
    uint16_t bg1_yoff;   /* BG1 Y-Offset */
    uint16_t bg2_xoff;   /* BG2 X-Offset */
    uint16_t bg2_yoff;   /* BG2 Y-Offset */
    uint16_t bg3_xoff;   /* BG3 X-Offset */
    uint16_t bg3_yoff;   /* BG3 Y-Offset */
    uint16_t bg2_pa;     /* BG2 Rotation/Scaling Parameter A (dx) */
    uint16_t bg2_pb;     /* BG2 Rotation/Scaling Parameter B (dmx) */
    uint16_t bg2_pc;     /* BG2 Rotation/Scaling Parameter C (dy) */
    uint16_t bg2_pd;     /* BG2 Rotation/Scaling Parameter D (dmy) */
    uint32_t bg2_x;      /* BG2 Reference Point X-Coordinate */
    uint32_t bg2_y;      /* BG2 Reference Point Y-Coordinate */
    uint16_t bg3_pa;     /* BG3 Rotation/Scaling Parameter A (dx) */
    uint16_t bg3_pb;     /* BG3 Rotation/Scaling Parameter B (dmx) */
    uint16_t bg3_pc;     /* BG3 Rotation/Scaling Parameter C (dy) */
    uint16_t bg3_pd;     /* BG3 Rotation/Scaling Parameter D (dmy) */
    uint32_t bg3_x;      /* BG3 Reference Point X-Coordinate */
    uint32_t bg3_y;      /* BG3 Reference Point Y-Coordinate */
    uint16_t win0h;      /* Window 0 Horizontal Dimensions */
    uint16_t win1h;      /* Window 1 Horizontal Dimensions */
    uint16_t win0v;      /* Window 0 Vertical Dimensions */
    uint16_t win1v;      /* Window 1 Vertical Dimensions */
    uint16_t winin;      /* Inside of Window 0 and 1 */
    uint16_t winout;     /* Inside of OBJ Window & Outside of Windows */
    uint16_t mosaic;     /* Mosaic Size */
    uint16_t _reserved2; /* Not used */
    uint16_t bldctrl;     /* Color Special Effects Selection */
    uint16_t bldalpha;   /* Alpha Blending Coefficients */
    uint16_t bldy;       /* Brightness (Fade-In/Out) Coefficient */
};

#endif /* _SOC_VIDEO_H_ */