#include <dangerfarm_contact/status_codes.h>
#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "ctool_internal.h"

/* forward decls. */
static void set_defaults(ctool_context* ctx);
static int read_args(ctool_context* ctx, int argc, char* argv[]);
static int set_string(char** str, const char* opt, const char* value);
static int set_u64(
    uint64_t* field, bool* field_set, const char* opt, const char* value);
static int decode_command(ctool_context* ctx, const char* command);
static void verify_argstr(
    int* retval, const char* str, const char* opt, const char* command);
static void verify_not_argstr(
    int* retval, const char* str, const char* opt, const char* command);
static void verify_id(
    int* retval, bool field_set, const char* opt, const char* command);
static void verify_not_id(
    int* retval, bool field_set, const char* opt, const char* command);
static int connect_local_socket(ctool_context* ctx);

/**
 * \brief Given an argument count and vector, create a ctool context.
 *
 * \param ctx               Pointer to the context pointer to be populated with
 *                          the context on success.
 * \param argc              The argument count.
 * \param argv              The argument vector.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int ctool_context_create_from_arguments(
    ctool_context** ctx, int argc, char* argv[])
{
    int retval, release_retval;
    ctool_context* tmp = NULL;

    /* allocate memory for context. */
    tmp = (ctool_context*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = ERROR_GENERAL_OUT_OF_MEMORY;
        goto done;
    }

    /* set the defaults. */
    set_defaults(tmp);

    /* read the command-line arguments. */
    retval = read_args(tmp, argc, argv);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tmp;
    }

    /* connect the socket. */
    retval = connect_local_socket(tmp);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tmp;
    }

    /* drop privileges. */
    retval = ctool_drop_privileges(tmp);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tmp;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    *ctx = tmp;
    goto done;

cleanup_tmp:
    release_retval = ctool_context_release(tmp);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}

/**
 * \brief Set the defaults for this context.
 *
 * \brief ctx           The context to set up.
 */
static void set_defaults(ctool_context* ctx)
{
    memset(ctx, 0, sizeof(*ctx));

    ctx->sock = -1;
}

/**
 * \brief Read arguments, populating the context.
 *
 * \brief ctx           The context to populate with arguments.
 * \brief argc          The argument count.
 * \brief argv          The argument vector.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
static int read_args(ctool_context* ctx, int argc, char* argv[])
{
    int retval;
    int ch;

    while ((ch = getopt(argc, argv, "L:k:n:e:s:c:")) != -1)
    {
        switch (ch)
        {
            /* local socket path option. */
            case 'L':
                retval = set_string(&ctx->socket_path, "-L", optarg);
                if (STATUS_SUCCESS != retval)
                {
                    goto done;
                }
                break;

            /* form id / key. */
            case 'k':
                retval =
                    set_u64(&ctx->form_id, &ctx->form_id_set, "-k", optarg);
                if (STATUS_SUCCESS != retval)
                {
                    goto done;
                }
                break;

            /* contact form name. */
            case 'n':
                retval = set_string(&ctx->contact_form_name, "-n", optarg);
                if (STATUS_SUCCESS != retval)
                {
                    goto done;
                }
                break;

            /* contact form e-mail. */
            case 'e':
                retval = set_string(&ctx->contact_form_email, "-e", optarg);
                if (STATUS_SUCCESS != retval)
                {
                    goto done;
                }
                break;

            /* contact form subject. */
            case 's':
                retval = set_string(&ctx->contact_form_subject, "-s", optarg);
                if (STATUS_SUCCESS != retval)
                {
                    goto done;
                }
                break;

            /* contact form comment. */
            case 'c':
                retval = set_string(&ctx->contact_form_comment, "-c", optarg);
                if (STATUS_SUCCESS != retval)
                {
                    goto done;
                }
                break;

            case '?':
                fprintf(stderr, "-%c is an invalid option.\n", optopt);
                retval = ERROR_CTOOL_BAD_PARAMETER;
                goto done;

            case ':':
                fprintf(
                    stderr, "-%c is missing a required parameter.\n", optopt);
                retval = ERROR_CTOOL_BAD_PARAMETER;
                goto done;
        }
    }

    /* skip past flags. */
    argc -= optind;
    argv += optind;

    /* there should be one remaining argument, the command. */
    if (argc != 1)
    {
        fprintf(stderr, "Error. Expecting exactly one command after flags.\n");
        retval = ERROR_CTOOL_BAD_PARAMETER;
        goto done;
    }

    /* decode the command. */
    retval = decode_command(ctx, argv[0]);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

done:
    return retval;
}

