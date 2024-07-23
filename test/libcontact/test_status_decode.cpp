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

/**
 * Test that each status is decoded into unique strings by class.
 */
TEST(decode_strings)
{
    const char* unique_strings[1024];
    size_t unique_ctr = 0;

    /* verify that an unknown status is decoded as an unknown string. */
    const char* unknown_string = status_decode(-1);
    TEST_ASSERT(0 == strcmp(unknown_string, "unknown error"));
    unique_strings[unique_ctr++] = unknown_string;

    /* verify the success string. */
    const char* success_string = status_decode(STATUS_SUCCESS);
    TEST_EXPECT(0 == match_count(success_string, unique_strings, unique_ctr));
    unique_strings[unique_ctr++] = success_string;
}
