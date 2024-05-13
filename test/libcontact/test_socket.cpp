#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>
#include <minunit/minunit.h>
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
