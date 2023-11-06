/**
 ***********************************************************************************************************************
 * @file        base64.c
 * @author      ${PROJECT_AUTHOR} (${PROJECT_CONTACT})
 * @date        ${PROJECT_BUILD_TIMESTAMP_UTC}
 * @version     ${PROJECT_VERSION}
 * @copyright   ${PROJECT_COPYRIGHT}
 ***********************************************************************************************************************
 */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "bde/bde.h"

/* Private types -----------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_base64_iapi_impl
 * @{
 */

/**
 * @}
 */

/* Private define ----------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_base64_iapi_impl
 * @{
 */

#define BDE_MODE_BASE64    (0U) /**< Base64 mode for specified operation. */
#define BDE_MODE_BASE64URL (1U) /**< Base64URL mode for specified operation. */

/**
 * @}
 */

/* Private macro -----------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_base64_iapi_impl
 * @{
 */

/**
 * @}
 */

/* Private variables -------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_base64_iapi_impl
 * @{
 */

static const bde_enc_t bde_base64_padding_char = '='; /**< Base64 padding character. */

/** Base64URL alphabet for encoding. */
static const bde_enc_t bde_base64_encode_alphabet_lut[64U] = {
    [0U] = 'A',  [1U] = 'B',  [2U] = 'C',  [3U] = 'D',  [4U] = 'E',  [5U] = 'F',  [6U] = 'G',  [7U] = 'H',
    [8U] = 'I',  [9U] = 'J',  [10U] = 'K', [11U] = 'L', [12U] = 'M', [13U] = 'N', [14U] = 'O', [15U] = 'P',
    [16U] = 'Q', [17U] = 'R', [18U] = 'S', [19U] = 'T', [20U] = 'U', [21U] = 'V', [22U] = 'W', [23U] = 'X',
    [24U] = 'Y', [25U] = 'Z', [26U] = 'a', [27U] = 'b', [28U] = 'c', [29U] = 'd', [30U] = 'e', [31U] = 'f',
    [32U] = 'g', [33U] = 'h', [34U] = 'i', [35U] = 'j', [36U] = 'k', [37U] = 'l', [38U] = 'm', [39U] = 'n',
    [40U] = 'o', [41U] = 'p', [42U] = 'q', [43U] = 'r', [44U] = 's', [45U] = 't', [46U] = 'u', [47U] = 'v',
    [48U] = 'w', [49U] = 'x', [50U] = 'y', [51U] = 'z', [52U] = '0', [53U] = '1', [54U] = '2', [55U] = '3',
    [56U] = '4', [57U] = '5', [58U] = '6', [59U] = '7', [60U] = '8', [61U] = '9', [62U] = '-', [63U] = '_',
};

