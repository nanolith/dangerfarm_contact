#include <dangerfarm_contact/status_codes.h>
#include <minunit/minunit.h>
#include <string.h>

TEST_SUITE(status_decode);

/**
 * Test that each status is decoded into unique strings by class.
 */
TEST(decode_strings)
{
    /* verify that an unknown status is decoded as an unknown string. */
    const char* unknown_string = status_decode(-1);
    TEST_ASSERT(0 == strcmp(unknown_string, "unknown error"));
}
