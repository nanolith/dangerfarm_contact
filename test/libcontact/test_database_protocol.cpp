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

/**
 * We can read and write a contact form append response.
 */
TEST(database_read_write_contact_form_append_response)
{
    int sock[2];
    const uint32_t WRITE_STATUS = 2233;
    uint32_t status = 9999;

    /* we can create a socket pair. */
    TEST_ASSERT(0 == socketpair(AF_UNIX, SOCK_STREAM, 0, sock));

    /* write the append response. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == database_write_contact_form_append_response(
                    sock[0], WRITE_STATUS));

    /* read the response payload. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == database_read_contact_form_append_response(
                    &status, sock[1]));

    /* the statuses match. */
    TEST_EXPECT(WRITE_STATUS == status);

    /* clean up. */
    TEST_ASSERT(0 == close(sock[0]));
    TEST_ASSERT(0 == close(sock[1]));
}

/**
 * We can write and read a contact form get count request.
 */
TEST(database_read_write_contact_form_get_count_request)
{
    int sock[2];
    uint32_t request_id = 1234;

    /* we can create a socket pair. */
    TEST_ASSERT(0 == socketpair(AF_UNIX, SOCK_STREAM, 0, sock));

    /* write the get count request. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == database_write_contact_form_get_count_request(sock[0]));

    /* read the request id. */
    TEST_ASSERT(
        STATUS_SUCCESS == database_read_request_id(&request_id, sock[1]));

    /* the request id matches. */
    TEST_ASSERT(DATABASE_REQUEST_ID_CONTACT_FORM_GET_COUNT == request_id);

    /* clean up. */
    TEST_ASSERT(0 == close(sock[0]));
    TEST_ASSERT(0 == close(sock[1]));
}

/**
 * We can write and read a contact form get count response.
 */
TEST(database_read_write_contact_form_get_count_response)
{
    int sock[2];
    const uint32_t WRITE_STATUS = STATUS_SUCCESS;
    const uint64_t WRITE_COUNT = 12;
    uint32_t request_id = 1234;
    uint32_t status = 4433;
    uint64_t count = 0;

    /* we can create a socket pair. */
    TEST_ASSERT(0 == socketpair(AF_UNIX, SOCK_STREAM, 0, sock));

    /* write the get count response. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == database_write_contact_form_get_count_response(
                    sock[0], WRITE_STATUS, WRITE_COUNT));

    /* read the response. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == database_read_contact_form_get_count_response(
                    &status, &count, sock[1]));

    /* the fields match. */
    TEST_EXPECT(WRITE_STATUS == status);
    TEST_EXPECT(WRITE_COUNT == count);

    /* clean up. */
    TEST_ASSERT(0 == close(sock[0]));
    TEST_ASSERT(0 == close(sock[1]));
}

/**
 * If the status is not successful, then the count is not updated.
 */
TEST(database_read_write_contact_form_get_count_response_not_successful)
{
    int sock[2];
    const uint32_t WRITE_STATUS = 4433;
    const uint64_t WRITE_COUNT = 12;
    uint32_t request_id = 1234;
    uint32_t status = 0;
    uint64_t count = 0;

    /* we can create a socket pair. */
    TEST_ASSERT(0 == socketpair(AF_UNIX, SOCK_STREAM, 0, sock));

    /* write the get count response. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == database_write_contact_form_get_count_response(
                    sock[0], WRITE_STATUS, WRITE_COUNT));

    /* read the response. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == database_read_contact_form_get_count_response(
                    &status, &count, sock[1]));

    /* The status matches. */
    TEST_EXPECT(WRITE_STATUS == status);

    /* the count is NOT updated. */
    TEST_EXPECT(WRITE_COUNT != count);

    /* clean up. */
    TEST_ASSERT(0 == close(sock[0]));
    TEST_ASSERT(0 == close(sock[1]));
}
