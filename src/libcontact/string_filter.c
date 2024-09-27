#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>
#include <stdbool.h>
#include <stdint.h>

/* forward decls. */
static void blank_and_advance(char** str, size_t length);
static bool is_lower_control_character(const char* str);
static bool is_allowed_control_character(const char* str);
static bool is_high_bit_character(const char* str);
static int read_multibyte(
    uint32_t* codepoint, size_t* codepoint_size, const char* str);
static int read_two_byte_sequence(
    uint32_t* codepoint, size_t* codepoint_size, uint8_t hdr, const char* str);
static int read_three_byte_sequence(
    uint32_t* codepoint, size_t* codepoint_size, uint8_t hdr, const char* str);
static int read_four_byte_sequence(
    uint32_t* codepoint, size_t* codepoint_size, uint8_t hdr, const char* str);
static bool is_two_byte_sequence_start_byte(uint8_t byte);
static bool is_three_byte_sequence_start_byte(uint8_t byte);
static bool is_four_byte_sequence_start_byte(uint8_t byte);
static bool is_ascii_nul(uint8_t byte);
static bool is_continuation_byte(uint8_t byte);
static bool is_codepoint_control_character(uint32_t codepoint);

/**
 * \brief Filter a string, replacing any invalid UTF-8 sequences or HTML /
 * commandline unsafe sequences with spaces.
 *
 * \param str           The string to filter.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(string_filter)(char* str)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(string_filter), str);

    int retval;
    uint32_t codepoint;
    size_t codepoint_size;

    while (!is_ascii_nul(*str))
    {
        /* is this a lower control character? */
        if (    is_lower_control_character(str)
            && !is_allowed_control_character(str))
        {
            blank_and_advance(&str, 1);
        }
        /* is this the start of a high plane sequence? */
        else if (is_high_bit_character(str))
        {
            /* attempt to read a multibyte codepoint. */
            retval = read_multibyte(&codepoint, &codepoint_size, str);
            if (STATUS_SUCCESS != retval)
            {
                /* if this representation is invalid, blank it. */
                blank_and_advance(&str, codepoint_size);
            }
            /* if this codepoint is actually a control character, blank it. */
            else if (is_codepoint_control_character(codepoint))
            {
                blank_and_advance(&str, codepoint_size);
            }
            /* if this is a valid codepoint, keep it. */
            else
            {
                str += codepoint_size;
            }
        }
        else
        {
            ++str;
        }
    }

    retval = STATUS_SUCCESS;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(string_filter), retval, str);

    return retval;
}

/**
 * \brief Check to see if the character at the start of the string is a lower
 * control character.
 *
 * \param str           The string to check.
 *
 * \returns true if this is a lower control character and false otherwise.
 */
static bool is_lower_control_character(const char* str)
{
    if ((*str > 0x00 && *str <= 0x1F) || *str == 0x7F)
    {
        return true;
    }

    return false;
}

/**
 * \brief Check to see if the control character is allowed to pass the filter.
 *
 * \param str           The string to check.
 *
 * \returns true if this is an allowable control character and false otherwise.
 */
static bool is_allowed_control_character(const char* str)
{
    if (*str == '\n' || *str == '\t')
    {
        return true;
    }

    return false;
}

/**
 * \brief Check to see if the given byte is a two byte sequence start byte.
 *
 * \param byte          The byte to check.
 *
 * \returns true if this is a valid two byte sequence start byte and false
 * otherwise.
 */
