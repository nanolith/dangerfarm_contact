#include <minunit/minunit.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>
#include <string.h>

TEST_SUITE(util_string);

/**
 * We can create a string from data and release this string.
 */
TEST(string_create_release)
{
    char* str = nullptr;
    const char* INPUT = "foo bar baz";
    const size_t INPUT_SIZE = strlen(INPUT);

    /* we can create a string from data. */
    TEST_ASSERT(STATUS_SUCCESS == string_create(&str, INPUT, INPUT_SIZE));

    /* the resulting string is not NULL. */
    TEST_ASSERT(nullptr != str);

    /* the length of this string is INPUT_SIZE. */
    TEST_EXPECT(INPUT_SIZE == strlen(str));

    /* the string matches the input. */
    TEST_EXPECT(0 == strcmp(str, INPUT));

    /* we can release this string. */
    TEST_ASSERT(STATUS_SUCCESS == string_release(str));
}

/**
 * string_filter filters out 0x01.
 */
TEST(string_filter_0x01)
{
    char* str = nullptr;
    const char* INPUT = "\x01xxx";
    const size_t INPUT_SIZE = strlen(INPUT);
    const char* EXPECTED_OUTPUT = " xxx";

    /* we can create a string from data. */
    TEST_ASSERT(STATUS_SUCCESS == string_create(&str, INPUT, INPUT_SIZE));

    /* we can filter the string. */
    TEST_ASSERT(STATUS_SUCCESS == string_filter(str));

    /* the string matches the expected output. */
    TEST_EXPECT(0 == strcmp(str, EXPECTED_OUTPUT));

    /* we can release this string. */
    TEST_ASSERT(STATUS_SUCCESS == string_release(str));
}

/**
 * string_filter filters out 0x02.
 */
TEST(string_filter_0x02)
{
    char* str = nullptr;
    const char* INPUT = "\x02xxx";
    const size_t INPUT_SIZE = strlen(INPUT);
    const char* EXPECTED_OUTPUT = " xxx";

    /* we can create a string from data. */
    TEST_ASSERT(STATUS_SUCCESS == string_create(&str, INPUT, INPUT_SIZE));

    /* we can filter the string. */
    TEST_ASSERT(STATUS_SUCCESS == string_filter(str));

    /* the string matches the expected output. */
    TEST_EXPECT(0 == strcmp(str, EXPECTED_OUTPUT));

    /* we can release this string. */
    TEST_ASSERT(STATUS_SUCCESS == string_release(str));
}

/**
 * string_filter filters out 0x03.
 */
TEST(string_filter_0x03)
{
    char* str = nullptr;
    const char* INPUT = "\x03xxx";
    const size_t INPUT_SIZE = strlen(INPUT);
    const char* EXPECTED_OUTPUT = " xxx";

    /* we can create a string from data. */
    TEST_ASSERT(STATUS_SUCCESS == string_create(&str, INPUT, INPUT_SIZE));

    /* we can filter the string. */
    TEST_ASSERT(STATUS_SUCCESS == string_filter(str));

    /* the string matches the expected output. */
    TEST_EXPECT(0 == strcmp(str, EXPECTED_OUTPUT));

    /* we can release this string. */
    TEST_ASSERT(STATUS_SUCCESS == string_release(str));
}

/**
 * string_filter filters out 0x04.
 */
TEST(string_filter_0x04)
{
    char* str = nullptr;
    const char* INPUT = "\x04xxx";
    const size_t INPUT_SIZE = strlen(INPUT);
    const char* EXPECTED_OUTPUT = " xxx";

    /* we can create a string from data. */
    TEST_ASSERT(STATUS_SUCCESS == string_create(&str, INPUT, INPUT_SIZE));

    /* we can filter the string. */
    TEST_ASSERT(STATUS_SUCCESS == string_filter(str));

    /* the string matches the expected output. */
    TEST_EXPECT(0 == strcmp(str, EXPECTED_OUTPUT));

    /* we can release this string. */
    TEST_ASSERT(STATUS_SUCCESS == string_release(str));
}

/**
 * string_filter filters out 0x05.
 */
TEST(string_filter_0x05)
{
    char* str = nullptr;
    const char* INPUT = "\x05xxx";
    const size_t INPUT_SIZE = strlen(INPUT);
    const char* EXPECTED_OUTPUT = " xxx";

    /* we can create a string from data. */
    TEST_ASSERT(STATUS_SUCCESS == string_create(&str, INPUT, INPUT_SIZE));

    /* we can filter the string. */
    TEST_ASSERT(STATUS_SUCCESS == string_filter(str));

    /* the string matches the expected output. */
    TEST_EXPECT(0 == strcmp(str, EXPECTED_OUTPUT));

    /* we can release this string. */
    TEST_ASSERT(STATUS_SUCCESS == string_release(str));
}
