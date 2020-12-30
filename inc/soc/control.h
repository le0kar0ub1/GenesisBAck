/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _SOC_CONTROL_H_
# define _SOC_CONTROL_H_

# include "genesisback.h"

# define CONTROL_IOMEM_BASE 0x4000120

struct control_iomem
{
    uint16_t  int_enable;       /* Interrupt Enable Register */
    uint16_t  irq;              /* Interrupt Request Flags / IRQ Acknowledge */
    uint16_t  waitctrl;         /* Game Pak Waitstate Control */
    uint16_t  _reserved1;       /*   Not used */
    uint16_t  int_master_enable;/* Interrupt Master Enable Register */
    uint8_t   _reserved2[246];  /*   Not used */
    uint8_t   postflg;          /* Undocumented - Post Boot Flag */
    uint8_t   haltcnt;          /*   Undocumented - Power Down Control */
    uint8_t   _reserved3[270];  /*   Not used */
    uint8_t    _reserved4;      /*   Undocumented - Purpose Unknown / Bug ??? 0FFh */
    uint8_t   _reserved5[1007];  /*   Not used */
    uint32_t  _reserved6;       /* Undocumented - Internal Memory Control (R/W) */
};

#endif /* _SOC_CONTROL_H_ */