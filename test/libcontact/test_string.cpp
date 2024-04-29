#include <minunit/minunit.h>
#include <dangerfarm_contact/macro_tricks.h>
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

#define STRING_FILTER_TEST(val) \
    TEST(string_filter_ ## val) \
    { \
        char* str = nullptr; \
        char INPUT[] = "xxxx"; \
        const size_t INPUT_SIZE = strlen(INPUT); \
        const char* EXPECTED_OUTPUT = " xxx"; \
        INPUT[0] = val; \
        TEST_ASSERT(STATUS_SUCCESS == string_create(&str, INPUT, INPUT_SIZE)); \
        TEST_ASSERT(STATUS_SUCCESS == string_filter(str)); \
        TEST_EXPECT(0 == strcmp(str, EXPECTED_OUTPUT)); \
        TEST_ASSERT(STATUS_SUCCESS == string_release(str)); \
    } \
    REQUIRE_SEMICOLON_HERE

STRING_FILTER_TEST(0x01);
STRING_FILTER_TEST(0x02);
STRING_FILTER_TEST(0x03);
STRING_FILTER_TEST(0x04);
STRING_FILTER_TEST(0x05);
STRING_FILTER_TEST(0x06);
STRING_FILTER_TEST(0x07);
STRING_FILTER_TEST(0x08);
STRING_FILTER_TEST(0x09);
STRING_FILTER_TEST(0x0A);
STRING_FILTER_TEST(0x0B);
STRING_FILTER_TEST(0x0C);
