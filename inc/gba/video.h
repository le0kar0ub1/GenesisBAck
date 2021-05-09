/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _GBA_VIDEO_H_
# define _GBA_VIDEO_H_

# include <genesisback.h>

# define VIDEO_IOMEM_BASE 0x4000000

struct video_iomem
{
    uint16_t dispctrl;   /* LCD Control */
    uint16_t _reserved1; /* Undocumented - Green Swap */
    uint16_t dispstat;   /* General LCD Status (STAT,LYC) */
    uint16_t vcount;     /* Vertical Counter (LY) */
    uint16_t bg0_ctrl;   /* BG0 Control */
    uint16_t bg1_ctrl;   /* BG1 Control */
    uint16_t bg2_ctrl;   /* BG2 Control */
    uint16_t bg3_ctrl;   /* BG3 Control */
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
    uint16_t bldctrl;    /* Color Special Effects Selection */
    uint16_t bldalpha;   /* Alpha Blending Coefficients */
    uint16_t bldy;       /* Brightness (Fade-In/Out) Coefficient */
};

enum {
    VIDEO_IOMEM_DISPCNT  = 0x4000000,    /* LCD Control */
    VIDEO_IOMEM_DISPSTAT = 0x4000004,    /* General LCD Status (STAT,LYC) */
    VIDEO_IOMEM_VCOUNT   = 0x4000006,    /* Vertical Counter (LY) */
    VIDEO_IOMEM_BG0CNT   = 0x4000008,    /* BG0 Control */
    VIDEO_IOMEM_BG1CNT   = 0x400000A,    /* BG1 Control */
    VIDEO_IOMEM_BG2CNT   = 0x400000C,    /* BG2 Control */
    VIDEO_IOMEM_BG3CNT   = 0x400000E,    /* BG3 Control */
    VIDEO_IOMEM_BG0HOFS  = 0x4000010,    /* BG0 X-Offset */
    VIDEO_IOMEM_BG0VOFS  = 0x4000012,    /* BG0 Y-Offset */
    VIDEO_IOMEM_BG1HOFS  = 0x4000014,    /* BG1 X-Offset */
    VIDEO_IOMEM_BG1VOFS  = 0x4000016,    /* BG1 Y-Offset */
    VIDEO_IOMEM_BG2HOFS  = 0x4000018,    /* BG2 X-Offset */
    VIDEO_IOMEM_BG2VOFS  = 0x400001A,    /* BG2 Y-Offset */
    VIDEO_IOMEM_BG3HOFS  = 0x400001C,    /* BG3 X-Offset */
    VIDEO_IOMEM_BG3VOFS  = 0x400001E,    /* BG3 Y-Offset */
    VIDEO_IOMEM_BG2PA    = 0x4000020,    /* BG2 Rotation/Scaling Parameter A (dx) */
    VIDEO_IOMEM_BG2PB    = 0x4000022,    /* BG2 Rotation/Scaling Parameter B (dmx) */
    VIDEO_IOMEM_BG2PC    = 0x4000024,    /* BG2 Rotation/Scaling Parameter C (dy) */
    VIDEO_IOMEM_BG2PD    = 0x4000026,    /* BG2 Rotation/Scaling Parameter D (dmy) */
    VIDEO_IOMEM_BG2X     = 0x4000028,    /* BG2 Reference Point X-Coordinate */
    VIDEO_IOMEM_BG2Y     = 0x400002C,    /* BG2 Reference Point Y-Coordinate */
    VIDEO_IOMEM_BG3PA    = 0x4000030,    /* BG3 Rotation/Scaling Parameter A (dx) */
    VIDEO_IOMEM_BG3PB    = 0x4000032,    /* BG3 Rotation/Scaling Parameter B (dmx) */
    VIDEO_IOMEM_BG3PC    = 0x4000034,    /* BG3 Rotation/Scaling Parameter C (dy) */
    VIDEO_IOMEM_BG3PD    = 0x4000036,    /* BG3 Rotation/Scaling Parameter D (dmy) */
    VIDEO_IOMEM_BG3X     = 0x4000038,    /* BG3 Reference Point X-Coordinate */
    VIDEO_IOMEM_BG3Y     = 0x400003C,    /* BG3 Reference Point Y-Coordinate */
    VIDEO_IOMEM_WIN0H    = 0x4000040,    /* Window 0 Horizontal Dimensions */
    VIDEO_IOMEM_WIN1H    = 0x4000042,    /* Window 1 Horizontal Dimensions */
    VIDEO_IOMEM_WIN0V    = 0x4000044,    /* Window 0 Vertical Dimensions */
    VIDEO_IOMEM_WIN1V    = 0x4000046,    /* Window 1 Vertical Dimensions */
    VIDEO_IOMEM_WININ    = 0x4000048,    /* Inside of Window 0 and 1 */
    VIDEO_IOMEM_WINOUT   = 0x400004A,    /* Inside of OBJ Window & Outside of Windows */
    VIDEO_IOMEM_MOSAIC   = 0x400004C,    /* Mosaic Size */
    VIDEO_IOMEM_BLDCNT   = 0x4000050,    /* Color Special Effects Selection */
    VIDEO_IOMEM_BLDALPHA = 0x4000052,    /* Alpha Blending Coefficients */  
    VIDEO_IOMEM_BLDY     = 0x4000054     /* Brightness (Fade-In/Out) Coefficient */
};

