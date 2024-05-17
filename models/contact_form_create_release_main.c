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
    char* name = NULL;
    char* email = NULL;
    char* subject = NULL;
    char* comment = NULL;

    randomize_string(NAME, sizeof(NAME));
    randomize_string(EMAIL, sizeof(EMAIL));
    randomize_string(SUBJECT, sizeof(SUBJECT));
    randomize_string(COMMENT, sizeof(COMMENT));

    /* Create a contact form. */
    retval = contact_form_create(&form, NAME, EMAIL, SUBJECT, COMMENT);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto done;
    }

    /* verify always succeeds for created contact forms. */
    MODEL_ASSERT(
        STATUS_SUCCESS
            == contact_form_verify(form, contact_form_compute_size(form)));

    /* extract the name. */
    retval = contact_form_extract_name(&name, form);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup_form;
    }

    /* extract the email. */
    retval = contact_form_extract_email(&email, form);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup_name;
    }

    /* extract the subject. */
    retval = contact_form_extract_subject(&subject, form);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup_email;
    }

    /* extract the comment. */
    retval = contact_form_extract_comment(&comment, form);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup_subject;
    }

    goto cleanup_comment;

cleanup_comment:
    MODEL_ASSERT(STATUS_SUCCESS == string_release(comment));

cleanup_subject:
    MODEL_ASSERT(STATUS_SUCCESS == string_release(subject));

cleanup_email:
    MODEL_ASSERT(STATUS_SUCCESS == string_release(email));

cleanup_name:
    MODEL_ASSERT(STATUS_SUCCESS == string_release(name));

cleanup_form:
    MODEL_ASSERT(STATUS_SUCCESS == contact_form_release(form));

done:
    return retval;
}
