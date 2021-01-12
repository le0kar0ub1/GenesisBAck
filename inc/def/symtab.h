/********************************************************************************
** 
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _DEF_KSYMTAB_H_
# define _DEF_KSYMTAB_H_

# include <def/def.h>

struct symbol_t
{
    void *addr;
    const char *name;
};

# define EXPORT_SYMBOL(symbol) \
    extern typeof(symbol) symbol; \
    static const char __sym_name_##symbol[] = #symbol; \
    static const struct symbol_t __ksymtab_##symbol \
    __attribute__((__used__, section(".genesisback.symtab.text"))) = { (void *)&symbol, __sym_name_##symbol }

# define symbol_get_name(x) ((typeof(&x))(__symbol_get_name(#x)))
# define symbol_get_addr(x) ((typeof(&x))(__symbol_get_addr(#x)))

char const *__symbol_get_name(void *);
void *__symbol_get_addr(const char *);

#endif /* !_DEF_KSYMTAB_H_ */
