/**
 ***********************************************************************************************************************
 * @file        decode.h
 * @author      ${PROJECT_AUTHOR} (${PROJECT_CONTACT})
 * @date        ${PROJECT_BUILD_TIMESTAMP_UTC}
 * @version     ${PROJECT_VERSION}
 * @copyright   ${PROJECT_COPYRIGHT}
 ***********************************************************************************************************************
 */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef BDE_BASE64_DECODE_H
#define BDE_BASE64_DECODE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "bde/other/commons.h"

/* Exported types ----------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_base64_decode_defs
 * @{
 */

/**
 * @}
 */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_base64_decode_defs
 * @{
 */

/**
 * @}
 */

/* Exported macro ----------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_base64_decode_papi
 * @{
 */

/**
 * @}
 */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_base64_decode_papi
 * @{
 */

/**
 * @brief Obtains the length of the decoded data from the length of the Base64 encoded string.
 *
 * This function does not check if the Base64 encoded string contains invalid data.
 * @param[in] encoded Base64 encoded string, if @c NULL a worst case length is returned to accomodate maximum padding.
 * @param[in] encoded_len Length of the Base64 encoded string, not including the @c NULL terminator.
 * @param[out] decoded_len Length of the decoded data.
 * @retval ::bde_error_ok Success.
 * @retval ::bde_error_args Invalid arguments.
 * @retval ::bde_error_encoded_string The Base64 encoded string has an invalid form.
 */
bde_error_t
    bde_base64_decode_length(const bde_enc_t * const encoded, const size_t encoded_len, size_t * const decoded_len);

/**
 * @brief Obtains the decoded data from the Base64 encoded string.
 *
 * This function can decode inplace, it is possible to use the same buffer for the encoded and decoded data.
 * @param[in] encoded Base64 encoded string.
 * @param[in] encoded_len Length of @p encoded, not including the @c NULL terminator.
 * @param[in] decoded_max_len Length of @p decoded.
 * @param[out] decoded Buffer where the decoded data will be written.
 * @param[out] decoded_len Amount of data written to @p decoded, can be @c NULL if not required by caller.
 * @retval ::bde_error_ok Success.
 * @retval ::bde_error_args Invalid arguments.
 * @retval ::bde_error_encoded_string The Base64 encoded string given is not valid.
 */
bde_error_t bde_base64_decode(const bde_enc_t * const encoded,
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

#endif /* BDE_BASE64_DECODE_H */

/******************************************************************************************************END OF FILE*****/
