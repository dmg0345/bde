Base64URL Use Cases
========================================================================================================================

This sections cover some typical use cases related to *Base64URL* decoding and encoding, for a description of the all
functionality refer to the *API* section.

Note that for simplicity, there is no error handling in the examples shown.

#1: Decoding with a large preallocated buffer
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

.. code-block:: c

    #include "bde/bde.h"

    // Prepare data to decode.
    const bde_enc_t * enc = "SGVsbG8gV29ybGQh";
    const size_t enc_len = 16U;

    // Prepare preallocated large buffer for the decoded data.
    bde_dec_t dec_buf[48U];
    size_t dec_buf_len = sizeof(dec_buf) / sizeof(*dec_buf);

    // Perform decoding.
    size_t dec_len = 0U;
    bde_base64url_decode(enc, enc_len, dec_buf_len, dec_buf, &dec_len);

#2: Decoding using Variable Length Arrays
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

.. code-block:: c

    #include "bde/bde.h"

    // Prepare data to decode.
    const bde_enc_t * enc = "SGVsbG8gV29ybGQh";
    const size_t enc_len = 16U;

    // Calculate size of the decoded data prior to decoding, and allocate VLA of that size.
    size_t dec_buf_len = 0U;
    bde_base64url_decode_length(enc_len, &dec_buf_len);
    bde_dec_t dec_buf[dec_buf_len];

    // Perform decoding.
    size_t dec_len = 0U;
    bde_base64url_decode(enc, enc_len, dec_buf_len, dec_buf, &dec_len);


#3: Decoding using dynamic memory allocation
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

.. code-block:: c

    #include <stdlib.h>
    #include "bde/bde.h"

    // Prepare data to decode.
    const bde_enc_t * enc = "SGVsbG8gV29ybGQh";
    const size_t enc_len = 16U;

    // Calculate size of the decoded data prior to decoding, and allocate VLA of that size.
    size_t dec_buf_len = 0U;
    bde_base64url_decode_length(enc_len, &dec_buf_len);
    bde_dec_t * const dec_buf = malloc(dec_buf_len * sizeof(bde_dec_t));

    // Perform decoding.
    size_t dec_len = 0U;
    bde_base64url_decode(enc, enc_len, dec_buf_len, dec_buf, &dec_len);

#4: Decoding in-place
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

.. code-block:: c

    #include "bde/bde.h"

    // Prepare inplace buffer with the encoded data and large enough for the decoded data.
    bde_dec_t inp_buf[48U] = "SGVsbG8gV29ybGQh";
    const size_t inp_buf_len = sizeof(inp_buf) / sizeof(*inp_buf);
    const size_t enc_len = 16U;

    // Perform decoding.
    size_t dec_len = 0U;
    bde_base64url_decode((const bde_enc_t *)inp_buf,
                         enc_len, inp_buf_len, inp_buf, &dec_len);

#5: Encoding with a large preallocated buffer
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

.. code-block:: c

    #include "bde/bde.h"

    // Prepare data to encode.
    const bde_dec_t dec[] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!'};
    const size_t dec_len = sizeof(dec) / sizeof(*dec);

    // Prepare preallocated large buffer for the encoded data.
    bde_enc_t enc_buf[48U];
    size_t enc_buf_len = sizeof(enc_buf) / sizeof(*enc_buf);

    // Perform encoding.
    size_t enc_str_len = 0U;
    bde_base64url_encode(dec, dec_len, enc_buf_len, enc_buf, &enc_str_len);

#6: Encoding using Variable Length Arrays
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

.. code-block:: c

    #include "bde/bde.h"

    // Prepare data to encode.
    const bde_dec_t dec[] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!'};
    const size_t dec_len = sizeof(dec) / sizeof(*dec);

    // Calculate size of the encoded data prior to decoding, and allocate VLA of that size.
    size_t enc_buf_len = 0U;
    bde_base64url_encode_length(dec_len, &enc_buf_len);
    enc_buf_len += 1U; // Increment to have space for the NULL terminator.
    bde_enc_t enc_buf[enc_buf_len];

    // Perform encoding.
    size_t enc_str_len = 0U;
    bde_base64url_encode(dec, dec_len, enc_buf_len, enc_buf, &enc_str_len);

#7: Encoding using dynamic memory allocation
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

.. code-block:: c

    #include <stdlib.h>
    #include "bde/bde.h"

    // Prepare data to encode.
    const bde_dec_t dec[] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!'};
    const size_t dec_len = sizeof(dec) / sizeof(*dec);

    // Calculate size of the encoded data prior to decoding, and allocate buffer of that size.
    size_t enc_buf_len = 0U;
    bde_base64url_encode_length(dec_len, &enc_buf_len);
    enc_buf_len += 1U; // Increment to have space for the NULL terminator.
    bde_enc_t * const enc_buf = malloc(enc_buf_len * sizeof(bde_enc_t));

    // Perform encoding.
    size_t enc_str_len = 0U;
    bde_base64url_encode(dec, dec_len, enc_buf_len, enc_buf, &enc_str_len);

#8: Encoding in-place
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

.. code-block:: c

    #include "bde/bde.h"

    // Prepare inplace buffer with the decoded data and large enough for the encoded data.
    bde_enc_t inp_buf[48U] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!'};
    const size_t inp_buf_len = sizeof(inp_buf) / sizeof(*inp_buf);
    const size_t dec_len = 12U;

    // Perform encoding.
    size_t enc_str_len = 0U;
    bde_base64url_encode((const bde_dec_t *)inp_buf,
                         dec_len, inp_buf_len, inp_buf, &enc_str_len);
