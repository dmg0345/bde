/**
 ***********************************************************************************************************************
 * @file        cmocka_defs.h
 * @author      Diego Martínez García (dmg0345@gmail.com)
 * @date        06-03-2024 22:23:23 (UTC)
 * @version     1.0.3
 * @copyright   github.com/dmg0345/bde/blob/master/LICENSE
 ***********************************************************************************************************************
 */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef CMOCKA_DEFS_H
#define CMOCKA_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @defgroup cmocka_defs_defs Definitions */
/** @defgroup cmocka_defs_papi Public API */
/** @defgroup cmocka_defs_iapi_impl Internal API implementation */
/** @defgroup cmocka_defs_papi_impl Public API implementation */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include <stdarg.h>
#include <stddef.h>
// MISRA Justification:
// This header is necessary just for the testing suites.
// cppcheck-suppress misra-c2012-21.4
#include <setjmp.h>
#include <stdbool.h>
#include <string.h>
// MISRA Justification:
// This header is necessary just for the testing suites.
// cppcheck-suppress misra-c2012-21.6
#include <stdio.h>
#include <stdint.h>
#include "cmocka.h"

/* Exported types ----------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup cmocka_defs_defs
 * @{
 */

/**
 * @}
 */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup cmocka_defs_defs
 * @{
 */

#define CMOCKA_OK    (0) /**< Generic CMocka success. */
#define CMOCKA_ERROR (1) /**< Generic CMocka error. */

/**
 * @}
 */

/* Exported macro ----------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup cmocka_defs_papi
 * @{
 */

/**
 * @brief Calculates the number of elements in an array.
 * @param[in] array The array.
 * @return The number of elements in an array.
 */
#define ARRAY_DIM(array) (sizeof((array)) / sizeof(*(array)))

/**
 * @}
 */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup cmocka_defs_papi
 * @{
 */

/**
 * @brief Function that needs to be called prior to running all test runners to initialize CMocka.
 */
void cmocka_init(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CMOCKA_DEFS_H */

/******************************************************************************************************END OF FILE*****/
