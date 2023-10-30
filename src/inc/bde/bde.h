/**
 ***********************************************************************************************************************
 * @file        bde.h
 * @author      Diego Martínez García (dmg0345@gmail.com)
 * @date        30-10-2023 21:48:22 (UTC)
 * @version     1.0.2
 * @copyright   github.com/dmg0345/bde/blob/master/LICENSE
 ***********************************************************************************************************************
 */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef BDE_H
#define BDE_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup bde Base Decoder and Encoder library
 * @{
 */

/** @defgroup bde_defs Definitions */
/** @defgroup bde_papi Public API */

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
