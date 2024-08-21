#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>

DANGERFARM_CONTACT_IMPORT_contact_form;
DANGERFARM_CONTACT_IMPORT_util_string;

int main(int argc, char* argv[])
{
    int retval;
    char* str = NULL;
    char NAME[9]; /* ignored by shadow contact_form_create. */
    size_t NAME_SIZE; /* ignored by shadow contact_form_create. */
    char EMAIL[9]; /* ignored by shadow contact_form_create. */
    size_t EMAIL_SIZE; /* ignored by shadow contact_form_create. */
    char SUBJECT[9]; /* ignored by shadow contact_form_create. */
    size_t SUBJECT_SIZE; /* ignored by shadow contact_form_create. */
    char COMMENT[9]; /* ignored by shadow contact_form_create. */
    size_t COMMENT_SIZE; /* ignored by shadow contact_form_create. */
    contact_form* form = NULL;
    char* comment = NULL;

    /* Create a contact form. */
    retval = contact_form_create(&form, NAME, EMAIL, SUBJECT, COMMENT);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto done;
    }

    /* extract the comment. */
    retval = contact_form_extract_comment(&comment, form);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup_form;
    }

    goto cleanup_comment;

cleanup_comment:
    MODEL_ASSERT(STATUS_SUCCESS == string_release(comment));

cleanup_form:
    MODEL_ASSERT(STATUS_SUCCESS == contact_form_release(form));

done:
    return retval;
}
