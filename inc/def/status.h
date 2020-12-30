/********************************************************************************
** 
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _DEF_STATUS_H_
# define _DEF_STATUS_H_

# include "def/assert.h"

/**
 * GenesisBack status
*/
typedef enum status {
    Ok = 0,
    ERR_FATAL
} status_t;

/**
 * A bad result implementation.
*/
typedef uint64_t any64_t;
typedef struct result
{
    status_t status;
    any64_t  result;
} __packed result_t;

/**
* Is the result an ERR
*/
# define RESULT_IS_ERR(x)       \
            (x.status != OK)

/**
* Is the result an OK
*/
# define RESULT_IS_OK(x)        \
            !(STATUS_IS_ERR(x))

/**
* Get the result
*/

# define RESULT_ERR(x)  \
            (x.status)

/**
* Unwrap the result
*/
# define RESULT_OK(res, type)   \
            (type)(res.result)

/**
* Propagate if ERR
*/
# define RAISE_IF(tgt, res)          \
            if (RESULT_IS_ERR(res))  \
                return (res)

/**
* Unwrap if OK or propagate if ERR
*/
# define UNWRAP_OR_RAISE(tgt, res)              \
            if (RESULT_IS_ERR(res))             \
                return (res);                   \
            tgt = RESULT_OK(res, typeof(tgt));

/**
* Return OK as a result
*/
# define OK_PROPAGATION(res)            \
            return (                    \
                (result_t) {            \
                    OK,                 \
                    res                 \
                }                       \
            )

/**
* Return the given ERR as a result 
*/
# define ERR_PROPAGATION(err)           \
            return (                    \
                (result_t) {            \
                    err,                \
                    err                 \
                }                       \
            )

#endif /* !_DEF_STATUS_H_ */
