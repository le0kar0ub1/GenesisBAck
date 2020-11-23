/******************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _DEF_ASSERT_H_
# define _DEF_ASSERT_H_

# include "genesisback.h"

# define static_assert(expr)                             \
    _Static_assert(                                      \
        expr,                                            \
        "assert(" #expr ") failed (file: " __FILE__ ")"  \
    )

# define assert(expr)                                           \
    if (unlikely(!(expr))) {                                    \
            panic(                                              \
                "assert(%s) failed in file %s at line %u).\n",  \
                #expr,                                          \
                __FILE__,                                       \
                __LINE__                                        \
            );                                                  \
        }                                                       \

# define assert_isok(expr) assert((status_t)expr == OK)

# define assert_debug(expr)
    #if DEBUG_MASTER == true
        assert(expr)
    #endif

#endif /* !_DEF_ASSERT_H_ */
