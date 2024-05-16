#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>

int nondet_char();
static void randomize_string(char* str, size_t size)
{
    for (size_t i = 0; i < size - 1; ++i) str[i] = nondet_char();
    str[size - 1] = 0;
}

int main(int argc, char* argv[])
{
    int retval;
    char* str = NULL;
    char NAME[10];
    char EMAIL[10];
    char SUBJECT[10];
    char COMMENT[10];
    contact_form* form = NULL;

    randomize_string(NAME, sizeof(NAME));
    randomize_string(EMAIL, sizeof(EMAIL));
    randomize_string(SUBJECT, sizeof(SUBJECT));
    randomize_string(COMMENT, sizeof(COMMENT));

    /* Create a contact form. */
    retval = contact_form_create(&form, NAME, EMAIL, SUBJECT, COMMENT);
    if (STATUS_SUCCESS != retval)
    {
        return 1;
    }

    /* Release the contact form. */
    retval = contact_form_release(form);
    if (STATUS_SUCCESS != retval)
    {
        return 1;
    }

    return 0;
}
