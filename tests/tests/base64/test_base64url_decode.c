/**
 ***********************************************************************************************************************
 * @file        test_base64url_decode.c
 * @author      ${PROJECT_AUTHOR} (${PROJECT_CONTACT})
 * @date        ${PROJECT_BUILD_TIMESTAMP_UTC}
 * @version     ${PROJECT_VERSION}
 * @copyright   ${PROJECT_COPYRIGHT}
 ***********************************************************************************************************************
 */

/** @defgroup bde_base64url_decode_tests Tests */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "cmocka_defs.h"
#include "samples/samples.h"
#include "bde/bde.h"

/* Private types -----------------------------------------------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------------------------------------------*/
/* Private macro -----------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/
static sample_test_data_t tds; /**< Test data structure. */

/* Private function prototypes ---------------------------------------------------------------------------------------*/
/** Suite setup function. */
static int setup(void ** state);
/** Suite teardown function. */
static int teardown(void ** state);

/**
 * @addtogroup bde_base64url_decode_tests
 * @{
 */

/** Tests invalid arguments when performing a decoding of a Base64URL string. */
static void test_base64url_decode_invalid_args(void ** state);
/** Tests invalid Base64URL strings when decoding. */
static void test_base64url_decode_invalid_encoded_strings(void ** state);
/** Tests invalid buffer lengths for the decoding buffer when decoding. */
static void test_base64url_decode_invalid_buffer_length(void ** state);
/** Tests decoding without querying the decoded length. */
static void test_base64url_decode_ignored_buffer_length(void ** state);
/** Tests decoding on two separate buffers, one for encoding and another for decoding. */
static void test_base64url_decode_two_separate_buffers(void ** state);
/** Tests decoding on a single in-place buffer, used for both encoding and decoding. */
static void test_base64url_decode_single_inplace_buffers(void ** state);
/** Tests obtaining the length of a decode with invalid arguments. */
static void test_base64url_decode_length_invalid_args(void ** state);
/** Tests obtaining the length of a decode with invalid Base64URL encoded strings. */
static void test_base64url_decode_length_invalid_encoded_strings(void ** state);
/** Tests obtaining the length of a decode for the samples. */
static void test_base64url_decode_length_samples(void ** state);

/**
 * @}
 */

/* Private functions -------------------------------------------------------------------------------------------------*/
static int setup(void ** state)
{
    (void)state;
    (void)memset(tds.decoded, 0U, sizeof(tds.decoded));
    tds.decoded_len = ARRAY_DIM(tds.decoded);
    (void)memset(tds.encoded, 0U, sizeof(tds.encoded));
    tds.encoded_len = ARRAY_DIM(tds.encoded);

    return CMOCKA_OK;
}

/*--------------------------------------------------------------------------------------------------------------------*/
static int teardown(void ** state)
{
    (void)state;

    return CMOCKA_OK;
}

/*--------------------------------------------------------------------------------------------------------------------*/
static void test_base64url_decode_invalid_args(void ** state)
{
    (void)state;
    bde_error_t error = bde_error_ok;

    // Check that error is returned when the Base64 encoded string is not valid.
    error = bde_base64url_decode(NULL, tds.encoded_len, tds.decoded_len, tds.decoded, &tds.decoded_len);
    assert_int_equal(bde_error_args, error);

    // Check that error is returned when the length of the Base64 encoded string is not valid.
    error = bde_base64url_decode(tds.encoded, 0U, tds.decoded_len, tds.decoded, &tds.decoded_len);
    assert_int_equal(bde_error_args, error);

    // Check that error is returned when the maximum length of the decoded data buffer is not valid.
    error = bde_base64url_decode(tds.encoded, tds.encoded_len, 0U, tds.decoded, &tds.decoded_len);
    assert_int_equal(bde_error_args, error);

    // Check that error is returned when the decoded data buffer is not valid.
    error = bde_base64url_decode(tds.encoded, tds.encoded_len, tds.decoded_len, NULL, &tds.decoded_len);
    assert_int_equal(bde_error_args, error);
}

