#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>
#include <stdlib.h>

DANGERFARM_CONTACT_IMPORT_contact_form;

char nondet_char();
size_t nondet_size();

size_t random_size()
{
    size_t size = nondet_size();

    if (size > 8)
        size = 8;

    return size;
}

int DANGERFARM_CONTACT_SYM(contact_form_extract_subject)(
    char** subject, const DANGERFARM_CONTACT_SYM(contact_form)* form)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(contact_form_extract_subject), subject, form);

    int retval;
    size_t size = random_size();

    char* tmp = (char*)malloc(size + 1);
    if (NULL == tmp)
    {
        *subject = NULL;
        retval = ERROR_GENERAL_OUT_OF_MEMORY;
        goto done;
    }

    for (size_t i = 0; i < size; ++i)
    {
        tmp[i] = nondet_char();
    }

    tmp[size] = 0;
    *subject = tmp;

    retval = STATUS_SUCCESS;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(contact_form_extract_subject), retval, subject);

    return retval;
}
