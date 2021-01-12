/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _GBA_SERIAL_H_
# define _GBA_SERIAL_H_

# include <genesisback.h>

# define SERIAL1_IOMEM_BASE 0x4000120
# define SERIAL2_IOMEM_BASE 0x4000134

struct serial1_iomem
{
    uint32_t  sio_data32; /* SIO Data (Normal-32bit Mode; shared with below) */
    uint16_t  sio_multi0; /* SIO Data 0 (Parent)    (Multi-Player Mode) */
    uint16_t  sio_multi1; /* SIO Data 1 (1st Child) (Multi-Player Mode) */
    uint16_t  sio_multi2; /* SIO Data 2 (2nd Child) (Multi-Player Mode) */
    uint16_t  sio_multi3; /* SIO Data 3 (3rd Child) (Multi-Player Mode) */
    uint16_t  sio_ctrl; /*    SIO Control Register */
    uint16_t  sio_mlt_send; /* SIO Data (Local of MultiPlayer; shared below) */
    uint16_t  sio_data8; /*  SIO Data (Normal-8bit and UART Mode) */
};

struct serial2_iomem
{
    uint16_t rcnt;      /* SIO Mode Select/General Purpose Data */
    uint16_t ir;        /* Ancient - Infrared Register (Prototypes only) */
    uint16_t _reserved1;         /* Not used */
    uint16_t joycnt;    /* SIO JOY Bus Control */
    uint16_t _reserved2[7]; /* Not used */
    uint32_t joy_recv;  /* SIO JOY Bus Receive Data */
    uint32_t joy_trans; /* SIO JOY Bus Transmit Data */
    uint16_t joy_stat;   /* SIO JOY Bus Receive Status */
};

#endif /* _GBA_SERIAL_H_ */