/** Base64URL alphabet for decoding, note it contains relevant range of [43, 122]. */
static const bde_dec_t bde_base64_decode_alphabet_lut[80U] = {
    [43U - 43U] = 0xFFU, [44U - 43U] = 0xFFU, ['-' - 43U] = 0x3EU, [46U - 43U] = 0xFFU, [47U - 43U] = 0xFFU,
    ['0' - 43U] = 0x34U, ['1' - 43U] = 0x35U, ['2' - 43U] = 0x36U, ['3' - 43U] = 0x37U, ['4' - 43U] = 0x38U,
    ['5' - 43U] = 0x39U, ['6' - 43U] = 0x3AU, ['7' - 43U] = 0x3BU, ['8' - 43U] = 0x3CU, ['9' - 43U] = 0x3DU,
    [58U - 43U] = 0xFFU, [59U - 43U] = 0xFFU, [60U - 43U] = 0xFFU, [61U - 43U] = 0xFFU, [62U - 43U] = 0xFFU,
    [63U - 43U] = 0xFFU, [64U - 43U] = 0xFFU, ['A' - 43U] = 0x00U, ['B' - 43U] = 0x01U, ['C' - 43U] = 0x02U,
    ['D' - 43U] = 0x03U, ['E' - 43U] = 0x04U, ['F' - 43U] = 0x05U, ['G' - 43U] = 0x06U, ['H' - 43U] = 0x07U,
    ['I' - 43U] = 0x08U, ['J' - 43U] = 0x09U, ['K' - 43U] = 0x0AU, ['L' - 43U] = 0x0BU, ['M' - 43U] = 0x0CU,
    ['N' - 43U] = 0x0DU, ['O' - 43U] = 0x0EU, ['P' - 43U] = 0x0FU, ['Q' - 43U] = 0x10U, ['R' - 43U] = 0x11U,
    ['S' - 43U] = 0x12U, ['T' - 43U] = 0x13U, ['U' - 43U] = 0x14U, ['V' - 43U] = 0x15U, ['W' - 43U] = 0x16U,
    ['X' - 43U] = 0x17U, ['Y' - 43U] = 0x18U, ['Z' - 43U] = 0x19U, [91U - 43U] = 0xFFU, [92U - 43U] = 0xFFU,
    [93U - 43U] = 0xFFU, [94U - 43U] = 0xFFU, ['_' - 43U] = 0x3FU, [96U - 43U] = 0xFFU, ['a' - 43U] = 0x1AU,
    ['b' - 43U] = 0x1BU, ['c' - 43U] = 0x1CU, ['d' - 43U] = 0x1DU, ['e' - 43U] = 0x1EU, ['f' - 43U] = 0x1FU,
    ['g' - 43U] = 0x20U, ['h' - 43U] = 0x21U, ['i' - 43U] = 0x22U, ['j' - 43U] = 0x23U, ['k' - 43U] = 0x24U,
    ['l' - 43U] = 0x25U, ['m' - 43U] = 0x26U, ['n' - 43U] = 0x27U, ['o' - 43U] = 0x28U, ['p' - 43U] = 0x29U,
    ['q' - 43U] = 0x2AU, ['r' - 43U] = 0x2BU, ['s' - 43U] = 0x2CU, ['t' - 43U] = 0x2DU, ['u' - 43U] = 0x2EU,
    ['v' - 43U] = 0x2FU, ['w' - 43U] = 0x30U, ['x' - 43U] = 0x31U, ['y' - 43U] = 0x32U, ['z' - 43U] = 0x33U,
};

/**
 * @}
 */

/* Private function prototypes ---------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_base64_iapi_impl
 * @{
 */

/**
 * @brief Gets relevant number of octets related to the encoding of the decoded data.
 * @param[in] decoded_len Length of the decoded data.
 * @param[in] mode Operation mode, one of @ref BDE_MODE_BASE64 or @ref BDE_MODE_BASE64URL.
 * @param[out] decoded_octets_cbl Number of decoded octets that generate complete encoded blocks.
 * @param[out] decoded_octets_lbl Number of octets in the last uncomplete decoded block, if any.
 * @param[out] encoded_octets Number of octets in the resulting encoded string, not including the @c NULL terminator.
 * @retval bde_error_ok Success.
 * @note There are three octets in a decoded block, there are four octets in a encoded block.
 * @note The output arguments are calculated in the order in which they appear in the parameter list of the function.
 */
static bde_error_t bde_encode_lengths(const size_t decoded_len,
                                      const size_t mode,
                                      size_t * const decoded_octets_cbl,
                                      size_t * const decoded_octets_lbl,
                                      size_t * const encoded_octets);

/**
 * @brief Encodes the given element.
 * @param[in] decoded The decoded element to encode.
 * @param[in] mode Operation mode, one of @ref BDE_MODE_BASE64 or @ref BDE_MODE_BASE64URL.
 * @return The encoded element.
 */
static bde_enc_t bde_encode_elem(const bde_dec_t decoded, const size_t mode);

/**
 * @brief Encodes the given decoded data.
 * @param[in] decoded The decoded data to encode.
 * @param[in] decoded_len The length of the decoded data.
 * @param[in] mode Operation mode, one of @ref BDE_MODE_BASE64 or @ref BDE_MODE_BASE64URL.
 * @param[in] encoded_max_len The length of the encoded buffer.
 * @param[out] encoded The buffer where the encoded string will be written.
 * @param[out] encoded_len The length of the encoded string written, not including the @c NULL terminator. Can
 * be @c NULL if not required.
 * @retval bde_error_ok Success.
 * @retval bde_error_buffer_length The buffer is not long enough for the encoded string.
 */
