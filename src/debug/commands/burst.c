/******************************************************************************
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include "debug/debug.h"
# include "core/core.h"
# include "mmu/mmu.h"
# include "capstone/capstone.h"

void debug_cmd_burst(int ac, char const **av)
{
    uint32_t addr;
    size_t cnt;
    size_t size;
    bool state = core_read_state();
    csh handle;
    cs_insn *burst;

    if (ac == 1) {
        addr = register_read32(PC);
        addr = state == STATE_ARM ? addr - 4 : addr - 2;
    } else if (ac == 2) {
        addr = register_read32(PC);
        addr = state == STATE_ARM ? addr - 4 : addr - 2;
        size = strtoul(av[1], NULL, get_base(av[1]));
    } else if (ac == 3) {
        size = strtoul(av[1], NULL, get_base(av[1]));
        addr = strtoul(av[2], NULL, get_base(av[2]));
    } else {
        return;
    }

    cs_open(
        CS_ARCH_ARM,
        state == STATE_ARM ? CS_MODE_ARM : CS_MODE_THUMB,
        &handle
    );

    if (state == STATE_ARM) {
        uint32_t *code = malloc(size * 4);
        for (size_t fill = 0; fill < size; fill++)
            code[fill] = mmu_read32(addr + (fill * 4));
        cnt = cs_disasm(handle, (uint8_t *)code, size * 4, addr, 0, &burst);
        free(code);
    } else {
        uint16_t *code = malloc(size * 2);
        for (size_t fill = 0; fill < size; fill++)
            code[fill] = mmu_read16(addr + (fill * 2));
        cnt = cs_disasm(handle, (uint8_t *)code, size * 2, addr, 0, &burst);
        free(code);
    }

    if (cnt) {
        for (size_t i = 0; i < cnt; i++)
            printf("%#08lx:\t%s\t%s\n", burst[i].address, burst[i].mnemonic, burst[i].op_str);
        cs_free(burst, cnt);
    } else {
        printf("Dissassembling failed\n");
    }
    cs_close(&handle);
}