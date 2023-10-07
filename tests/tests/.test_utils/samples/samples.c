/**
 ***********************************************************************************************************************
 * @file        samples.c
 * @author      ${PROJECT_AUTHOR} (${PROJECT_CONTACT})
 * @date        ${PROJECT_BUILD_TIMESTAMP_UTC}
 * @version     ${PROJECT_VERSION}
 * @copyright   ${PROJECT_COPYRIGHT}
 ***********************************************************************************************************************
 */

/** @defgroup bde_samples_iapi_impl Internal API implementation */
/** @defgroup bde_samples_papi_impl Public API implementation */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "cmocka_defs.h"
#include "samples.h"

/* Private types -----------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_samples_iapi_impl
 * @{
 */

/**
 * @}
 */

/* Private define ----------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_samples_iapi_impl
 * @{
 */

/**
 * @}
 */

/* Private macro -----------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_samples_iapi_impl
 * @{
 */

/**
 * @}
 */

/* Private variables -------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_samples_iapi_impl
 * @{
 */

/** Sample 00: 'Hello World!'. */
/** @{ */
static const bde_dec_t sample00_data[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
static const bde_enc_t sample00_base64[] = "SGVsbG8gV29ybGQh";
static const bde_enc_t sample00_base64url[] = "SGVsbG8gV29ybGQh";
/** @} */

/** Sample 01: 'H'. */
/** @{ */
static const bde_dec_t sample01_data[] = {'H'};
static const bde_enc_t sample01_base64[] = "SA==";
static const bde_enc_t sample01_base64url[] = "SA";
/** @} */

/** Sample 02: 'He'. */
/** @{ */
static const bde_dec_t sample02_data[] = {'H', 'e'};
static const bde_enc_t sample02_base64[] = "SGU=";
static const bde_enc_t sample02_base64url[] = "SGU";
/** @} */

/** Sample 03: 'Hel'. */
/** @{ */
static const bde_dec_t sample03_data[] = {'H', 'e', 'l'};
static const bde_enc_t sample03_base64[] = "SGVs";
static const bde_enc_t sample03_base64url[] = "SGVs";
/** @} */

/** Sample 04: 'Hell'. */
/** @{ */
static const bde_dec_t sample04_data[] = {'H', 'e', 'l', 'l'};
static const bde_enc_t sample04_base64[] = "SGVsbA==";
static const bde_enc_t sample04_base64url[] = "SGVsbA";
/** @} */

/** Sample 05: 'Hello'. */
/** @{ */
static const bde_dec_t sample05_data[] = {'H', 'e', 'l', 'l', 'o'};
static const bde_enc_t sample05_base64[] = "SGVsbG8=";
static const bde_enc_t sample05_base64url[] = "SGVsbG8";
/** @} */

/** Sample 06: no printable characters. */
/** @{ */
static const bde_dec_t sample06_data[] = {0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU};
static const bde_enc_t sample06_base64[] = "qqqqqqqqqqqqqg==";
static const bde_enc_t sample06_base64url[] = "qqqqqqqqqqqqqg";
/** @} */

/** Sample 07: no printable characters. */
/** @{ */
static const bde_dec_t sample07_data[] = {0xAAU};
static const bde_enc_t sample07_base64[] = "qg==";
static const bde_enc_t sample07_base64url[] = "qg";
/** @} */

/** Sample 08: no printable characters. */
/** @{ */
static const bde_dec_t sample08_data[] = {0xAAU, 0xAAU};
static const bde_enc_t sample08_base64[] = "qqo=";
static const bde_enc_t sample08_base64url[] = "qqo";
/** @} */

/** Sample 09: no printable characters. */
/** @{ */
static const bde_dec_t sample09_data[] = {0xAAU, 0xAAU, 0xAAU};
static const bde_enc_t sample09_base64[] = "qqqq";
static const bde_enc_t sample09_base64url[] = "qqqq";
/** @} */

/** Sample 10: no printable characters. */
/** @{ */
static const bde_dec_t sample10_data[] = {0xAAU, 0xAAU, 0xAAU, 0xAAU};
static const bde_enc_t sample10_base64[] = "qqqqqg==";
static const bde_enc_t sample10_base64url[] = "qqqqqg";
/** @} */

/** Sample 11: no printable characters. */
/** @{ */
static const bde_dec_t sample11_data[] = {0xFBU, 0xFFU, 0xBFU, 0xFBU, 0xFFU, 0xBFU};
static const bde_enc_t sample11_base64[] = "+/+/+/+/";
static const bde_enc_t sample11_base64url[] = "-_-_-_-_";
/** @} */

/** Sample 12: 'Лорем ипсумм'. */
/** @{ */
static const bde_dec_t sample12_data[] = {
    0xD0U, 0x9BU, 0xD0U, 0xBEU, 0xD1U, 0x80U, 0xD0U, 0xB5U, 0xD0U, 0xBCU, 0x20U, 0xD0U,
    0xB8U, 0xD0U, 0xBFU, 0xD1U, 0x81U, 0xD1U, 0x83U, 0xD0U, 0xBCU, 0xD0U, 0xBCU,
};
static const bde_enc_t sample12_base64[] = "0JvQvtGA0LXQvCDQuNC/0YHRg9C80Lw=";
static const bde_enc_t sample12_base64url[] = "0JvQvtGA0LXQvCDQuNC_0YHRg9C80Lw";
/** @} */

/** Collection of samples. */
static const sample_t samples[] = {
    {
     .decoded = sample00_data,
     .decoded_len = ARRAY_DIM(sample00_data),
     .encoded_base64 = sample00_base64,
     .encoded_base64_len = ARRAY_DIM(sample00_base64) - 1UL,
     .encoded_base64url = sample00_base64url,
     .encoded_base64url_len = ARRAY_DIM(sample00_base64url) - 1U,
     },
    {
     .decoded = sample01_data,
     .decoded_len = ARRAY_DIM(sample01_data),
     .encoded_base64 = sample01_base64,
     .encoded_base64_len = ARRAY_DIM(sample01_base64) - 1UL,
     .encoded_base64url = sample01_base64url,
     .encoded_base64url_len = ARRAY_DIM(sample01_base64url) - 1U,
     },
    {
     .decoded = sample02_data,
     .decoded_len = ARRAY_DIM(sample02_data),
     .encoded_base64 = sample02_base64,
     .encoded_base64_len = ARRAY_DIM(sample02_base64) - 1UL,
     .encoded_base64url = sample02_base64url,
     .encoded_base64url_len = ARRAY_DIM(sample02_base64url) - 1U,
     },
    {
     .decoded = sample03_data,
     .decoded_len = ARRAY_DIM(sample03_data),
     .encoded_base64 = sample03_base64,
     .encoded_base64_len = ARRAY_DIM(sample03_base64) - 1UL,
     .encoded_base64url = sample03_base64url,
     .encoded_base64url_len = ARRAY_DIM(sample03_base64url) - 1U,
     },
    {
     .decoded = sample04_data,
     .decoded_len = ARRAY_DIM(sample04_data),
     .encoded_base64 = sample04_base64,
     .encoded_base64_len = ARRAY_DIM(sample04_base64) - 1UL,
     .encoded_base64url = sample04_base64url,
     .encoded_base64url_len = ARRAY_DIM(sample04_base64url) - 1U,
     },
    {
     .decoded = sample05_data,
     .decoded_len = ARRAY_DIM(sample05_data),
     .encoded_base64 = sample05_base64,
     .encoded_base64_len = ARRAY_DIM(sample05_base64) - 1UL,
     .encoded_base64url = sample05_base64url,
     .encoded_base64url_len = ARRAY_DIM(sample05_base64url) - 1U,
     },
    {
     .decoded = sample06_data,
     .decoded_len = ARRAY_DIM(sample06_data),
     .encoded_base64 = sample06_base64,
     .encoded_base64_len = ARRAY_DIM(sample06_base64) - 1UL,
     .encoded_base64url = sample06_base64url,
     .encoded_base64url_len = ARRAY_DIM(sample06_base64url) - 1U,
     },
    {
     .decoded = sample07_data,
     .decoded_len = ARRAY_DIM(sample07_data),
     .encoded_base64 = sample07_base64,
     .encoded_base64_len = ARRAY_DIM(sample07_base64) - 1UL,
     .encoded_base64url = sample07_base64url,
     .encoded_base64url_len = ARRAY_DIM(sample07_base64url) - 1U,
     },
    {
     .decoded = sample08_data,
     .decoded_len = ARRAY_DIM(sample08_data),
     .encoded_base64 = sample08_base64,
     .encoded_base64_len = ARRAY_DIM(sample08_base64) - 1UL,
     .encoded_base64url = sample08_base64url,
     .encoded_base64url_len = ARRAY_DIM(sample08_base64url) - 1U,
     },
    {
     .decoded = sample09_data,
     .decoded_len = ARRAY_DIM(sample09_data),
     .encoded_base64 = sample09_base64,
     .encoded_base64_len = ARRAY_DIM(sample09_base64) - 1UL,
     .encoded_base64url = sample09_base64url,
     .encoded_base64url_len = ARRAY_DIM(sample09_base64url) - 1U,
     },
    {
     .decoded = sample10_data,
     .decoded_len = ARRAY_DIM(sample10_data),
     .encoded_base64 = sample10_base64,
     .encoded_base64_len = ARRAY_DIM(sample10_base64) - 1UL,
     .encoded_base64url = sample10_base64url,
     .encoded_base64url_len = ARRAY_DIM(sample10_base64url) - 1U,
     },
    {
     .decoded = sample11_data,
     .decoded_len = ARRAY_DIM(sample11_data),
     .encoded_base64 = sample11_base64,
     .encoded_base64_len = ARRAY_DIM(sample11_base64) - 1UL,
     .encoded_base64url = sample11_base64url,
     .encoded_base64url_len = ARRAY_DIM(sample11_base64url) - 1U,
     },
    {
     .decoded = sample12_data,
     .decoded_len = ARRAY_DIM(sample12_data),
     .encoded_base64 = sample12_base64,
     .encoded_base64_len = ARRAY_DIM(sample12_base64) - 1UL,
     .encoded_base64url = sample12_base64url,
     .encoded_base64url_len = ARRAY_DIM(sample12_base64url) - 1U,
     }
};

/**
 * @}
 */

/* Private function prototypes ---------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_samples_iapi_impl
 * @{
 */

/**
 * @}
 */

/* Private functions -------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_samples_iapi_impl
 * @{
 */

/**
 * @}
 */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_samples_papi_impl
 * @{
 */

size_t sample_get_count(void)
{
    return ARRAY_DIM(samples);
}

/*--------------------------------------------------------------------------------------------------------------------*/
const sample_t * sample_get(const size_t index)
{
    if (index >= ARRAY_DIM(samples))
    {
        return NULL;
    }

    return &samples[index];
}

/**
 * @}
 */

/******************************************************************************************************END OF FILE*****/