static bde_error_t bde_encode(const bde_dec_t * const decoded,
                              const size_t decoded_len,
                              const size_t mode,
                              const size_t encoded_max_len,
                              bde_enc_t * const encoded,
                              size_t * const encoded_len);

/**
 * @brief Gets relevant number of octets related to the decoding of the encoded string.
 * @param[in] encoded Encoded string.
 * @param[in] encoded_len Length of the encoded string, not including the @c NULL terminator.
 * @param[in] mode Operation mode, one of @ref BDE_MODE_BASE64 or @ref BDE_MODE_BASE64URL.
 * @param[out] encoded_octets_cbl Number of encoded octets that generate complete decoded blocks, not including padding.
 * @param[out] encoded_octets_lbl Number of octets in the last uncomplete decoded block, including padding.
 * @param[out] encoded_octets_pad Number of padding characters in the encoded string.
 * @param[out] decoded_octets Number of octets in the resulting decoded data.
 * @retval bde_error_ok Success.
 * @retval bde_error_encoded_string The encoded string provided is not a valid encoded string in terms of form.
 * @note There are three octets in a decoded block, there are four octets in a encoded block.
 * @note The value returned in @p encoded_octets_lbl must be zero for a valid Base64 encoded string, as the length
 * of a valid Base64 encoded string is always a multiple of four.
 * @note The value returned in @p encoded_octets_pad must be two or less for a valid Base64 encoded string, as it is not
 * possible for a decoded block to have more than two padding characters to make a complete decoded block.
 * @note The decoded octets length is only valid if the two conditions above for @p encoded_octets_lbl and
 * @p encoded_octets_pad are met, this calculation is already performed by the function.
 */
static bde_error_t bde_decode_lengths(const size_t encoded_len,
                                      const bde_enc_t * const encoded,
                                      const size_t mode,
                                      size_t * const encoded_octets_cbl,
                                      size_t * const encoded_octets_lbl,
                                      size_t * const encoded_octets_pad,
                                      size_t * const decoded_octets);

/**
 * @brief Decodes the given encoded elem.
 * @param[in] encoded The decoded element to encode.
 * @param[in] mode Operation mode, one of @ref BDE_MODE_BASE64 or @ref BDE_MODE_BASE64URL.
 * @return The decoded element, or 0xFF if the encoded data is invalid.
 */
static bde_dec_t bde_decode_elem(const bde_enc_t encoded, const size_t mode);

/**
 * @brief Decodes the given encoded string.
 * @param[in] encoded The encoded string.
 * @param[in] encoded_len The length of the encoded string, not including the @c NULL terminator.
 * @param[in] mode Operation mode, one of @ref BDE_MODE_BASE64 or @ref BDE_MODE_BASE64URL.
 * @param[in] decoded_max_len The length of the decoded buffer.
 * @param[out] decoded The buffer where the decoded data will be written to.
 * @param[out] decoded_len The length of the decoded data written to the decoded buffer, can be @c NULL if not required.
 * @retval bde_error_ok Success.
 * @retval bde_error_buffer_length The length of the decoded buffer is not enough for the decoded data.
 * @retval bde_error_encoded_string The encoded string is invalid, it has invalid characters.
 */
static bde_error_t bde_decode(const bde_enc_t * const encoded,
                              const size_t encoded_len,
                              const size_t mode,
                              const size_t decoded_max_len,
                              bde_dec_t * const decoded,
                              size_t * const decoded_len);

/**
 * @}
 */

/* Private functions -------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_base64_iapi_impl
 * @{
 */

/*--------------------------------------------------------------------------------------------------------------------*/
static bde_error_t bde_encode_lengths(const size_t decoded_len,
                                      const size_t mode,
                                      size_t * const decoded_octets_cbl,
                                      size_t * const decoded_octets_lbl,
                                      size_t * const encoded_octets)
{
    // Calculate the number of complete decoded blocks.
    size_t complete_decoded_blocks = decoded_len / 3U;

    // Calculate number of encoded octets that make complete decoded blocks.
    *decoded_octets_cbl = complete_decoded_blocks * 3U;

    // Calculate number of decoded octets that make the last block.
    *decoded_octets_lbl = decoded_len - (*decoded_octets_cbl);

    if (mode == BDE_MODE_BASE64)
    {
        // Calculate length of the resultant Base64 encoded string, not including the terminator.
        *encoded_octets = (complete_decoded_blocks + (((*decoded_octets_lbl) > 0U) ? 1U : 0U)) * 4U;
    }
    else
    {
        // Calculate length of the resultant Base64URL encoded string, not including the terminator.
        *encoded_octets =
            (complete_decoded_blocks * 4U) + ((((*decoded_octets_lbl) > 0U) ? 1U : 0U) * ((*decoded_octets_lbl) + 1U));
    }

    return bde_error_ok;
}