/**
 * Each color occupied two bytes.
 */
struct color
{
    union
    {
        struct
        {
            uint16_t red    : 5;
            uint16_t green  : 5;
            uint16_t blue   : 5;
            uint16_t unused : 1;
        };
        uint16_t raw;
    };
};


struct OBJ_ATTR_0
{
    union 
    {
        struct
        {
            uint16_t y              : 8; // Y-Coordinate (0-255)
            uint16_t rot_scal_flag  : 1; // (0=Off, 1=On)
            uint16_t obj_disable    : 1; // Meaning depends on above flag.
            uint16_t obj_mode       : 2; // (0=Normal, 1=Semi-Transparent, 2=OBJ Window, 3=Prohibited)
            uint16_t obj_mosaic     : 1; // (0=Off, 1=On)
            uint16_t color_mode     : 1; // (0=16/16, 1=256/1)
            uint16_t obj_shape      : 2; // (0=Square,1=Horizontal,2=Vertical,3=Prohibited)
        };
        uint16_t raw;
    };
};

/**
 * When Rotation/Scaling used (Attribute 0, bit 8 set):
 *     9-13  Rotation/Scaling Parameter Selection (0-31)
 *         (Selects one of the 32 Rotation/Scaling Parameters that
 *         can be defined in OAM, for details read next chapter.)
 * When Rotation/Scaling not used (Attribute 0, bit 8 cleared):
 *     9-11  Not used
 *     12    Horizontal Flip      (0=Normal, 1=Mirrored)
 *     13    Vertical Flip        (0=Normal, 1=Mirrored)
 */
struct OBJ_ATTR_1
{
     union
    {
        struct
        {
            uint16_t x              : 9; /*(0-8) X-Coordinate (0-511) */
            uint16_t rot_scal_param : 5; /*(9-13) desc above */
            uint16_t obj_size       : 2; /*(14-15) (0..3, depends on OBJ Shape, see Attr 0) */
        };
        uint16_t raw;
    };
};

struct OBJ_ATTR_2
{
     union
    {
        struct
        {
            uint16_t char_name      : 10;   /*(0-9)     (0-1023=Tile Number)*/
            uint16_t priority_on_bg : 2;    /*(10-11)   (0=Highest)*/
            uint16_t palette_number : 4;    /*(12-15)   (Not used in 256 color/1 palette mode)*/
        };
        uint16_t raw;
    };
};


void gpu_flush_display(void);

#endif /* _GBA_VIDEO_H_ */