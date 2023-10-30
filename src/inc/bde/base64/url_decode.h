/**
 ***********************************************************************************************************************
 * @file        url_decode.h
 * @author      Diego Martínez García (dmg0345@gmail.com)
 * @date        30-10-2023 21:48:22 (UTC)
 * @version     1.0.2
 * @copyright   github.com/dmg0345/bde/blob/master/LICENSE
 ***********************************************************************************************************************
 */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef BDE_BASE64_URL_DECODE_H
#define BDE_BASE64_URL_DECODE_H

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup bde_base64url_decode_defs Definitions */
/** @defgroup bde_base64url_decode_papi Public API */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "bde/other/commons.h"

/* Exported types ----------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_base64url_decode_defs
 * @{
 */

/**
 * @}
 */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_base64url_decode_defs
 * @{
 */

/**
 * @}
 */

/* Exported macro ----------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_base64url_decode_papi
 * @{
 */

/**
 * @}
 */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_base64url_decode_papi
 * @{
 */

/**
 * @brief Obtains the length of the decoded data from the length of the Base64URL encoded string.
 * @param[in] encoded_len Length of the Base64URL encoded string, not including the @c NULL terminator.
 * @param[out] decoded_len Length of the decoded data.
 * @retval bde_error_ok Success.
 * @retval bde_error_args Invalid arguments.
 * @retval bde_error_encoded_string The Base64URL encoded string has an invalid form.
 */
bde_error_t bde_base64url_decode_length(const size_t encoded_len, size_t * const decoded_len);

/**
 * @brief Obtains the decoded data from the Base64URL encoded string.
 *
 * This function can decode inplace, it is possible to use the same buffer for the encoded and decoded data.
 * @param[in] encoded Base64URL encoded string.
 * @param[in] encoded_len Length of @p encoded, not including the @c NULL terminator.
 * @param[in] decoded_max_len Length of @p decoded.
 * @param[out] decoded Buffer where the decoded data will be written.
 * @param[out] decoded_len Amount of data written to @p decoded, can be @c NULL if not required by caller.
 * @retval bde_error_ok Success.
 * @retval bde_error_args Invalid arguments.
 * @retval bde_error_encoded_string The Base64URL encoded string given is not valid.
 */
bde_error_t bde_base64url_decode(const bde_enc_t * encoded,
                                 const size_t encoded_len,
                                 const size_t decoded_max_len,
                                 bde_dec_t * const decoded,
                                 size_t * const decoded_len);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BDE_BASE64_URL_DECODE_H */

/******************************************************************************************************END OF FILE*****/
