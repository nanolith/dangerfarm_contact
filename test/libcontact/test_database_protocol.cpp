#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/protocol/database.h>
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
 * We can read and write a contact form append request.
 */
TEST(database_read_write_contact_form_append_request)
{
    int sock[2];
    contact_form* formwrite;
    contact_form* form;
    char* name;
    char* email;
    char* subject;
    char* comment;
    uint32_t request_id = 1234;

    /* We can create a contact_form instance. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == contact_form_create(&formwrite, NAME, EMAIL, SUBJECT, COMMENT));

    /* we can create a socket pair. */
    TEST_ASSERT(0 == socketpair(AF_UNIX, SOCK_STREAM, 0, sock));

    /* write the append request. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == database_write_contact_form_append_request(
                    sock[0], formwrite));

    /* read the request id. */
    TEST_ASSERT(
        STATUS_SUCCESS == database_read_request_id(&request_id, sock[1]));

    /* the request id matches. */
    TEST_ASSERT(DATABASE_REQUEST_ID_CONTACT_FORM_APPEND == request_id);

    /* read the request payload. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == database_read_contact_form_append_request_payload(
                    &form, sock[1]));

    /* extract the fields. */
    TEST_ASSERT(STATUS_SUCCESS == contact_form_extract_name(&name, form));
    TEST_ASSERT(STATUS_SUCCESS == contact_form_extract_email(&email, form));
    TEST_ASSERT(STATUS_SUCCESS == contact_form_extract_subject(&subject, form));
    TEST_ASSERT(STATUS_SUCCESS == contact_form_extract_comment(&comment, form));

    /* the fields match. */
    TEST_EXPECT(0 == strcmp(name, NAME));
    TEST_EXPECT(0 == strcmp(email, EMAIL));
    TEST_EXPECT(0 == strcmp(subject, SUBJECT));
    TEST_EXPECT(0 == strcmp(comment, COMMENT));

    /* clean up. */
    TEST_ASSERT(0 == close(sock[0]));
    TEST_ASSERT(0 == close(sock[1]));
    TEST_ASSERT(STATUS_SUCCESS == contact_form_release(formwrite));
    TEST_ASSERT(STATUS_SUCCESS == contact_form_release(form));
    TEST_ASSERT(STATUS_SUCCESS == string_release(name));
    TEST_ASSERT(STATUS_SUCCESS == string_release(email));
    TEST_ASSERT(STATUS_SUCCESS == string_release(subject));
    TEST_ASSERT(STATUS_SUCCESS == string_release(comment));
}
