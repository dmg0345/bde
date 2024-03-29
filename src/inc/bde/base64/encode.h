/**
 ***********************************************************************************************************************
 * @file        encode.h
 * @author      Diego Martínez García (dmg0345@gmail.com)
 * @date        06-03-2024 22:23:23 (UTC)
 * @version     1.0.3
 * @copyright   github.com/dmg0345/bde/blob/master/LICENSE
 ***********************************************************************************************************************
 */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef BDE_BASE64_ENCODE_H
#define BDE_BASE64_ENCODE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "bde/other/commons.h"

/* Exported types ----------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_base64_encode_defs
 * @{
 */

/**
 * @}
 */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_base64_encode_defs
 * @{
 */

/**
 * @}
 */

/* Exported macro ----------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_base64_encode_papi
 * @{
 */

/**
 * @}
 */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_base64_encode_papi
 * @{
 */

/**
 * @brief Obtains the length of the Base64 encoded string from the length of the decoded data.
 * @param[in] decoded_len Length of the decoded data.
 * @param[out] encoded_len Length of the Base64 encoded string, not including the @c NULL terminator.
 * @retval ::bde_error_ok Success.
 * @retval ::bde_error_args Invalid arguments.
 */
bde_error_t bde_base64_encode_length(const size_t decoded_len, size_t * const encoded_len);

/**
 * @brief Obtains the Base64 encoded string from the decoded data.
 *
 * This function can encode inplace, it is possible to use the same buffer for the encoded and decoded data.
 * @param[in] decoded Decoded data.
 * @param[in] decoded_len Length of @p decoded.
 * @param[in] encoded_max_len Length of @p encoded.
 * @param[out] encoded Buffer where the Base64 encoded string and the @c NULL terminator will be written.
 * @param[out] encoded_len Amount of data written to @p encoded, not including the @c NULL terminator, can be @c NULL if
 * not required by caller.
 * @retval ::bde_error_ok Success.
 * @retval ::bde_error_args Invalid arguments.
 */
bde_error_t bde_base64_encode(const bde_dec_t * const decoded,
                              const size_t decoded_len,
                              const size_t encoded_max_len,
                              bde_enc_t * const encoded,
                              size_t * const encoded_len);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BDE_BASE64_ENCODE_H */

/******************************************************************************************************END OF FILE*****/