/*--------------------------------------------------------------------------------------------------------------------*/
static void test_base64url_decode_invalid_encoded_strings(void ** state)
{
    (void)state;
    bde_error_t error = bde_error_ok;

    error = bde_base64url_decode("Q", 1U, tds.decoded_len, tds.decoded, &tds.decoded_len);
    assert_int_equal(bde_error_encoded_string, error);

    error = bde_base64url_decode("QQQQQ", 5U, tds.decoded_len, tds.decoded, &tds.decoded_len);
    assert_int_equal(bde_error_encoded_string, error);

    error = bde_base64url_decode("=", 1U, tds.decoded_len, tds.decoded, &tds.decoded_len);
    assert_int_equal(bde_error_encoded_string, error);

    error = bde_base64url_decode("==", 2U, tds.decoded_len, tds.decoded, &tds.decoded_len);
    assert_int_equal(bde_error_encoded_string, error);

    error = bde_base64url_decode("===", 3U, tds.decoded_len, tds.decoded, &tds.decoded_len);
    assert_int_equal(bde_error_encoded_string, error);

    error = bde_base64url_decode("====", 4U, tds.decoded_len, tds.decoded, &tds.decoded_len);
    assert_int_equal(bde_error_encoded_string, error);

    error = bde_base64url_decode("Q===", 4U, tds.decoded_len, tds.decoded, &tds.decoded_len);
    assert_int_equal(bde_error_encoded_string, error);

    error = bde_base64url_decode("QQQQ=", 5U, tds.decoded_len, tds.decoded, &tds.decoded_len);
    assert_int_equal(bde_error_encoded_string, error);

    error = bde_base64url_decode("QQQQ==", 6U, tds.decoded_len, tds.decoded, &tds.decoded_len);
    assert_int_equal(bde_error_encoded_string, error);

    error = bde_base64url_decode("QQQQ===", 7U, tds.decoded_len, tds.decoded, &tds.decoded_len);
    assert_int_equal(bde_error_encoded_string, error);

    error = bde_base64url_decode("QQQQ====", 8U, tds.decoded_len, tds.decoded, &tds.decoded_len);
    assert_int_equal(bde_error_encoded_string, error);

    error = bde_base64url_decode("QQQQQQQ/", 8U, tds.decoded_len, tds.decoded, &tds.decoded_len);
    assert_int_equal(bde_error_encoded_string, error);

    error = bde_base64url_decode("QQQQQQ/Q", 8U, tds.decoded_len, tds.decoded, &tds.decoded_len);
    assert_int_equal(bde_error_encoded_string, error);

    error = bde_base64url_decode("QQQQQ/QQ", 8U, tds.decoded_len, tds.decoded, &tds.decoded_len);
    assert_int_equal(bde_error_encoded_string, error);

    error = bde_base64url_decode("QQQQQQQ+", 8U, tds.decoded_len, tds.decoded, &tds.decoded_len);
    assert_int_equal(bde_error_encoded_string, error);

    error = bde_base64url_decode("QQQQQQ+Q", 8U, tds.decoded_len, tds.decoded, &tds.decoded_len);
    assert_int_equal(bde_error_encoded_string, error);

    error = bde_base64url_decode("QQQQQ+QQ", 8U, tds.decoded_len, tds.decoded, &tds.decoded_len);
    assert_int_equal(bde_error_encoded_string, error);

    error = bde_base64url_decode("*#$%", 4U, tds.decoded_len, tds.decoded, &tds.decoded_len);
    assert_int_equal(bde_error_encoded_string, error);
}

/*--------------------------------------------------------------------------------------------------------------------*/
static void test_base64url_decode_invalid_buffer_length(void ** state)
{
    (void)state;
    bde_error_t error = bde_error_ok;
    const sample_t * const sp = sample_get(0U);

    // Check that an error is returned when the decoded data buffer is not big enough.
    error = bde_base64url_decode(sp->encoded_base64url,
                                 sp->encoded_base64url_len,
                                 sp->decoded_len - 1U,
                                 tds.decoded,
                                 &tds.decoded_len);
    assert_int_equal(bde_error_buffer_length, error);
}

/*--------------------------------------------------------------------------------------------------------------------*/
static void test_base64url_decode_ignored_buffer_length(void ** state)
{
    (void)state;
    bde_error_t error = bde_error_ok;
    const sample_t * const sp = sample_get(0U);

    // Check that the decoding works the same when the caller ignores the decoded data length argument.
    error = bde_base64url_decode(sp->encoded_base64url, sp->encoded_base64url_len, sp->decoded_len, tds.decoded, NULL);
    assert_int_equal(bde_error_ok, error);
    assert_memory_equal(sp->decoded, tds.decoded, sp->decoded_len);
    assert_int_equal(tds.decoded[sp->decoded_len], 0U);
}

