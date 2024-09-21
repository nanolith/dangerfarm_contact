#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>
#include <stdlib.h>

DANGERFARM_CONTACT_IMPORT_contact_form;
DANGERFARM_CONTACT_IMPORT_util_string;

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
        *form = NULL;
        return ERROR_GENERAL_OUT_OF_MEMORY;
    }

    /* set the sizes. */
    tmp->name_size = name_len;
    tmp->email_size = email_len;
    tmp->subject_size = subject_len;
    tmp->comment_size = comment_len;

    /* initialize with random data. */
    char contents_name_nondet[name_len];
    __CPROVER_array_replace(tmp->data + offset, contents_name_nondet);
    offset += name_len;
    char contents_email_nondet[email_len];
    __CPROVER_array_replace(tmp->data + offset, contents_email_nondet);
    offset += email_len;
    char contents_subject_nondet[subject_len];
    __CPROVER_array_replace(tmp->data + offset, contents_subject_nondet);
    offset += subject_len;
    char contents_comment_nondet[comment_len];
    __CPROVER_array_replace(tmp->data + offset, contents_comment_nondet);
    offset += comment_len;

    *form = tmp;
    return STATUS_SUCCESS;
}

int DANGERFARM_CONTACT_SYM(contact_form_create)(
    contact_form** form, const char* name, const char* email,
    const char* subject, const char* comment)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(contact_form_create), form, name, email, subject,
        comment);

    int retval = contact_form_create_nondet(form);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(contact_form_create), retval, form, name, email,
        subject, comment);

    return retval;
}
