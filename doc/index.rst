Introduction
========================================================================================================================

|ProjectFriendlyName| is a C/C++ decoder and encoder based on `RFC4648 <https://datatracker.ietf.org/doc/html/rfc4648>`_
that supports the following bases:

- Base64 encoding and decoding
- Base64URL encoding and decoding (without padding)

Other features are:

- Support for inplace encoding and decoding.
- Obtain length of the resulting encoded or decoded data prior to encoding or decoding.
- Rejection of invalid encoded strings, such as invalid lenghts, padding or characters, or empty strings.
- All functionality is accessible through a single include file ``bde/bde.h``.
- Fully tested, see `Test Results HTML Report <_static/_test_results/test_report.html>`_.
- Around 100% code coverage, see `Code Coverage HTML report <_static/_test_coverage/index.html>`_.
- `MISRA:C 2012 <https://misra.org.uk/misra-c/>`_ compliance, detailed below.
- *MIT* license.

The source code for |ProjectFriendlyName| is hosted at `Github <https://github.com/dmg0345/bde>`_ and related
*Docker* images for development containers are located at `DockerHub <https://hub.docker.com/r/dmg00345/bde>`_.

.. note::

    This is the documentation for |ProjectFriendlyName|, version |ProjectVersion|, refer to :doc:`api/version` for
    more details regarding the release.

MISRA C:2012 Compliance
------------------------------------------------------------------------------------------------------------------------

The `CppCheck <https://cppcheck.sourceforge.io/>`_ tool along with it's MISRA addon is used to check for compliance.
This tool is run, along with others, on workflows in `Github Actions` as part of pull requests and prior to release.

For details about suppressions and deviations, look in the global *suppressions.xml* file or for inline suppressions
in the source code on top of the ``cppcheck-suppress misra`` inline supression identifier.

License
-----------------------------------------------------------------------------------------------------------------------

.. literalinclude:: ../LICENSE

.. toctree::
    :caption: Main
    :titlesonly:
    :hidden:

    self
    Base64 <usecases/base64>
    Base64URL <usecases/base64url>

.. toctree::
    :caption: API
    :titlesonly:
    :hidden:

    Base64 <api/base64>
    Base64URL <api/base64url>
    Versioning <api/version>
    Commons <api/commons>
