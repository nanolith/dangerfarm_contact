#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>
#include <minunit/minunit.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

TEST_SUITE(contact_form);

namespace {
    const char* NAME = "Mr. Smith";
    const char* EMAIL = "smith@example.com";
    const char* SUBJECT = "Website Security";
    const char* COMMENT = "I like your website, but is it secure?";
}

/**
 * We can create a contact form and release it.
 */
TEST(contact_form_create_release)
{
    contact_form* form;
    char* name;
    char* email;
    char* subject;
    char* comment;

    /* We can create a contact_form instance. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == contact_form_create(&form, NAME, EMAIL, SUBJECT, COMMENT));

    /* A created form is always valid. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == contact_form_verify(form, contact_form_compute_size(form)));

    /* We can extract the name. */
    TEST_ASSERT(STATUS_SUCCESS == contact_form_extract_name(&name, form));

    /* We can extract the email. */
    TEST_ASSERT(STATUS_SUCCESS == contact_form_extract_email(&email, form));

    /* We can extract the subject. */
    TEST_ASSERT(STATUS_SUCCESS == contact_form_extract_subject(&subject, form));

    /* We can extract the comment field. */
    TEST_ASSERT(STATUS_SUCCESS == contact_form_extract_comment(&comment, form));

    /* the name matches. */
    TEST_EXPECT(0 == strcmp(name, NAME));

    /* the email matches. */
    TEST_EXPECT(0 == strcmp(email, EMAIL));

    /* the subject matches. */
    TEST_EXPECT(0 == strcmp(subject, SUBJECT));

    /* the comment matches. */
    TEST_EXPECT(0 == strcmp(comment, COMMENT));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == contact_form_release(form));
    TEST_ASSERT(STATUS_SUCCESS == string_release(name));
    TEST_ASSERT(STATUS_SUCCESS == string_release(email));
    TEST_ASSERT(STATUS_SUCCESS == string_release(subject));
    TEST_ASSERT(STATUS_SUCCESS == string_release(comment));
}

/**
 * We can read and write contact form data.
 */
TEST(contact_form_read_write)
{
    int sock[2];
    contact_form* formwrite;
    contact_form* formread;
    char* name;
    char* email;
    char* subject;
    char* comment;

    /* We can create a contact_form instance. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == contact_form_create(&formwrite, NAME, EMAIL, SUBJECT, COMMENT));

    /* we can create a socket pair. */
    TEST_ASSERT(0 == socketpair(AF_UNIX, SOCK_STREAM, 0, sock));

    /* write the form. */
    TEST_ASSERT(STATUS_SUCCESS == contact_form_write(sock[0], formwrite));

    /* read the form. */
    TEST_ASSERT(STATUS_SUCCESS == contact_form_read(&formread, sock[1]));

    /* extract the fields. */
    TEST_ASSERT(STATUS_SUCCESS == contact_form_extract_name(&name, formread));
    TEST_ASSERT(STATUS_SUCCESS == contact_form_extract_email(&email, formread));
    TEST_ASSERT(
        STATUS_SUCCESS == contact_form_extract_subject(&subject, formread));
    TEST_ASSERT(
        STATUS_SUCCESS == contact_form_extract_comment(&comment, formread));

    /* the fields match. */
    TEST_EXPECT(0 == strcmp(name, NAME));
    TEST_EXPECT(0 == strcmp(email, EMAIL));
    TEST_EXPECT(0 == strcmp(subject, SUBJECT));
    TEST_EXPECT(0 == strcmp(comment, COMMENT));

    /* clean up. */
    TEST_ASSERT(0 == close(sock[0]));
    TEST_ASSERT(0 == close(sock[1]));
    TEST_ASSERT(STATUS_SUCCESS == contact_form_release(formwrite));
    TEST_ASSERT(STATUS_SUCCESS == string_release(name));
    TEST_ASSERT(STATUS_SUCCESS == string_release(email));
    TEST_ASSERT(STATUS_SUCCESS == string_release(subject));
    TEST_ASSERT(STATUS_SUCCESS == string_release(comment));
}
