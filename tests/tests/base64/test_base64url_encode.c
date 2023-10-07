/**
 ***********************************************************************************************************************
 * @file        test_base64url_encode.c
 * @author      ${PROJECT_AUTHOR} (${PROJECT_CONTACT})
 * @date        ${PROJECT_BUILD_TIMESTAMP_UTC}
 * @version     ${PROJECT_VERSION} (${PROJECT_VCS_HASH})
 * @copyright   ${PROJECT_COPYRIGHT}
 ***********************************************************************************************************************
 */

/** @defgroup bde_base64url_encode_tests Tests */

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
/**
 * @brief Suite setup function.
 */
static int setup(void ** state);

/**
 * @brief Suite teardown function.
 */
static int teardown(void ** state);

/**
 * @addtogroup bde_base64url_encode_tests
 * @{
 */

/**
 * @brief Tests invalid arguments when performing a encoding to a Base64URL string.
 */
static void test_base64url_encode_invalid_args(void ** state);

/**
 * @brief Tests invalid buffer lengths for the encoding buffer when encoding.
 */
static void test_base64url_encode_invalid_buffer_length(void ** state);

/**
 * @brief Tests encoding without querying the encoded length.
 */
static void test_base64url_encode_ignored_buffer_length(void ** state);

/**
 * @brief Tests encoding on two separate buffers, one for encoding and another for decoding.
 */
static void test_base64url_encode_two_separate_buffers(void ** state);

/**
 * @brief Tests encoding on a single in-place buffer, used for both encoding and decoding.
 */
static void test_base64url_encode_single_inplace_buffers(void ** state);

/**
 * @brief Tests obtaining the length of a encode with invalid arguments.
 */
static void test_base64url_encode_length_invalid_args(void ** state);

/**
 * @brief Tests obtaining the length of a encode for the samples.
 */
static void test_base64url_encode_length_samples(void ** state);

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
static void test_base64url_encode_invalid_args(void ** state)
{
    (void)state;
    bde_error_t error = bde_error_ok;

    // Check that error is returned when the decoded buffer given is not valid.
    error = bde_base64url_encode(NULL, tds.decoded_len, tds.encoded_len, tds.encoded, &tds.encoded_len);
    assert_int_equal(bde_error_args, error);

    // Check that error is returned when the decoded buffer length given is not valid.
    error = bde_base64url_encode(tds.decoded, 0U, tds.encoded_len, tds.encoded, &tds.encoded_len);
    assert_int_equal(bde_error_args, error);

    // Check that error is returned when the encoded buffer maximum length given is not valid.
    error = bde_base64url_encode(tds.decoded, tds.decoded_len, 0U, tds.encoded, &tds.encoded_len);
    assert_int_equal(bde_error_args, error);

    // Check that error is returned when the encoded buffer given is not valid.
    error = bde_base64url_encode(tds.decoded, tds.decoded_len, tds.encoded_len, NULL, &tds.encoded_len);
    assert_int_equal(bde_error_args, error);
}

/*--------------------------------------------------------------------------------------------------------------------*/
static void test_base64url_encode_invalid_buffer_length(void ** state)
{
    (void)state;
    bde_error_t error = bde_error_ok;
    const sample_t * const sp = sample_get(0U);

    // Check that an error is returned when the encoded buffer is not long enough.
    error =
        bde_base64url_encode(sp->decoded, sp->decoded_len, sp->encoded_base64url_len, tds.encoded, &tds.encoded_len);
    assert_int_equal(bde_error_buffer_length, error);
}

/*--------------------------------------------------------------------------------------------------------------------*/
static void test_base64url_encode_ignored_buffer_length(void ** state)
{
    (void)state;
    bde_error_t error = bde_error_ok;
    const sample_t * const sp = sample_get(0U);

    // Check that the encoding works the same when the caller ignores the encoded length argument.
    error = bde_base64url_encode(sp->decoded, sp->decoded_len, tds.encoded_len, tds.encoded, NULL);
    assert_int_equal(bde_error_ok, error);
    assert_string_equal(sp->encoded_base64url, tds.encoded);
}