static bool is_two_byte_sequence_start_byte(uint8_t byte)
{
    if ((byte & 0xE0) == 0xC0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * \brief Check to see if the given byte is a three byte sequence start byte.
 *
 * \param byte          The byte to check.
 *
 * \returns true if this is a valid three byte sequence start byte and false
 * otherwise.
 */
static bool is_three_byte_sequence_start_byte(uint8_t byte)
{
    if ((byte & 0xF0) == 0xE0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/**
 * \brief Check to see if the given byte is a four byte sequence start byte.
 *
 * \param byte          The byte to check.
 *
 * \returns true if this is a valid four byte sequence start byte and false
 * otherwise.
 */
static bool is_four_byte_sequence_start_byte(uint8_t byte)
{
    if ((byte & 0xF8) == 0xF0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * \brief Check to see if the given byte is an ASCII nul.
 *
 * \param byte          The byte to check.
 *
 * \returns true if this is an ASCII nul and false otherwise.
 */
static bool is_ascii_nul(uint8_t byte)
{
    if (0 == byte)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * \brief Check to see if the given byte is a multibyte sequence continuation
 * byte.
 *
 * \param byte          The byte to check.
 *
 * \returns true if this is a contination byte and false otherwise.
 */
static bool is_continuation_byte(uint8_t byte)
{
    if ((byte & 0xC0) == 0x80)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * \brief Check to see if the given codepoint is a control character.
 *
 * \param codepoint     The codepoint to check.
 *
 * \returns true if this is a control character and false otherwise.
 */
static bool is_codepoint_control_character(uint32_t codepoint)
{
    if (codepoint >= 0x80 && codepoint <= 0x9F)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * \brief Check to see if the character at the start of the string is a high bit
 * character, indicating a UTF-8 multibyte sequence.
 *
 * \param str           The string to check.
 *
 * \returns true if this is the start of a multibyte sequence and false
 * otherwise.
 */
static bool is_high_bit_character(const char* str)
{
    if ((*str & 0x80) == 0x80)
    {
        return true;
    }

    return false;
}

/**
 * Blank the given number of characters and advance the pointer.
 *
 * \param str           The string pointer pointer to modify.
 */
static void blank_and_advance(char** str, size_t length)
{
    while (length--)
    {
        if (!is_ascii_nul(**str))
        {
            **str = ' ';
        }

        ++(*str);
    }
}

/**
 * \brief Attempt to read a multibyte sequence and convert this to a codepoint.
 *
 * \note If this read fails, \p codepoint_size will be set to the length of the
 * failing sequence to blank or skip over.
 *
 * \param codepoint         Pointer to receive the codepoint on success.
 * \param codepoint_size    The size of the multibyte sequence in the input
 *                          string that represents this codepoint.
 * \param str               The input string to read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
static int read_multibyte(
    uint32_t* codepoint, size_t* codepoint_size, const char* str)
{
    /* read the first character of this sequence. */
    uint8_t hdr = str[0];

    if (is_continuation_byte(hdr))
    {
        *codepoint_size = 1;
        return ERROR_READ_MULTIBYTE_RAW_CONTINUATION;
    }
    else if (is_two_byte_sequence_start_byte(hdr))
    {
        return read_two_byte_sequence(codepoint, codepoint_size, hdr, str + 1);
    }
    else if (is_three_byte_sequence_start_byte(hdr))
    {
        return
            read_three_byte_sequence(codepoint, codepoint_size, hdr, str + 1);
    }
    else if (is_four_byte_sequence_start_byte(hdr))
    {
        return read_four_byte_sequence(codepoint, codepoint_size, hdr, str + 1);
    }
    else
    {
        *codepoint_size = 1;
        return ERROR_READ_MULTIBYTE_UNEXPECTED_CHARACTER;
    }
}

/**
 * \brief Attempt to read the continuation byte of a two byte sequence and
 * convert this to a codepoint.
 *
 * \note If this read fails, \p codepoint_size will be set to the length of the
 * failing sequence to blank or skip over.
 *
 * \param codepoint         Pointer to receive the codepoint on success.
 * \param codepoint_size    The size of the multibyte sequence in the input
 *                          string that represents this codepoint.
 * \param hdr               The header byte for this sequence.
 * \param str               The input string to read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
static int read_two_byte_sequence(
    uint32_t* codepoint, size_t* codepoint_size, uint8_t hdr, const char* str)
{
    uint8_t byte2 = *str;

    if (is_ascii_nul(byte2))
    {
        *codepoint_size = 1;
        return ERROR_READ_MULTIBYTE_EOF;
    }
    else if (!is_continuation_byte(byte2))
    {
        *codepoint_size = 2;
        return ERROR_READ_MULTIBYTE_INVALID_CONTINUATION;
    }

    /* compute the codepoint. */
    uint32_t point = (hdr & 0x1F) << 6 | (byte2 & 0x3F);
    *codepoint_size = 2;

    /* Is this an overlong representation? */
    if (point < 0x80)
    {
        return ERROR_READ_MULTIBYTE_OVERLONG_REPRESENTATION;
    }

    /* success. */
    *codepoint = point;
    return STATUS_SUCCESS;
}

/**
 * \brief Attempt to read the continuation bytes of a three byte sequence and
 * convert this to a codepoint.
 *
 * \note If this read fails, \p codepoint_size will be set to the length of the
 * failing sequence to blank or skip over.
 *
 * \param codepoint         Pointer to receive the codepoint on success.
 * \param codepoint_size    The size of the multibyte sequence in the input
 *                          string that represents this codepoint.
 * \param hdr               The header byte for this sequence.
 * \param str               The input string to read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
static int read_three_byte_sequence(
    uint32_t* codepoint, size_t* codepoint_size, uint8_t hdr, const char* str)
{
    uint8_t byte2 = str[0];

    if (is_ascii_nul(byte2))
    {
        *codepoint_size = 1;
        return ERROR_READ_MULTIBYTE_EOF;
    }
    else if (!is_continuation_byte(byte2))
    {
        *codepoint_size = 2;
        return ERROR_READ_MULTIBYTE_INVALID_CONTINUATION;
    }

    uint8_t byte3 = str[1];

    if (is_ascii_nul(byte3))
    {
        *codepoint_size = 2;
        return ERROR_READ_MULTIBYTE_EOF;
    }
    else if (!is_continuation_byte(byte3))
    {
        *codepoint_size = 3;
        return ERROR_READ_MULTIBYTE_INVALID_CONTINUATION;
    }

    /* compute the codepoint. */
    uint32_t point = (hdr & 0x0F) << 12 | (byte2 & 0x3F) << 6 | (byte3 & 0x3F);
    *codepoint_size = 3;

    /* Is this an overlong representation? */
    if (point < 0x800)
    {
        return ERROR_READ_MULTIBYTE_OVERLONG_REPRESENTATION;
    }

    /* success. */
    *codepoint = point;
    return STATUS_SUCCESS;
}

/**
 * \brief Attempt to read the continuation bytes of a four byte sequence and
 * convert this to a codepoint.
 *
 * \note If this read fails, \p codepoint_size will be set to the length of the
 * failing sequence to blank or skip over.
 *
 * \param codepoint         Pointer to receive the codepoint on success.
 * \param codepoint_size    The size of the multibyte sequence in the input
 *                          string that represents this codepoint.
 * \param hdr               The header byte for this sequence.
 * \param str               The input string to read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
static int read_four_byte_sequence(
    uint32_t* codepoint, size_t* codepoint_size, uint8_t hdr, const char* str)
{
    uint8_t byte2 = str[0];

    if (is_ascii_nul(byte2))
    {
        *codepoint_size = 1;
        return ERROR_READ_MULTIBYTE_EOF;
    }
    else if (!is_continuation_byte(byte2))
    {
        *codepoint_size = 2;
        return ERROR_READ_MULTIBYTE_INVALID_CONTINUATION;
    }

    uint8_t byte3 = str[1];

    if (is_ascii_nul(byte3))
    {
        *codepoint_size = 2;
        return ERROR_READ_MULTIBYTE_EOF;
    }
    else if (!is_continuation_byte(byte3))
    {
        *codepoint_size = 3;
        return ERROR_READ_MULTIBYTE_INVALID_CONTINUATION;
    }

    uint8_t byte4 = str[2];

    if (is_ascii_nul(byte4))
    {
        *codepoint_size = 3;
        return ERROR_READ_MULTIBYTE_EOF;
    }
    else if (!is_continuation_byte(byte4))
    {
        *codepoint_size = 4;
        return ERROR_READ_MULTIBYTE_INVALID_CONTINUATION;
    }

    /* compute the codepoint. */
    uint32_t point =
          (hdr   & 0x07) << 18
        | (byte2 & 0x3F) << 12
        | (byte3 & 0x3F) <<  6
        | (byte4 & 0x3F);
    *codepoint_size = 4;

    /* Is this an overlong representation? */
    if (point < 0x10000)
    {
        return ERROR_READ_MULTIBYTE_OVERLONG_REPRESENTATION;
    }

    /* Is this representation out of range? */
    if (point > 0x10FFFF)
    {
        return ERROR_READ_MULTIBYTE_CODEPOINT_OUT_OF_RANGE;
    }

    /* success. */
    *codepoint = point;
    return STATUS_SUCCESS;
}