/**
 * \brief Set the given string argument, returning an error if the string
 * argument was already set.
 *
 * \param str           The string argument to set.
 * \param opt           The option being set (for error logging).
 * \param value         The value to which this argument is set.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
static int set_string(char** str, const char* opt, const char* value)
{
    /* check for dupe. */
    if (NULL != *str)
    {
        fprintf(stderr, "%s parameter used twice!\n", opt);
        return ERROR_CTOOL_BAD_PARAMETER;
    }

    /* set the socket path. */
    *str = strdup(value);
    if (NULL == *str)
    {
        fprintf(stderr, "out of memory.\n");
        return ERROR_GENERAL_OUT_OF_MEMORY;
    }

    /* success. */
    return STATUS_SUCCESS;
}

/**
 * \brief Set the given uint64 field argument and field set flag, returning an
 * error if the argument was already set or if numerical conversion failed.
 *
 * \param field         The field to set.
 * \param field_set     Flag to indicate whether this field has been set
 *                      previously.
 * \param opt           The option being set (for error logging).
 * \param value         The value to which this value is set (converted from
 *                      string to uint64).
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
static int set_u64(
    uint64_t* field, bool* field_set, const char* opt, const char* value)
{
    uintmax_t tmp;
    char* endpos = NULL;

    /* check for dupe. */
    if (*field_set)
    {
        fprintf(stderr, "%s parameter used twice!\n", opt);
        return ERROR_CTOOL_BAD_PARAMETER;
    }

    /* attempt to convert the string representation to a uint64_t. */
    errno = 0;
    tmp = strtoumax(value, &endpos, 0);
    if ((0 == tmp && 0 != errno)
     || (endpos != NULL && 0 != *endpos)
     || tmp > UINT64_MAX)
    {
        if (ERANGE == errno)
        {
            fprintf(
                stderr, "%s parameter is out of range for uint64_t.\n", opt);

            return ERROR_CTOOL_NUMBER_OUT_OF_RANGE;
        }
        else
        {
            fprintf(stderr, "%s parameter is an invalid number.\n", opt);

            return ERROR_CTOOL_BAD_NUMBER;
        }
    }

    /* success. */
    *field = tmp;
    *field_set = true;
    return STATUS_SUCCESS;
}

/**
 * \brief Attempt to decode a command from a command string, and verify that
 * required flags for the command are set.
 *
 * \param ctx               The context for this operation.
 * \param command           The command string to decode.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
static int decode_command(ctool_context* ctx, const char* command)
{
    int retval = STATUS_SUCCESS;

    /* is this an append command? */
    if (!strcmp(command, "append"))
    {
        ctx->command = CTOOL_COMMAND_APPEND;
        verify_argstr(&retval, ctx->socket_path, "-L", "append");
        verify_not_id(&retval, ctx->form_id_set, "-k", "append");
        verify_argstr(&retval, ctx->contact_form_name, "-n", "append");
        verify_argstr(&retval, ctx->contact_form_email, "-e", "append");
        verify_argstr(&retval, ctx->contact_form_subject, "-s", "append");
        verify_argstr(&retval, ctx->contact_form_comment, "-c", "append");
    }
    /* is this a get count command? */
    else if (!strcmp(command, "count"))
    {
        ctx->command = CTOOL_COMMAND_GET_COUNT;
        verify_argstr(&retval, ctx->socket_path, "-L", "count");
        verify_not_id(&retval, ctx->form_id_set, "-k", "append");
        verify_not_argstr(&retval, ctx->contact_form_name, "-n", "count");
        verify_not_argstr(&retval, ctx->contact_form_email, "-e", "count");
        verify_not_argstr(&retval, ctx->contact_form_subject, "-s", "count");
        verify_not_argstr(&retval, ctx->contact_form_comment, "-c", "count");
    }
    /* is this a list command? */
    else if (!strcmp(command, "list"))
    {
        ctx->command = CTOOL_COMMAND_LIST;
        verify_argstr(&retval, ctx->socket_path, "-L", "list");
        verify_not_id(&retval, ctx->form_id_set, "-k", "append");
        verify_not_argstr(&retval, ctx->contact_form_name, "-n", "list");
        verify_not_argstr(&retval, ctx->contact_form_email, "-e", "list");
        verify_not_argstr(&retval, ctx->contact_form_subject, "-s", "list");
        verify_not_argstr(&retval, ctx->contact_form_comment, "-c", "list");
    }
    /* is this a get command? */
    else if (!strcmp(command, "get"))
    {
        ctx->command = CTOOL_COMMAND_GET;
        verify_argstr(&retval, ctx->socket_path, "-L", "get");
        verify_id(&retval, ctx->form_id_set, "-k", "get");
        verify_not_argstr(&retval, ctx->contact_form_name, "-n", "get");
        verify_not_argstr(&retval, ctx->contact_form_email, "-e", "get");
        verify_not_argstr(&retval, ctx->contact_form_subject, "-s", "get");
        verify_not_argstr(&retval, ctx->contact_form_comment, "-c", "get");
    }
    /* is this a delete command? */
    else if (!strcmp(command, "delete"))
    {
        ctx->command = CTOOL_COMMAND_DELETE;
        verify_argstr(&retval, ctx->socket_path, "-L", "delete");
        verify_id(&retval, ctx->form_id_set, "-k", "delete");
        verify_not_argstr(&retval, ctx->contact_form_name, "-n", "delete");
        verify_not_argstr(&retval, ctx->contact_form_email, "-e", "delete");
        verify_not_argstr(&retval, ctx->contact_form_subject, "-s", "delete");
        verify_not_argstr(&retval, ctx->contact_form_comment, "-c", "delete");
    }
    else
    {
        fprintf(stderr, "Error. %s is not a valid command.\n", command);
        retval = ERROR_CTOOL_INVALID_COMMAND;
    }

    return retval;
}

