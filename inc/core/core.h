/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _CORE_CORE_H_
# define _CORE_CORE_H_

# include "genesisback.h"
# include <endian.h>

/**
 * The cpu has to deal with these type of data only
 */
typedef uint8_t   byte_t;
typedef uint16_t  hword_t;
typedef uint32_t  word_t;

/**
 * Define the 2 processor states
 */
enum {
    STATE_ARM   = 0b0,
    STATE_THUMB = 0b1
};

# define MASK_ARM_RELOAD(x)   (x & 0xFFFFFFFC)
# define MASK_THUMB_RELOAD(x) (x & 0xFFFFFFFE) 

# define ALIGN2(x) (x & 0xFFFFFFFE)
# define ALIGN4(x) (x & 0xFFFFFFFC)

/**
 * Define the 7 operations modes of the processor
 */
enum {
    OPERATION_MODE_USER       = 0b10000,
    OPERATION_MODE_FIQ        = 0b10001,
    OPERATION_MODE_IRQ        = 0b10010, 
    OPERATION_MODE_SUPERVISOR = 0b10011,
    OPERATION_MODE_ABORT      = 0b10111, 
    OPERATION_MODE_UNDEFINED  = 0b11011,
    OPERATION_MODE_SYSTEM     = 0b11111
};

enum ARM7TDMI_REGISTER {
    R0  = 0,
    R1  = 1,
    R2  = 2,
    R3  = 3,
    R4  = 4,
    R5  = 5,
    R6  = 6,
    R7  = 7,
    R8  = 8,
    R9  = 9,
    R10 = 10,
    R11 = 11,
    R12 = 12,
    R13 = 13, SP  = 13,
    R14 = 14, LR  = 14,
    R15 = 15, PC  = 15
};

enum OPCODE_CONDITION {
    CONDITION_EQ = 0b0000,  // Equal
    CONDITION_NE = 0b0001,  // Not Equal
    CONDITION_CS = 0b0010,  // Unsigned higher or same
    CONDITION_CC = 0b0011,  // Unsigned lower
    CONDITION_MI = 0b0100,  // Negative
    CONDITION_PL = 0b0101,  // Positive or zero
    CONDITION_VS = 0b0110,  // Overflow
    CONDITION_VC = 0b0111,  // No overflow
    CONDITION_HI = 0b1000,  // Unsigned higher
    CONDITION_LS = 0b1001,  // Unsigned lower or same
    CONDITION_GE = 0b1010,  // Greater or equal
    CONDITION_LT = 0b1011,  // Less than
    CONDITION_GT = 0b1100,  // Greather than
    CONDITION_LE = 0b1101,  // Less than or equal
    CONDITION_AL = 0b1110,  // Always
};

/**
 * A basic wide 32 bits register
 */
struct register32
{
    union
    {
        union
        {
            union
            {
                struct
                {
                    uint8_t r8;
                    uint8_t _reserved8;
                };
                uint16_t r16;
            };
            uint16_t _reserverd16;
        };
        uint32_t r32;
    };
};

static_assert(sizeof(struct register32) == 4);

/**
 * CPSR register articulation
 */
struct register_psr
{
    union
    {
        struct
        {
        #ifdef __BIG_ENDIAN__
            uint32_t opmode        : 5;
            uint32_t state         : 1;
            uint32_t fiq_disable   : 1;
            uint32_t irq_disable   : 1;
            uint32_t _reserved     : 20;
            uint32_t overflow      : 1;
            uint32_t carry         : 1;
            uint32_t zero          : 1;
            uint32_t negative      : 1;
        #else
            uint32_t negative      : 1;
            uint32_t zero          : 1;
            uint32_t carry         : 1;
            uint32_t overflow      : 1;
            uint32_t _reserved     : 20;
            uint32_t irq_disable   : 1;
            uint32_t fiq_disable   : 1;
            uint32_t state         : 1;
            uint32_t opmode        : 5;
        #endif
        };
        uint32_t raw;
    };
};

static_assert(sizeof(struct register_psr) == sizeof(uint32_t));

/**
 * Will be staticaly declared for each mode and will refered to the good register in the arm7dmi global
 */
struct arm_regs
{
    union
    {
        struct
        {
            struct register32 *r0;
            struct register32 *r1;
            struct register32 *r2;
            struct register32 *r3;
            struct register32 *r4;
            struct register32 *r5;
            struct register32 *r6;
            struct register32 *r7;
            struct register32 *r8;
            struct register32 *r9;
            struct register32 *r10;
            struct register32 *r11;
            struct register32 *r12;
            /* stack pointer */
            struct register32 *r13;
            /* link register */
            struct register32 *r14;
            /* program counter */
            struct register32 *r15;

            struct register_psr *cpsr;
            struct register_psr *spsr;
        };
        uint32_t *raw[18];
    };
};

/**
 * Will be staticaly declared for each mode and will refered to the good register in the arm7dmi global
 */
struct thumb_regs
{
    union
    {
        struct {
            struct register32 *r0;
            struct register32 *r1;
            struct register32 *r2;
            struct register32 *r3;
            struct register32 *r4;
            struct register32 *r5;
            struct register32 *r6;
            struct register32 *r7;
            /* stack pointer */
            struct register32 *r13;
            /* link register */
            struct register32 *r14;
            /* program counter */
            struct register32 *r15;

            struct register_psr *cpsr;
            struct register_psr *spsr;
        };
        uint32_t *raw[13];
    };
};

void register_reset(void);
struct register32 *register_read_ptr(uint32_t id);
uint8_t register_read8(uint32_t id);
uint16_t register_read16(uint32_t id);
uint32_t register_read32(uint32_t id);
void register_write8(uint32_t id, uint8_t val);
void register_write16(uint32_t id, uint16_t val);
void register_write32(uint32_t id, uint32_t val);
void register_uadd32(uint32_t id, uint32_t val);
void register_usub32(uint32_t id, uint32_t val);
struct register_psr register_read_cpsr(void);
void register_write_cpsr(uint32_t wr);
struct register_psr register_read_spsr(void);
void register_write_spsr(uint32_t wr);
struct thumb_regs *core_get_thumb_regs(void);
struct arm_regs *core_get_arm_regs(void);

uint32_t core_read_prefetch(void);
void core_write_prefetch(uint32_t prefetch);
uint32_t core_read_state(void);
uint32_t core_read_opmode(void);
void core_init(void);
void core_exit(void);
void core_start(void);
void core_reset(void);
void core_switch_state(uint32_t state);
void core_switch_opmode(uint32_t opmode);
void core_flush_pipeline(void);

void core_scheduler(void);
bool schedule_opcode_condition(uint32_t cond);

#endif /* _CORE_CORE_H_ */