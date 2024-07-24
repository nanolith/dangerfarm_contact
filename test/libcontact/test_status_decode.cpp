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
}