/**
 * \brief Verify that a given string argument is set for a given command.
 *
 * \param retval            Set this to an error on failure.
 * \param str               The string field to check.
 * \param opt               The option required.
 * \param command           The command being verified.
 */
static void verify_argstr(
    int* retval, const char* str, const char* opt, const char* command)
{
    if (NULL == str)
    {
        fprintf(stderr, "Error. %s expected with %s command.\n", opt, command);
        *retval = ERROR_CTOOL_BAD_PARAMETER;
    }
}

/**
 * \brief Verify that a given string argument is NOT set for a given command.
 *
 * \param retval            Set this to an error on failure.
 * \param str               The string field to check.
 * \param opt               The option required.
 * \param command           The command being verified.
 */
static void verify_not_argstr(
    int* retval, const char* str, const char* opt, const char* command)
{
    if (NULL != str)
    {
        fprintf(
            stderr, "Error. %s specified but not used with %s command.\n",
            opt, command);
        *retval = ERROR_CTOOL_BAD_PARAMETER;
    }
}

/**
 * \brief Verify that a given id field argument is set for a given command.
 *
 * \param retval            Set this to an error on failure.
 * \param field_set         Flag indicating whether the field is set.
 * \param opt               The option required.
 * \param command           The command being verified.
 */
static void verify_id(
    int* retval, bool field_set, const char* opt, const char* command)
{
    if (!field_set)
    {
        fprintf(stderr, "Error. %s expected with %s command.\n", opt, command);
        *retval = ERROR_CTOOL_BAD_PARAMETER;
    }
}

/**
 * \brief Verify that a given id field argument is NOT set for a given command.
 *
 * \param retval            Set this to an error on failure.
 * \param field_set         Flag indicating whether the field is set.
 * \param opt               The option required.
 * \param command           The command being verified.
 */
static void verify_not_id(
    int* retval, bool field_set, const char* opt, const char* command)
{
    if (field_set)
    {
        fprintf(
            stderr, "Error. %s specified but not used with %s command.\n", opt,
            command);
        *retval = ERROR_CTOOL_BAD_PARAMETER;
    }
}

/**
 * \brief Attempt to connect to the local socket specified by the command-line
 * options.
 *
 * \param ctx               The context for this operation.
 */
static int connect_local_socket(ctool_context* ctx)
{
    int retval;
    struct sockaddr_un addr;

    /* verify that the length of the socket path does not exceed sun_path. */
    if (strlen(ctx->socket_path) + 1 > sizeof(addr.sun_path))
    {
        fprintf(
            stderr, "%s is too long for a socket path.\n", ctx->socket_path);
        retval = ERROR_CTOOL_SOCKET_PATH_TOO_LONG;
        goto done;
    }

    /* set the connect address. */
    addr.sun_family = AF_UNIX;
    strlcpy(addr.sun_path, ctx->socket_path, sizeof(addr.sun_path));

    /* create a socket. */
    ctx->sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (ctx->sock < 0)
    {
        fprintf(stderr, "Socket creation failure.\n");
        retval = ERROR_CTOOL_SOCKET_FAILURE;
        goto done;
    }

    /* connect this socket. */
    retval = connect(ctx->sock, (struct sockaddr*)&addr, sizeof(addr));
    if (retval < 0)
    {
        fprintf(stderr, "Could not connect to %s.\n", ctx->socket_path);
        retval = ERROR_CTOOL_CONNECT_FAILURE;
        goto cleanup_sock;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

cleanup_sock:
    close(ctx->sock);
    ctx->sock = -1;

done:
    return retval;
}
