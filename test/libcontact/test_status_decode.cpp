#include <dangerfarm_contact/status_codes.h>
#include <minunit/minunit.h>
#include <string.h>

TEST_SUITE(status_decode);

static size_t match_count(const char* str, const char** arr, size_t size)
{
    size_t count = 0;

    for (size_t i = 0; i < size; ++i)
    {
        if (str == arr[i])
            ++count;
    }

    return count;
}

#define MATCH_AND_ADD(status, count) \
    str = status_decode(status); \
    TEST_EXPECT(count == match_count(str, unique_strings, unique_ctr)); \
    unique_strings[unique_ctr++] = str; \

/**
 * Test that each status is decoded into unique strings by class.
 */
TEST(decode_strings)
{
    const char* unique_strings[1024];
    const char* str;
    size_t unique_ctr = 0;

    /* verify that an unknown status is decoded as an unknown string. */
    const char* unknown_string = status_decode(-1);
    TEST_ASSERT(0 == strcmp(unknown_string, "unknown error"));
    unique_strings[unique_ctr++] = unknown_string;

    /* verify status strings. */
    MATCH_AND_ADD(STATUS_SUCCESS, 0);
    MATCH_AND_ADD(ERROR_GENERAL_OUT_OF_MEMORY, 0);
    MATCH_AND_ADD(ERROR_READ_MULTIBYTE_EOF, 0);
    MATCH_AND_ADD(ERROR_READ_MULTIBYTE_RAW_CONTINUATION, 0);
    MATCH_AND_ADD(ERROR_READ_MULTIBYTE_INVALID_CONTINUATION, 0);
    MATCH_AND_ADD(ERROR_READ_MULTIBYTE_OVERLONG_REPRESENTATION, 0);
    MATCH_AND_ADD(ERROR_READ_MULTIBYTE_UNEXPECTED_CHARACTER, 0);
    MATCH_AND_ADD(ERROR_READ_MULTIBYTE_CODEPOINT_OUT_OF_RANGE, 0);
    MATCH_AND_ADD(ERROR_CONTACT_FORM_WRITE, 0);
    MATCH_AND_ADD(ERROR_CONTACT_FORM_READ, 0);
    MATCH_AND_ADD(ERROR_CONTACT_FORM_INVALID, 0);
    MATCH_AND_ADD(ERROR_SOCKET_WRITE, 0);
    MATCH_AND_ADD(ERROR_SOCKET_READ, 0);
    MATCH_AND_ADD(ERROR_DATABASE_PROTOCOL_UNEXPECTED_REQUEST_ID, 0);
    MATCH_AND_ADD(ERROR_DATABASE_PROTOCOL_INVALID_COUNT, 0);
    MATCH_AND_ADD(ERROR_DATABASE_SYNC, 0);
    MATCH_AND_ADD(ERROR_DATABASE_ENV_CREATE, 0);
    MATCH_AND_ADD(ERROR_DATABASE_SET_MAPSIZE, 0);
    MATCH_AND_ADD(ERROR_DATABASE_SET_MAXDBS, 0);
    MATCH_AND_ADD(ERROR_DATABASE_ENV_OPEN, 0);
    MATCH_AND_ADD(ERROR_DATABASE_TXN_BEGIN, 0);
    MATCH_AND_ADD(ERROR_DATABASE_DBI_OPEN, 0);
    MATCH_AND_ADD(ERROR_DATABASE_TXN_COMMIT, 0);
    MATCH_AND_ADD(ERROR_DATABASE_PUT, 0);
    MATCH_AND_ADD(ERROR_DATABASE_GET, 0);
    MATCH_AND_ADD(ERROR_DATABASE_DELETE, 0);
    MATCH_AND_ADD(ERROR_DATABASE_CURSOR_OPEN, 0);
    MATCH_AND_ADD(ERROR_DATABASE_CURSOR_GET, 0);
    MATCH_AND_ADD(ERROR_CONTACTDB_MISSING_PARAMETER, 0);
    MATCH_AND_ADD(ERROR_CONTACTDB_BAD_PARAMETER, 0);
    MATCH_AND_ADD(ERROR_CONTACTDB_SOCKET_PATH_TOO_LONG, 0);
    MATCH_AND_ADD(ERROR_CONTACTDB_SOCKET_FAILURE, 0);
    MATCH_AND_ADD(ERROR_CONTACTDB_BIND_FAILURE, 0);
}
