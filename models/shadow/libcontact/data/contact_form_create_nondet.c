#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>
#include <stdlib.h>

DANGERFARM_CONTACT_IMPORT_contact_form;

static char nondet_char();
static size_t nondet_size();
static size_t random_size()
{
    size_t size = nondet_size();
    if (size > 3)
        size = 3;

    return size;
}

int contact_form_create_nondet(
    contact_form** form)
{
    contact_form* tmp = NULL;
    size_t offset = 0;
    size_t name_len = random_size();
    size_t email_len = random_size();
    size_t subject_len = random_size();
    size_t comment_len = random_size();
    size_t contact_form_size = sizeof(contact_form);
    size_t total_size =
        name_len + email_len + subject_len + comment_len + contact_form_size;

    /* allocate memory for this form. */
    tmp = (contact_form*)malloc(total_size);
    if (NULL == tmp)
    {
        return ERROR_GENERAL_OUT_OF_MEMORY;
    }

    /* set the sizes. */
    tmp->name_size = name_len;
    tmp->email_size = email_len;
    tmp->subject_size = subject_len;
    tmp->comment_size = comment_len;

    /* initialize with random data. */
    for (size_t i = 0; i < name_len; ++i)
        tmp->data[offset + i] = nondet_char();
    offset += name_len;
    for (size_t i = 0; i < email_len; ++i)
        tmp->data[offset + i] = nondet_char();
    offset += email_len;
    for (size_t i = 0; i < subject_len; ++i)
        tmp->data[offset + i] = nondet_char();
    offset += subject_len;
    for (size_t i = 0; i < comment_len; ++i)
        tmp->data[offset + i] = nondet_char();
    offset += comment_len;

    *form = tmp;
    return STATUS_SUCCESS;
}

int contact_form_create(
    contact_form** form, const char* name, const char* email,
    const char* subject, const char* comment)
{
    /* verify that the parameters are valid. */
    MODEL_ASSERT(prop_string_valid(name));
    MODEL_ASSERT(prop_string_valid(email));
    MODEL_ASSERT(prop_string_valid(subject));
    MODEL_ASSERT(prop_string_valid(comment));
    MODEL_ASSERT(NULL != form);

    return contact_form_create_nondet(form);
}
