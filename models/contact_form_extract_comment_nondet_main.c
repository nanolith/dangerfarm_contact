#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>

int main(int argc, char* argv[])
{
    int retval;
    const char* NAME = "foo";
    const char* EMAIL = "foo";
    const char* SUBJECT = "foo";
    const char* COMMENT = "foo";
    char* str = NULL;
    contact_form* form = NULL;

    retval = contact_form_create(&form, NAME, EMAIL, SUBJECT, COMMENT);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto done;
    }

    retval = contact_form_extract_comment(&str, form);
    if (STATUS_SUCCESS != retval)
    {
        /* the only failure case this implementation supports is an allocation
         * error. */
        MODEL_ASSERT(ERROR_GENERAL_OUT_OF_MEMORY == retval);
        goto cleanup_form;
    }

    retval = 0;
    goto cleanup_str;

cleanup_str:
    MODEL_ASSERT(STATUS_SUCCESS == string_release(str));

cleanup_form:
    MODEL_ASSERT(STATUS_SUCCESS == contact_form_release(form));

done:
    return retval;
}