/*--------------------------------------------------------------------------------------------------------------------*/
static void test_base64url_encode_two_separate_buffers(void ** state)
{
    (void)state;
    bde_error_t error = bde_error_ok;
    const size_t sample_count = sample_get_count();

    // Check that the encoding of the sample is correct when using two buffers.
    for (size_t i = 0U; i < sample_count; i++)
    {
        // Get sample.
        const sample_t * const sp = sample_get(i);
        // Encode.
        error = bde_base64url_encode(sp->decoded,
                                     sp->decoded_len,
                                     sp->encoded_base64url_len + 1U,
                                     tds.encoded,
                                     &tds.encoded_len);
        assert_int_equal(bde_error_ok, error);
        assert_int_equal(sp->encoded_base64url_len, tds.encoded_len);
        assert_string_equal(sp->encoded_base64url, tds.encoded);
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/
static void test_base64url_encode_single_inplace_buffers(void ** state)
{
    (void)state;
    bde_error_t error = bde_error_ok;
    const size_t sample_count = sample_get_count();

    // Check that the encoding of the samples is correct when using one buffer.
    for (size_t i = 0U; i < sample_count; i++)
    {
        // Get sample.
        const sample_t * const sp = sample_get(i);
        // Copy to encoded buffer for in-place.
        tds.decoded_len = sp->decoded_len;
        (void)memset(tds.decoded, 0U, sizeof(tds.decoded));
        (void)memcpy(tds.decoded, sp->decoded, tds.decoded_len * sizeof(bde_dec_t));
        // Encode.
        error = bde_base64url_encode(tds.decoded,
                                     tds.decoded_len,
                                     sp->encoded_base64url_len + 1U,
                                     (bde_enc_t * const)tds.decoded,
                                     &tds.decoded_len);
        assert_int_equal(bde_error_ok, error);
        assert_int_equal(sp->encoded_base64url_len, tds.decoded_len);
        assert_string_equal(sp->encoded_base64url, (const bde_enc_t *)tds.decoded);
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/
static void test_base64url_encode_length_invalid_args(void ** state)
{
    (void)state;
    bde_error_t error = bde_error_ok;
    const sample_t * const sp = sample_get(0U);

    // Check that an error is returned when the decoded length is not valid.
    error = bde_base64url_encode_length(0U, &tds.encoded_len);
    assert_int_equal(bde_error_args, error);

    // Check that an error is returned when the encoded length is not valid.
    error = bde_base64url_encode_length(sp->decoded_len, NULL);
    assert_int_equal(bde_error_args, error);
}

/*--------------------------------------------------------------------------------------------------------------------*/
static void test_base64url_encode_length_samples(void ** state)
{
    (void)state;
    bde_error_t error = bde_error_ok;
    const size_t sample_count = sample_get_count();

    for (size_t i = 0U; i < sample_count; i++)
    {
        // Get sample.
        const sample_t * const sp = sample_get(i);
        // Encode.
        error = bde_base64url_encode_length(sp->decoded_len, &tds.encoded_len);
        assert_int_equal(bde_error_ok, error);
        assert_int_equal(sp->encoded_base64url_len, tds.encoded_len);
    }
}

/* Exported functions ------------------------------------------------------------------------------------------------*/
#if !defined(DOXYGEN)
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
        cmocka_unit_test_setup_teardown(test_base64url_encode_invalid_args, setup, teardown),
        cmocka_unit_test_setup_teardown(test_base64url_encode_invalid_buffer_length, setup, teardown),
        cmocka_unit_test_setup_teardown(test_base64url_encode_ignored_buffer_length, setup, teardown),
        cmocka_unit_test_setup_teardown(test_base64url_encode_two_separate_buffers, setup, teardown),
        cmocka_unit_test_setup_teardown(test_base64url_encode_single_inplace_buffers, setup, teardown),
        cmocka_unit_test_setup_teardown(test_base64url_encode_length_invalid_args, setup, teardown),
        cmocka_unit_test_setup_teardown(test_base64url_encode_length_samples, setup, teardown),
    };

    // Execute the test runner.
    return cmocka_run_group_tests_name("test_base64url_encode", tests, NULL, NULL);
}
#endif /* !DOXYGEN */

/******************************************************************************************************END OF FILE*****/
