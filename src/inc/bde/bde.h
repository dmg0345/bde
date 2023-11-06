/**
 ***********************************************************************************************************************
 * @file        bde.h
 * @author      ${PROJECT_AUTHOR} (${PROJECT_CONTACT})
 * @date        ${PROJECT_BUILD_TIMESTAMP_UTC}
 * @version     ${PROJECT_VERSION}
 * @copyright   ${PROJECT_COPYRIGHT}
 ***********************************************************************************************************************
 */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef BDE_H
#define BDE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup bde Base Decoder and Encoder library
 * @{
 */

/** @defgroup bde_defs Definitions */
/** @defgroup bde_papi Public API */
/** @defgroup bde_base64_decode_defs Definitions */
/** @defgroup bde_base64_decode_papi Public API */
/** @defgroup bde_base64_encode_defs Definitions */
/** @defgroup bde_base64_encode_papi Public API */
/** @defgroup bde_base64url_decode_defs Definitions */
/** @defgroup bde_base64url_decode_papi Public API */
/** @defgroup bde_base64url_encode_defs Definitions */
/** @defgroup bde_base64url_encode_papi Public API */
/** @defgroup bde_commons_defs Definitions */
/** @defgroup bde_commons_errors Errors */
/** @defgroup bde_commons_papi Public API */
/** @defgroup bde_base64_iapi_impl Internal API implementation */
/** @defgroup bde_base64_papi_impl Public API implementation */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "bde/other/version.h"
#include "bde/other/commons.h"

// Base64 and Base64URL includes.
#include "bde/base64/encode.h"
#include "bde/base64/decode.h"
#include "bde/base64/url_encode.h"
#include "bde/base64/url_decode.h"

/* Exported types ----------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_defs
 * @{
 */

/**
 * @}
 */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_defs
 * @{
 */

/**
 * @}
 */

/* Exported macro ----------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_papi
 * @{
 */

/**
 * @}
 */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_papi
 * @{
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BDE_H */

/******************************************************************************************************END OF FILE*****/
