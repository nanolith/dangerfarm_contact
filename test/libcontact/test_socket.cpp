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
 * We can read and write a uint32_t value.
 */
TEST(socket_read_write_uint32)
{
    int sock[2];
    uint32_t val_read;
    const uint32_t VAL_WRITE = 0x4321;

    /* we can create a socket pair. */
    TEST_ASSERT(0 == socketpair(AF_UNIX, SOCK_STREAM, 0, sock));

    /* write the value. */
    TEST_ASSERT(STATUS_SUCCESS == socket_write_uint32(sock[0], VAL_WRITE));

    /* read the value. */
    TEST_ASSERT(STATUS_SUCCESS == socket_read_uint32(&val_read, sock[1]));

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

/**
 * We can read and write a contact form header.
 */
TEST(socket_read_write_contact_form_header)
{
    int sock[2];
    contact_form write_header;
    contact_form hdr;
    const uint64_t NAME_SIZE = 42;
    const uint64_t EMAIL_SIZE = 17;
    const uint64_t SUBJECT_SIZE = 31;
    const uint64_t COMMENT_SIZE = 1503;

    /* we can create a socket pair. */
    TEST_ASSERT(0 == socketpair(AF_UNIX, SOCK_STREAM, 0, sock));

    /* clear and set the write header. */
    memset(&write_header, 0, sizeof(write_header));
    write_header.name_size = NAME_SIZE;
    write_header.email_size = EMAIL_SIZE;
    write_header.subject_size = SUBJECT_SIZE;
    write_header.comment_size = COMMENT_SIZE;

    /* clear the header. */
    memset(&hdr, 0, sizeof(hdr));

    /* write the header. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == socket_write_contact_form_header(sock[0], &write_header));

    /* read the header. */
    TEST_ASSERT(
        STATUS_SUCCESS == socket_read_contact_form_header(&hdr, sock[1]));

    /* verify that the read values match. */
    TEST_ASSERT(NAME_SIZE == hdr.name_size);
    TEST_ASSERT(EMAIL_SIZE == hdr.email_size);
    TEST_ASSERT(SUBJECT_SIZE == hdr.subject_size);
    TEST_ASSERT(COMMENT_SIZE == hdr.comment_size);

    /* verify that the two headers match. */
    TEST_ASSERT(0 == memcmp(&hdr, &write_header, sizeof(hdr)));

    /* clean up. */
    TEST_ASSERT(0 == close(sock[0]));
    TEST_ASSERT(0 == close(sock[1]));
}

/**
 * We can read contact data.
 */
TEST(socket_read_contact_form_data)
{
    int sock[2];
    const char DATA[] = "123456";
    const size_t DATA_SIZE = strlen(DATA) + 1;
    char data[7];

    /* clear data. */
    memset(data, 0, DATA_SIZE);

    /* we can create a socket pair. */
    TEST_ASSERT(0 == socketpair(AF_UNIX, SOCK_STREAM, 0, sock));

    /* write the data. */
    write(sock[0], DATA, DATA_SIZE);

    /* read the data. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == socket_read_contact_form_data(data, sock[1], DATA_SIZE));

    /* verify that the read values match. */
    TEST_ASSERT(0 == memcmp(data, DATA, DATA_SIZE));

    /* clean up. */
    TEST_ASSERT(0 == close(sock[0]));
    TEST_ASSERT(0 == close(sock[1]));
}

/**
 * We can read and write contact data.
 */
TEST(socket_read_write_contact_form_data)
{
    int sock[2];
    const char DATA[] = "123456";
    const size_t DATA_SIZE = strlen(DATA) + 1;
    char data[7];

    /* clear data. */
    memset(data, 0, DATA_SIZE);

    /* we can create a socket pair. */
    TEST_ASSERT(0 == socketpair(AF_UNIX, SOCK_STREAM, 0, sock));

    /* write the data. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == socket_write_contact_form_data(sock[0], DATA, DATA_SIZE));

    /* read the data. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == socket_read_contact_form_data(data, sock[1], DATA_SIZE));

    /* verify that the read values match. */
    TEST_ASSERT(0 == memcmp(data, DATA, DATA_SIZE));

    /* clean up. */
    TEST_ASSERT(0 == close(sock[0]));
    TEST_ASSERT(0 == close(sock[1]));
}