/*--------------------------------------------------------------------------------------------------------------------*/
static bde_enc_t bde_encode_elem(const bde_dec_t decoded, const size_t mode)
{
    bde_enc_t encoded = 0U;

    // If using Base64, handle distinct characters in the alphabet.
    if (mode == BDE_MODE_BASE64)
    {
        switch (decoded)
        {
            case 62U:
            {
                encoded = '+';
            }
            break;

            case 63U:
            {
                encoded = '/';
            }
            break;

            default:
            {
                encoded = bde_base64_encode_alphabet_lut[decoded];
            }
            break;
        }
    }
    else
    {
        encoded = bde_base64_encode_alphabet_lut[decoded];
    }

    return encoded;
}

/*--------------------------------------------------------------------------------------------------------------------*/
static bde_error_t bde_encode(const bde_dec_t * const decoded,
                              const size_t decoded_len,
                              const size_t mode,
                              const size_t encoded_max_len,
                              bde_enc_t * const encoded,
                              size_t * const encoded_len)
{
    // Ensure the encoded string buffer given is big enough.
    size_t noct = 0U;
    size_t loct = 0U;
    size_t ooct = 0U;
    if ((bde_encode_lengths(decoded_len, mode, &noct, &loct, &ooct) != bde_error_ok) || (encoded_max_len < (ooct + 1U)))
    {
        return bde_error_buffer_length;
    }

    // Set pointers and others for reverse encoding.
    bde_enc_t * encoded_r = encoded + ooct;
    const bde_dec_t * decoded_r = decoded + decoded_len - 1U;

    // Write terminator character.
    *(encoded_r--) = '\0';

    // Handle last decoded block, if any, it can be one or two octets of data.
    switch (loct)
    {
        case 2U:
        {
            if (mode == BDE_MODE_BASE64)
            {
                // Write 4th encoded character of current encoded block.
                *(encoded_r--) = bde_base64_padding_char;
            }
            // Move backwards.
            decoded_r -= 2U;
            // Write 3rd encoded character of current encoded block.
            *(encoded_r--) = bde_encode_elem((bde_dec_t)((decoded_r[2U] & 0x0FU) << 2U), mode);
            // Write 2nd encoded character of current encoded block.
            *(encoded_r--) =
                bde_encode_elem((bde_dec_t)(((decoded_r[2U] & 0xF0U) >> 4U) | ((decoded_r[1U] & 0x03U) << 4U)), mode);
            // Write 1st encoded character of current encoded block.
            *(encoded_r--) = bde_encode_elem((decoded_r[1U] & 0xFCU) >> 2U, mode);
        }
        break;

        case 1U:
        {
            if (mode == BDE_MODE_BASE64)
            {
                // Write 4th encoded character of current encoded block.
                *(encoded_r--) = bde_base64_padding_char;
                // Write 3rd encoded character of current encoded block.
                *(encoded_r--) = bde_base64_padding_char;
            }
            // Move backwards.
            decoded_r -= 1U;
            // Write 2nd encoded character of current encoded block.
            *(encoded_r--) = bde_encode_elem((bde_dec_t)((decoded_r[1U] & 0x03U) << 4U), mode);
            // Write 1st encoded character of current encoded block.
            *(encoded_r--) = bde_encode_elem((decoded_r[1U] & 0xFCU) >> 2U, mode);
        }
        break;

        default:
        {
            // Will never get here, only present for MISRA compliance.
        }
        break;
    }

    // Handle remaining decoded blocks, if any, all of which are three octets in size.
    while (decoded_r > decoded)
    {
        // Move backwards.
        decoded_r -= 3U;
        // Write 4th encoded character of current encoded block.
        *(encoded_r--) = bde_encode_elem(decoded_r[3U] & 0x3FU, mode);
        // Write 3rd encoded character of current encoded block.
        *(encoded_r--) =
            bde_encode_elem((bde_dec_t)(((decoded_r[3U] & 0xC0U) >> 6U) | ((decoded_r[2U] & 0x0FU) << 2U)), mode);
        // Write 2nd encoded character of current encoded block.
        *(encoded_r--) =
            bde_encode_elem((bde_dec_t)(((decoded_r[2U] & 0xF0U) >> 4U) | ((decoded_r[1U] & 0x03U) << 4U)), mode);
        // Write 1st encoded character of current encoded block.
        *(encoded_r--) = bde_encode_elem((decoded_r[1U] & 0xFCU) >> 2U, mode);
    }

    // Return encoded string length if requested.
    if (encoded_len != NULL)
    {
        *encoded_len = ooct;
    }

    return bde_error_ok;
}

