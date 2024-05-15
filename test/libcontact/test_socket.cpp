#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>
#include <minunit/minunit.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

TEST_SUITE(util_socket);

/**
 * We can read and write a uint64_t value.
 */
TEST(socket_read_write_uint64)
{
    int sock[2];
    uint64_t val_read;
    const uint64_t VAL_WRITE = 0x1234;

    /* we can create a socket pair. */
    TEST_ASSERT(0 == socketpair(AF_UNIX, SOCK_STREAM, 0, sock));

    /* write the value. */
    TEST_ASSERT(STATUS_SUCCESS == socket_write_uint64(sock[0], VAL_WRITE));

    /* read the value. */
    TEST_ASSERT(STATUS_SUCCESS == socket_read_uint64(&val_read, sock[1]));

    /* the values should match. */
    TEST_EXPECT(val_read == VAL_WRITE);

    /* clean up. */
    TEST_ASSERT(0 == close(sock[0]));
    TEST_ASSERT(0 == close(sock[1]));
}

/**
 * We can read a contact form header.
 */
TEST(socket_read_contact_form_header)
{
    int sock[2];
    contact_form hdr;
    const uint64_t NAME_SIZE = 42;
    const uint64_t EMAIL_SIZE = 17;
    const uint64_t SUBJECT_SIZE = 31;
    const uint64_t COMMENT_SIZE = 1503;

    /* we can create a socket pair. */
    TEST_ASSERT(0 == socketpair(AF_UNIX, SOCK_STREAM, 0, sock));

    /* clear the header. */
    memset(&hdr, 0, sizeof(hdr));

    /* write the values. */
    TEST_ASSERT(STATUS_SUCCESS == socket_write_uint64(sock[0], NAME_SIZE));
    TEST_ASSERT(STATUS_SUCCESS == socket_write_uint64(sock[0], EMAIL_SIZE));
    TEST_ASSERT(STATUS_SUCCESS == socket_write_uint64(sock[0], SUBJECT_SIZE));
    TEST_ASSERT(STATUS_SUCCESS == socket_write_uint64(sock[0], COMMENT_SIZE));

    /* read the header. */
    TEST_ASSERT(
        STATUS_SUCCESS == socket_read_contact_form_header(&hdr, sock[1]));

    /* verify that the read values match. */
    TEST_ASSERT(NAME_SIZE == hdr.name_size);
    TEST_ASSERT(EMAIL_SIZE == hdr.email_size);
    TEST_ASSERT(SUBJECT_SIZE == hdr.subject_size);
    TEST_ASSERT(COMMENT_SIZE == hdr.comment_size);

    /* clean up. */
    TEST_ASSERT(0 == close(sock[0]));
    TEST_ASSERT(0 == close(sock[1]));
}
