/**
 ***********************************************************************************************************************
 * @file        samples.h
 * @author      Diego Martínez García (dmg0345@gmail.com)
 * @date        07-10-2023 23:44:17 (UTC)
 * @version     1.0.0
 * @copyright   github.com/dmg0345/bde/blob/master/LICENSE
 ***********************************************************************************************************************
 */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef SAMPLES_H
#define SAMPLES_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @defgroup bde_samples_defs Definitions */
/** @defgroup bde_samples_errors Errors */
/** @defgroup bde_samples_papi Public API */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "bde/other/commons.h"

/* Exported types ----------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_samples_defs
 * @{
 */

/** Sample definition. */
typedef struct
{
    const bde_dec_t * decoded; /**< Decoded data, the sample. */
    size_t decoded_len; /**< Length of the decoded data. */
    const bde_enc_t * encoded_base64; /**< Base64 encoded data, @c NULL terminated. */
    size_t encoded_base64_len; /**< Length of the Base64 encoded data, excluding @c NULL terminator. */
    const bde_enc_t * encoded_base64url; /**< Base64URL encoded data, @c NULL terminated. */
    size_t encoded_base64url_len; /**< Length of the Base64URL encoded data, excluding @c NULL terminator. */
} sample_t;

/** Sample test data definition. */
typedef struct
{
    bde_dec_t decoded[48U]; /**< Buffer for any decoded / encoded sample. */
    size_t decoded_len; /**< Length of relevant data in the decoded buffer. */
    bde_enc_t encoded[48U]; /**< Buffer for any decoded / encoded sample, including @c NULL terminator. */
    size_t encoded_len; /**< Length of relevant data in the encoded buffer. */
} sample_test_data_t;

/**
 * @}
 */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_samples_defs
 * @{
 */

/**
 * @}
 */

/**
 * @addtogroup bde_samples_errors
 * @{
 */

/**
 * @}
 */

/* Exported macro ----------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_samples_papi
 * @{
 */

/**
 * @}
 */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_samples_papi
 * @{
 */

/**
 * @brief Obtains the number of samples.
 * @return The number of samples available.
 */
size_t sample_get_count(void);

/**
 * @brief Obtains the sample specified.
 * @param[in] index Sample to obtain, a value from zero to sample_get_count().
 * @return A pointer to a valid sample, or @c NULL if the sample does not exist for @p index specified.
 */
const sample_t * sample_get(const size_t index);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SAMPLES_H */

/******************************************************************************************************END OF FILE*****/
