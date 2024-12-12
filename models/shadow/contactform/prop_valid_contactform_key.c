#include "../../../src/contactform/contactform_internal.h"

/**
 * \brief Verify that the given contact form key is valid.
 *
 * \param key           The contact form key to verify.
 *
 * \returns true if this contact form key is valid and false otherwise.
 */
bool prop_valid_contactform_key(int key)
{
    switch (key)
    {
        case KEY_NAME:
        case KEY_EMAIL:
        case KEY_SUBJECT:
        case KEY_COMMENT:
            return true;

        default:
            return false;
    }
}