/*--------------------------------------------------------------------------------------------------------------------*/
static void test_base64url_decode_two_separate_buffers(void ** state)
{
    (void)state;
    bde_error_t error = bde_error_ok;
    const size_t sample_count = sample_get_count();

    // Check that the decoding of the samples is correct when using two buffers.
    for (size_t i = 0U; i < sample_count; i++)
    {
        // Get sample.
        const sample_t * const sp = sample_get(i);
        // Decode.
        error = bde_base64url_decode(sp->encoded_base64url,
                                     sp->encoded_base64url_len,
                                     sp->decoded_len,
                                     tds.decoded,
                                     &tds.decoded_len);
        assert_int_equal(bde_error_ok, error);
        assert_int_equal(sp->decoded_len, tds.decoded_len);
        assert_memory_equal(sp->decoded, tds.decoded, tds.decoded_len);
        assert_int_equal(tds.decoded[sp->decoded_len], 0U);
        (void)memset(tds.decoded, 0U, sizeof(tds.decoded));
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/
static void test_base64url_decode_single_inplace_buffers(void ** state)
{
    (void)state;
    bde_error_t error = bde_error_ok;
    const size_t sample_count = sample_get_count();

    // Check that the decoding of the samples is correct when using one buffer.
    for (size_t i = 0U; i < sample_count; i++)
    {
        // Get sample.
        const sample_t * const sp = sample_get(i);
        // Copy to encoded buffer for in-place.
        tds.encoded_len = sp->encoded_base64url_len;
        (void)memset(tds.encoded, 0U, sizeof(tds.encoded));
        (void)memcpy(tds.encoded, sp->encoded_base64url, sp->encoded_base64url_len * sizeof(bde_enc_t));
        // Decode.
        error = bde_base64url_decode(tds.encoded,
                                     tds.encoded_len,
                                     sp->decoded_len,
                                     (bde_dec_t * const)tds.encoded,
                                     &tds.encoded_len);
        assert_int_equal(bde_error_ok, error);
        assert_int_equal(sp->decoded_len, tds.encoded_len);
        assert_memory_equal(sp->decoded, tds.encoded, tds.encoded_len);
        assert_int_equal(tds.encoded[sp->decoded_len], sp->encoded_base64url[sp->decoded_len]);
        (void)memset(tds.encoded, 0U, sizeof(tds.encoded));
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/
static void test_base64url_decode_length_invalid_args(void ** state)
{
    (void)state;
    bde_error_t error = bde_error_ok;
    const sample_t * const sp = sample_get(0U);

    // Check that an error is returned when the encoded length is not valid.
    error = bde_base64url_decode_length(0U, &tds.decoded_len);
    assert_int_equal(bde_error_args, error);

    // Check that an error is returned when the decoded length is not valid.
    error = bde_base64url_decode_length(sp->encoded_base64url_len, NULL);
    assert_int_equal(bde_error_args, error);
}

/*--------------------------------------------------------------------------------------------------------------------*/
static void test_base64url_decode_length_invalid_encoded_strings(void ** state)
{
    (void)state;
    bde_error_t error = bde_error_ok;

    error = bde_base64url_decode_length(1U, &tds.decoded_len);
    assert_int_equal(bde_error_encoded_string, error);

    error = bde_base64url_decode_length(5U, &tds.decoded_len);
    assert_int_equal(bde_error_encoded_string, error);

    error = bde_base64url_decode_length(9U, &tds.decoded_len);
    assert_int_equal(bde_error_encoded_string, error);

    error = bde_base64url_decode_length(13U, &tds.decoded_len);
    assert_int_equal(bde_error_encoded_string, error);
}

/*--------------------------------------------------------------------------------------------------------------------*/
static void test_base64url_decode_length_samples(void ** state)
{
    (void)state;
    bde_error_t error = bde_error_ok;
    const size_t sample_count = sample_get_count();

    for (size_t i = 0U; i < sample_count; i++)
    {
        // Get sample.
        const sample_t * const sp = sample_get(i);
        // Decode.
        error = bde_base64url_decode_length(sp->encoded_base64url_len, &tds.decoded_len);
        assert_int_equal(bde_error_ok, error);
        assert_int_equal(sp->decoded_len, tds.decoded_len);
    }
}

/* Exported functions ------------------------------------------------------------------------------------------------*/
/**
 * @brief Test runner for this suite of tests.
 * @return The result of the test runner.
 */
int main(void)
{
    // Initialize CMocka.
    cmocka_init();

    // The table with the tests.
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(test_base64url_decode_invalid_args, setup, teardown),
        cmocka_unit_test_setup_teardown(test_base64url_decode_invalid_encoded_strings, setup, teardown),
        cmocka_unit_test_setup_teardown(test_base64url_decode_invalid_buffer_length, setup, teardown),
        cmocka_unit_test_setup_teardown(test_base64url_decode_ignored_buffer_length, setup, teardown),
        cmocka_unit_test_setup_teardown(test_base64url_decode_two_separate_buffers, setup, teardown),
        cmocka_unit_test_setup_teardown(test_base64url_decode_single_inplace_buffers, setup, teardown),
        cmocka_unit_test_setup_teardown(test_base64url_decode_length_invalid_args, setup, teardown),
        cmocka_unit_test_setup_teardown(test_base64url_decode_length_invalid_encoded_strings, setup, teardown),
        cmocka_unit_test_setup_teardown(test_base64url_decode_length_samples, setup, teardown),
    };

    // Execute the test runner.
    return cmocka_run_group_tests_name("base64url_decode", tests, NULL, NULL);
}

/******************************************************************************************************END OF FILE*****/
