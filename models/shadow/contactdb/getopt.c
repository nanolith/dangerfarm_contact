#include <stddef.h>

int optind = 0;
const char* optarg = NULL;

int nondet_optmax();

static int optlen()
{
    int len = nondet_optmax();
    if (len > 5) len = 5;

    return len;
}

int nondet_char();
int nondet_option();

int getopt(int argc, char* const argv, const char* optstring)
{
    optarg = NULL;

    /* iterate a random number of times, up to 5. */
    ++optind;
    if (optind >= optlen())
    {
        return -1;
    }

    /* get the character returned. */
    int ch = nondet_char();
    switch (ch)
    {
        case 'd':
            optarg = "p2db";
            return 'd';

        case 'L':
            optarg = "p2s";
            return 'L';

        case 'r':
            switch (nondet_option())
            {
                case 0:
                    optarg = "app";
                    break;
                case 1:
                    optarg = "admin";
                    break;
                default:
                    optarg = "invalid";
                    break;
            }
            return 'r';

        case ':':
            return ':';

        default:
            return '?';
    }
}