/*--------------------------------------------------------------------------------------------------------------------*/
static bde_error_t bde_decode_lengths(const size_t encoded_len,
                                      const bde_enc_t * const encoded,
                                      const size_t mode,
                                      size_t * const encoded_octets_cbl,
                                      size_t * const encoded_octets_lbl,
                                      size_t * const encoded_octets_pad,
                                      size_t * const decoded_octets)
{
    // Calculate number of complete encoded blocks.
    size_t complete_encoded_blocks = encoded_len / 4U;

    // Calculate number of octets that create complete blocks.
    *encoded_octets_cbl = complete_encoded_blocks * 4U;

    // Calculate number of characters in last incomplete block, if any.
    *encoded_octets_lbl = encoded_len - (*encoded_octets_cbl);

    *encoded_octets_pad = 0U;
    if (mode == BDE_MODE_BASE64)
    {
        // Get number of padding characters in the Base64 string, if the encoded string was given.
        // Otherwise assume worst case in terms of decoded length, thus no padding characters.
        if (encoded != NULL)
        {
            for (size_t el = encoded_len - 1U; (el > 0U) && (encoded[el] == bde_base64_padding_char); el--)
            {
                (*encoded_octets_pad)++;
            }
        }

        // The number of characters in the last block in a Base64 string can only be zero.
        // The number of padding characters in the last block in a Base64 string can be zero, one or two.
        if ((*encoded_octets_lbl != 0U) || (*encoded_octets_pad > 2U))
        {
            return bde_error_encoded_string;
        }

        // Remove padding from number of useful octets in the encoded Base64 string.
        *encoded_octets_cbl -= *encoded_octets_pad;

        // Calculate number of octets in the decoded output.
        *decoded_octets = (complete_encoded_blocks * 3U) - (*encoded_octets_pad);
    }
    else
    {
        // Set the number of decoded octets from the complete encoded blocks.
        *decoded_octets = complete_encoded_blocks * 3U;

        if (*encoded_octets_lbl > 0U)
        {
            // The number of characters in the last block of a Base64URL string can be zero, two or three.
            if (*encoded_octets_lbl == 1U)
            {
                return bde_error_encoded_string;
            }

            // Calculate number of padding characters in the Base64URL string.
            *encoded_octets_pad = 4U - *encoded_octets_lbl;

            // Add characters in last block to number of useful octets in the encoded Base64URL string.
            *encoded_octets_cbl += *encoded_octets_lbl;

            // Add number of decodec octets from the last complete encoded block.
            *decoded_octets += *encoded_octets_lbl - 1U;
        }
    }

    return bde_error_ok;
}

/*--------------------------------------------------------------------------------------------------------------------*/
static bde_dec_t bde_decode_elem(const bde_enc_t encoded, const size_t mode)
{
    const uint8_t encoded_r = (const uint8_t)encoded;
    bde_dec_t decoded = 0U;

    // Check that the encoded data is within range.
    if ((encoded_r < 43U) || (encoded_r > 122U))
    {
        return 0xFFU;
    }

    // If using Base64, handle distinct characters in the alphabet.
    if (mode == BDE_MODE_BASE64)
    {
        switch (encoded_r)
        {
            case '+':
            {
                decoded = 62U;
            }
            break;

            case '/':
            {
                decoded = 63U;
            }
            break;

            case '_':
            case '-':
            {
                decoded = 0xFFU;
            }
            break;

            default:
            {
                decoded = bde_base64_decode_alphabet_lut[encoded_r - 43U];
            }
            break;
        }
    }
    else
    {
        decoded = bde_base64_decode_alphabet_lut[encoded_r - 43U];
    }

    return decoded;
}

