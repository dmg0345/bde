/**
 ***********************************************************************************************************************
 * @file        cmocka_defs.h
 * @author      Diego Martínez García (dmg0345@gmail.com)
 * @date        07-10-2023 23:44:17 (UTC)
 * @version     1.0.0
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
/** @defgroup cmocka_defs_errors Errors */
/** @defgroup cmocka_defs_papi Public API */

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

/**
 * @}
 */

/**
 * @addtogroup cmocka_defs_errors
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

#endif /* CMOCKA_DEFS */

/******************************************************************************************************END OF FILE*****/
