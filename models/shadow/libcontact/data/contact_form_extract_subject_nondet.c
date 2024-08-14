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

int contact_form_extract_subject(char** subject, const contact_form* form)
{
    size_t size = random_size();

    MODEL_ASSERT(prop_valid_contact_form(form));

    char* tmp = (char*)malloc(size + 1);
    if (NULL == tmp)
    {
        return ERROR_GENERAL_OUT_OF_MEMORY;
    }

    for (size_t i = 0; i < size; ++i)
    {
        tmp[i] = nondet_char();
    }

    tmp[size] = 0;
    *subject = tmp;

    return STATUS_SUCCESS;
}
