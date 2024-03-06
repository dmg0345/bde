/**
 ***********************************************************************************************************************
 * @file        commons.h
 * @author      Diego Martínez García (dmg0345@gmail.com)
 * @date        06-03-2024 22:23:23 (UTC)
 * @version     1.0.3
 * @copyright   github.com/dmg0345/bde/blob/master/LICENSE
 ***********************************************************************************************************************
 */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef BDE_COMMONS_H
#define BDE_COMMONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include <stddef.h>
#include <stdint.h>

/* Exported types ----------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_commons_defs
 * @{
 */

typedef char bde_enc_t; /**< The type of each element in the encoded data. */
typedef uint8_t bde_dec_t; /**< The type of each element in the decoded data. */

/**
 * @}
 */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_commons_defs
 * @{
 */

/**
 * @}
 */

/**
 * @addtogroup bde_commons_errors
 * @{
 */

/** Errors returned by this library. */
typedef enum
{
    bde_error_ok = 0U, /**< No error, success. */
    bde_error_args, /**< One or more arguments provided are invalid. */
    bde_error_buffer_length, /**< Buffer length is not big enough. */
    bde_error_encoded_string, /**< String is not a valid encoded string. */

    bde_error_count /**< Number of errors. */
} bde_error_t;

/**
 * @}
 */

/* Exported macro ----------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_commons_papi
 * @{
 */

/**
 * @}
 */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_commons_papi
 * @{
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BDE_COMMONS_H */

/******************************************************************************************************END OF FILE*****/
