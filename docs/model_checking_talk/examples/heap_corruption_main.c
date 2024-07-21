#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>

typedef struct customer customer;

struct customer
{
    uint32_t customer_id;
    char customer_name[0];
};

#define MAX_CUSTOMER_SIZE 100

int main(int argc, char* argv[])
{
    int retval;
    int desc = -1;
    char buffer[5];
    uint32_t name_size;
    customer* tmp = NULL;

    /* open a file. */
    desc = open("/tmp/file.txt", O_CREAT | O_RDWR);
    if (desc < 0)
    {
        retval = 1;
        goto done;
    }

    /* read the name size. */
    ssize_t read_bytes = read(desc, &name_size, sizeof(name_size));
    if (read_bytes < 0 || read_bytes != sizeof(name_size))
    {
        retval = 1;
        goto cleanup_desc;
    }

    /* compute the data size. */
    uint32_t data_size = name_size + sizeof(customer) + 1;

    /* sanity check the size. */
    if (data_size > MAX_CUSTOMER_SIZE)
    {
        retval = 1;
        goto cleanup_desc;
    }

    /* allocate memory. */
    tmp = (customer*)malloc(data_size);
    if (NULL == tmp)
    {
        retval = 1;
        goto cleanup_desc;
    }

    /* read the customer record. */
    read_bytes = read(desc, tmp, data_size);
    if (read_bytes < data_size)
    {
        retval = 1;
        goto cleanup_tmp;
    }

    /* ASCII zero the record. */
    tmp->customer_name[name_size] = 0;

    /* success. */
    retval = 0;
    goto cleanup_tmp;

cleanup_tmp:
    free(tmp);

cleanup_desc:
    /* close the file. */
    retval = close(desc);
    if (retval < 0)
    {
        retval = 1;
    }

done:
    return retval;

}