/*--------------------------------------------------------------------------------------------------------------------*/
static bde_error_t bde_decode(const bde_enc_t * const encoded,
                              const size_t encoded_len,
                              const size_t mode,
                              const size_t decoded_max_len,
                              bde_dec_t * const decoded,
                              size_t * const decoded_len)
{
    // Get lengths.
    size_t noct = 0U;
    size_t loct = 0U;
    size_t ooct = 0U;
    size_t poct = 0U;
    bde_error_t res = bde_decode_lengths(encoded_len, encoded, mode, &noct, &loct, &poct, &ooct);
    if (res != bde_error_ok)
    {
        return res;
    }

    // Ensure the decoded data buffer given is big enough for the encoded string.
    if (ooct > decoded_max_len)
    {
        return bde_error_buffer_length;
    }

    // Decode complete blocks, if any.
    const bde_enc_t * encoded_r = encoded;
    bde_dec_t * decoded_r = decoded;
    const bde_enc_t * const encoded_e = encoded + noct;
    while ((encoded_e - encoded_r) >= 4U)
    {
        uint32_t enc =
            (uint32_t)((bde_decode_elem(encoded_r[0U], mode) << 24U) | (bde_decode_elem(encoded_r[1U], mode) << 16U) |
                       (bde_decode_elem(encoded_r[2U], mode) << 8U) | (bde_decode_elem(encoded_r[3U], mode)));
        if ((enc & 0x80808080U) > 0U)
        {
            return bde_error_encoded_string;
        }

        // Handle 1st octet of current decoded block.
        *(decoded_r++) = ((enc & 0x3F000000U) >> 22U) | ((enc & 0x00300000U) >> 20U);
        // Handle 2nd octet of current decoded block.
        *(decoded_r++) = ((enc & 0x000F0000U) >> 12U) | ((enc & 0x0003C00U) >> 10U);
        // Handle 3rd octet of current decoded block.
        *(decoded_r++) = ((enc & 0x00000300U) >> 2U) | (enc & 0x000003FU);
        // Move pointer forwards.
        encoded_r += 4U;
    }

    // Handle last block with the padding, if it exists.
    switch (poct)
    {
        case 2U:
        {
            uint16_t enc =
                (uint16_t)((bde_decode_elem(encoded_r[0U], mode) << 8U) | (bde_decode_elem(encoded_r[1U], mode)));
            if ((enc & 0x8080U) > 0U)
            {
                return bde_error_encoded_string;
            }

            // Handle 1st octet of current decoded block.
            *(decoded_r++) = ((enc & 0x3F00U) >> 6U) | ((enc & 0x0030U) >> 4U);
            // Do not move pointer forwards as it will never be read at this point.
        }
        break;

        case 1U:
        {
            uint32_t enc =
                (uint32_t)((bde_decode_elem(encoded_r[0U], mode) << 16U) |
                           (bde_decode_elem(encoded_r[1U], mode) << 8U) | (bde_decode_elem(encoded_r[2U], mode)));
            if ((enc & 0x808080U) > 0U)
            {
                return bde_error_encoded_string;
            }

            // Handle 1st octet of current decoded block.
            *(decoded_r++) = ((enc & 0x003F0000U) >> 14U) | ((enc & 0x00003000U) >> 12U);
            // Handle 2st octet of current decoded block.
            *(decoded_r++) = ((enc & 0x00000F00U) >> 4U) | ((enc & 0x0000003CU) >> 2U);
            // Do not move pointer forwards as it will never be read at this point.
        }
        break;

        default:
        {
            // Will never get here, present for MISRA compliance.
        }
        break;
    }

    // Store length of decoded data if requested.
    if (decoded_len != NULL)
    {
        *decoded_len = ooct;
    }

    return bde_error_ok;
}

/**
 * @}
 */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/**
 * @addtogroup bde_base64_papi_impl
 * @{
 */

