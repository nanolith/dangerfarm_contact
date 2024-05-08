#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>
#include <stdbool.h>
#include <stdint.h>

char random_char()
{
    char ch = nondet_char();
    MODEL_ASSUME(ch != 0);

    return ch;
}

void randomize_string(char* str, size_t size)
{
    for (size_t i = 0; i < size - 1; ++i)
    {
        str[i] = random_char();
    }

    str[size - 1] = 0;
}

uint32_t read_codepoint(const char* str)
{
    uint32_t byte1 = (((uint8_t)str[0]) & 0xFF);
    if (byte1 < 0x80)
    {
        return byte1;
    }

    if ((byte1 & 0xE0) == 0xC0)
    {
        uint32_t byte2 = (((uint8_t)str[1]) & 0xFF);
        return (byte1 & 0x1F) << 6 | (byte2 & 0x3F);
    }

    if ((byte1 & 0xF0) == 0xE0)
    {
        uint32_t byte2 = (((uint8_t)str[1]) & 0xFF);
        uint32_t byte3 = (((uint8_t)str[2]) & 0xFF);
        return (byte1 & 0x1F) << 12 | (byte2 & 0x3F) << 6 | (byte3 & 0x3F);
    }

    if ((byte1 & 0xF8) == 0xF0)
    {
        uint32_t byte2 = (((uint8_t)str[1]) & 0xFF);
        uint32_t byte3 = (((uint8_t)str[2]) & 0xFF);
        uint32_t byte4 = (((uint8_t)str[3]) & 0xFF);
        return
              (byte1 & 0x1F) << 18
            | (byte2 & 0x3F) << 12
            | (byte3 & 0x3F) <<  6
            | (byte4 & 0x3F);
    }

    return 0;
}

bool is_lower_control(uint32_t codepoint)
{
    return (codepoint >= 0x01 && codepoint <= 0x1F) || (codepoint == 0x7F);
}

bool is_allowed_control(uint32_t codepoint)
{
    return (codepoint == '\t' || codepoint == '\n');
}

bool is_upper_control(uint32_t codepoint)
{
    return (codepoint >= 0x80 && codepoint <= 0x9F);
}

int main(int argc, char* argv[])
{
    int retval;
    char* str = NULL;
    char INPUT[5];

    /* create a randomized string. */
    randomize_string(INPUT, sizeof(INPUT));

    const size_t INPUT_SIZE = 4;

    /* basic exercise of string creation. */
    retval = string_create(&str, INPUT, INPUT_SIZE);
    if (STATUS_SUCCESS != retval)
    {
        return 0;
    }

    /* filter the string. */
    MODEL_ASSERT(STATUS_SUCCESS == string_filter(str));

    uint32_t codepoint = read_codepoint(str);

    /* this codepoint can't be NULL. */
    MODEL_ASSERT(0 != codepoint);
    /* this codepoint can't be a lower control character unless it is allowed */
    MODEL_ASSERT(
        !(is_lower_control(codepoint) && !is_allowed_control(codepoint)));
    /* this codepoint can't be an upper control character. */
    MODEL_ASSERT(!is_upper_control(codepoint));

    /* basic exercise of string release. */
    retval = string_release(str);
    if (STATUS_SUCCESS != retval)
    {
        return 0;
    }

    return 0;
}
