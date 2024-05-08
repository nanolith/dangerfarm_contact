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
STRING_FILTER_TEST(0x0D);
STRING_FILTER_TEST(0x0E);
STRING_FILTER_TEST(0x0F);
STRING_FILTER_TEST(0x10);
STRING_FILTER_TEST(0x11);
STRING_FILTER_TEST(0x12);
STRING_FILTER_TEST(0x13);
STRING_FILTER_TEST(0x14);
STRING_FILTER_TEST(0x15);
STRING_FILTER_TEST(0x16);
STRING_FILTER_TEST(0x17);
STRING_FILTER_TEST(0x18);
STRING_FILTER_TEST(0x19);
STRING_FILTER_TEST(0x1A);
STRING_FILTER_TEST(0x1B);
STRING_FILTER_TEST(0x1C);
STRING_FILTER_TEST(0x1D);
STRING_FILTER_TEST(0x1E);
STRING_FILTER_TEST(0x1F);
STRING_FILTER_TEST(0x7F);

#define STRING_FILTER_HIGH_TEST(name, val) \
    TEST(string_filter_high_ ## name) \
    { \
        char* str = nullptr; \
        const char* INPUT = val; \
        const size_t INPUT_SIZE = strlen(INPUT); \
        TEST_ASSERT(STATUS_SUCCESS == string_create(&str, INPUT, INPUT_SIZE)); \
        TEST_ASSERT(STATUS_SUCCESS == string_filter(str)); \
        for (size_t i = 0; i < INPUT_SIZE; ++i) \
        { \
            TEST_EXPECT(' ' == str[i]); \
        } \
        TEST_EXPECT(0 == str[INPUT_SIZE]); \
        TEST_ASSERT(STATUS_SUCCESS == string_release(str)); \
    } \
    REQUIRE_SEMICOLON_HERE

STRING_FILTER_HIGH_TEST(x80, "\u0080");
STRING_FILTER_HIGH_TEST(x81, "\u0081");
STRING_FILTER_HIGH_TEST(x82, "\u0082");
STRING_FILTER_HIGH_TEST(x83, "\u0083");
STRING_FILTER_HIGH_TEST(x84, "\u0084");
STRING_FILTER_HIGH_TEST(x85, "\u0085");
STRING_FILTER_HIGH_TEST(x86, "\u0086");
STRING_FILTER_HIGH_TEST(x87, "\u0087");
STRING_FILTER_HIGH_TEST(x88, "\u0088");
STRING_FILTER_HIGH_TEST(x89, "\u0089");
STRING_FILTER_HIGH_TEST(x8A, "\u008A");
STRING_FILTER_HIGH_TEST(x8B, "\u008B");
STRING_FILTER_HIGH_TEST(x8C, "\u008C");
STRING_FILTER_HIGH_TEST(x8D, "\u008D");
STRING_FILTER_HIGH_TEST(x8E, "\u008E");
STRING_FILTER_HIGH_TEST(x8F, "\u008F");
STRING_FILTER_HIGH_TEST(x90, "\u0090");
STRING_FILTER_HIGH_TEST(x91, "\u0091");
STRING_FILTER_HIGH_TEST(x92, "\u0092");
STRING_FILTER_HIGH_TEST(x93, "\u0093");
STRING_FILTER_HIGH_TEST(x94, "\u0094");
STRING_FILTER_HIGH_TEST(x95, "\u0095");
STRING_FILTER_HIGH_TEST(x96, "\u0096");
STRING_FILTER_HIGH_TEST(x97, "\u0097");
STRING_FILTER_HIGH_TEST(x98, "\u0098");

#define INVALID_SEQUENCE_TEST(name, val, length) \
    TEST(invalid_sequence_ ## name) \
    { \
        char* str = nullptr; \
        const char INPUT[] = val; \
        const size_t INPUT_SIZE = length; \
        const char* EXPECTED_OUTPUT = "              "; \
        TEST_ASSERT(STATUS_SUCCESS == string_create(&str, INPUT, INPUT_SIZE)); \
        TEST_ASSERT(STATUS_SUCCESS == string_filter(str)); \
        TEST_EXPECT(0 == memcmp(str, EXPECTED_OUTPUT, length)); \
        TEST_EXPECT(0 == str[length]); \
        TEST_ASSERT(STATUS_SUCCESS == string_release(str)); \
    } \
    REQUIRE_SEMICOLON_HERE

INVALID_SEQUENCE_TEST(naked_continuation, "\x80", 1);
INVALID_SEQUENCE_TEST(truncated_2_byte, "\xD0", 1);
INVALID_SEQUENCE_TEST(invalid_2_byte_continuation, "\xD0\x01", 2);
INVALID_SEQUENCE_TEST(overlong_2_byte_sequence, "\xC0\x81", 2);
INVALID_SEQUENCE_TEST(truncated_3_byte1, "\xE0", 1);
INVALID_SEQUENCE_TEST(truncated_3_byte2, "\xE1\x81", 2);
INVALID_SEQUENCE_TEST(invalid_3_byte_continuation1, "\xE1\x01", 2);
INVALID_SEQUENCE_TEST(invalid_3_byte_continuation2, "\xE1\x81\x01", 3);
INVALID_SEQUENCE_TEST(overlong_3_byte_sequence, "\xE0\x80\x81", 3);
INVALID_SEQUENCE_TEST(truncated_4_byte1, "\xF0", 1);
INVALID_SEQUENCE_TEST(truncated_4_byte2, "\xF0\x81", 2);
INVALID_SEQUENCE_TEST(truncated_4_byte3, "\xF0\x81\x81", 3);
INVALID_SEQUENCE_TEST(invalid_4_byte_continuation1, "\xF1\x01", 2);
INVALID_SEQUENCE_TEST(invalid_4_byte_continuation2, "\xF1\x81\x01", 3);
INVALID_SEQUENCE_TEST(invalid_4_byte_continuation3, "\xF1\x81\x81\x01", 4);
INVALID_SEQUENCE_TEST(overlong_4_byte_sequence, "\xF0\x80\x80\x81", 4);
INVALID_SEQUENCE_TEST(out_of_range_4_byte_sequence, "\xF7\xBF\xBF\xBF", 4);
INVALID_SEQUENCE_TEST(bad_high_byte, "\xFF", 1);

#define VALID_SEQUENCE_TEST(name, val) \
    TEST(valid_sequence_ ## name) \
    { \
        char* str = nullptr; \
        const char INPUT[] = val; \
        const size_t INPUT_SIZE = strlen(val); \
        TEST_ASSERT(STATUS_SUCCESS == string_create(&str, INPUT, INPUT_SIZE)); \
        TEST_ASSERT(STATUS_SUCCESS == string_filter(str)); \
        TEST_EXPECT(0 == memcmp(str, INPUT, INPUT_SIZE)); \
        TEST_EXPECT(0 == str[INPUT_SIZE]); \
        TEST_ASSERT(STATUS_SUCCESS == string_release(str)); \
    } \
    REQUIRE_SEMICOLON_HERE

VALID_SEQUENCE_TEST(two_byte_character, "français");
VALID_SEQUENCE_TEST(three_byte_characters, "x ∈ ℤ");
VALID_SEQUENCE_TEST(four_byte_characters, "😎");
