#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>

int nondet_char();
size_t nondet_size();
size_t get_random_size(size_t size)
{
    size_t random_size = nondet_size();

    if (random_size > size)
    {
        random_size = size;
    }
    if (random_size < 1)
    {
        random_size = 1;
    }

    return random_size;
}

static void randomize_string(char* str, size_t size)
{
    for (size_t i = 0; i < size - 1; ++i) str[i] = nondet_char();
    str[size - 1] = 0;
}

int main(int argc, char* argv[])
{
    int retval;
    char* str = NULL;
    char NAME[9];
    size_t NAME_SIZE = get_random_size(sizeof(NAME));
    char EMAIL[9];
    size_t EMAIL_SIZE = get_random_size(sizeof(EMAIL));
    char SUBJECT[9];
    size_t SUBJECT_SIZE = get_random_size(sizeof(SUBJECT));
    char COMMENT[9];
    size_t COMMENT_SIZE = get_random_size(sizeof(COMMENT));
    contact_form* form = NULL;
    char* email = NULL;

    randomize_string(NAME, NAME_SIZE);
    randomize_string(EMAIL, EMAIL_SIZE);
    randomize_string(SUBJECT, SUBJECT_SIZE);
    randomize_string(COMMENT, COMMENT_SIZE);

    /* Create a contact form. */
    retval = contact_form_create(&form, NAME, EMAIL, SUBJECT, COMMENT);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto done;
    }

    /* extract the email. */
    retval = contact_form_extract_email(&email, form);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup_form;
    }

    goto cleanup_email;

cleanup_email:
    MODEL_ASSERT(STATUS_SUCCESS == string_release(email));

cleanup_form:
    MODEL_ASSERT(STATUS_SUCCESS == contact_form_release(form));

done:
    return retval;
}