/*--------------------------------------------------------------------------------------------------------------------*/
bde_error_t bde_base64_encode_length(const size_t decoded_len, size_t * const encoded_len)
{
    if ((decoded_len == 0U) || (encoded_len == NULL))
    {
        return bde_error_args;
    }

    return bde_encode_lengths(decoded_len, BDE_MODE_BASE64, encoded_len, encoded_len, encoded_len);
}

/*--------------------------------------------------------------------------------------------------------------------*/
bde_error_t bde_base64_encode(const bde_dec_t * const decoded,
                              const size_t decoded_len,
                              const size_t encoded_max_len,
                              bde_enc_t * const encoded,
                              size_t * const encoded_len)
{
    if ((decoded == NULL) || (decoded_len == 0U) || (encoded_max_len == 0U) || (encoded == NULL))
    {
        return bde_error_args;
    }

    return bde_encode(decoded, decoded_len, BDE_MODE_BASE64, encoded_max_len, encoded, encoded_len);
}

/*--------------------------------------------------------------------------------------------------------------------*/
bde_error_t
    bde_base64_decode_length(const bde_enc_t * const encoded, const size_t encoded_len, size_t * const decoded_len)
{
    if ((encoded_len == 0U) || (decoded_len == NULL))
    {
        return bde_error_args;
    }

    size_t un0 = 0U;
    size_t un1 = 0U;
    size_t un2 = 0U;
    return bde_decode_lengths(encoded_len, encoded, BDE_MODE_BASE64, &un0, &un1, &un2, decoded_len);
}

/*--------------------------------------------------------------------------------------------------------------------*/
bde_error_t bde_base64_decode(const bde_enc_t * const encoded,
                              const size_t encoded_len,
                              const size_t decoded_max_len,
                              bde_dec_t * const decoded,
                              size_t * const decoded_len)
{
    if ((encoded == NULL) || (encoded_len == 0U) || (decoded_max_len == 0U) || (decoded == NULL))
    {
        return bde_error_args;
    }

    return bde_decode(encoded, encoded_len, BDE_MODE_BASE64, decoded_max_len, decoded, decoded_len);
}

/*--------------------------------------------------------------------------------------------------------------------*/
bde_error_t bde_base64url_encode_length(const size_t decoded_len, size_t * const encoded_len)
{
    if ((decoded_len == 0U) || (encoded_len == NULL))
    {
        return bde_error_args;
    }

    return bde_encode_lengths(decoded_len, BDE_MODE_BASE64URL, encoded_len, encoded_len, encoded_len);
}

/*--------------------------------------------------------------------------------------------------------------------*/
bde_error_t bde_base64url_encode(const bde_dec_t * const decoded,
                                 const size_t decoded_len,
                                 const size_t encoded_max_len,
                                 bde_enc_t * const encoded,
                                 size_t * const encoded_len)
{
    if ((decoded == NULL) || (decoded_len == 0U) || (encoded_max_len == 0U) || (encoded == NULL))
    {
        return bde_error_args;
    }

    return bde_encode(decoded, decoded_len, BDE_MODE_BASE64URL, encoded_max_len, encoded, encoded_len);
}

/*--------------------------------------------------------------------------------------------------------------------*/
bde_error_t bde_base64url_decode_length(const size_t encoded_len, size_t * const decoded_len)
{
    if ((encoded_len == 0U) || (decoded_len == NULL))
    {
        return bde_error_args;
    }

    size_t un0 = 0U;
    size_t un1 = 0U;
    size_t un2 = 0U;
    return bde_decode_lengths(encoded_len, NULL, BDE_MODE_BASE64URL, &un0, &un1, &un2, decoded_len);
}

/*--------------------------------------------------------------------------------------------------------------------*/
bde_error_t bde_base64url_decode(const bde_enc_t * const encoded,
                                 const size_t encoded_len,
                                 const size_t decoded_max_len,
                                 bde_dec_t * const decoded,
                                 size_t * const decoded_len)
{
    if ((encoded == NULL) || (encoded_len == 0U) || (decoded_max_len == 0U) || (decoded == NULL))
    {
        return bde_error_args;
    }

    return bde_decode(encoded, encoded_len, BDE_MODE_BASE64URL, decoded_max_len, decoded, decoded_len);
}

/**
 * @}
 */

/******************************************************************************************************END OF FILE*****/
