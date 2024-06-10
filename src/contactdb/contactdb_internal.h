#pragma once

#include <stdbool.h>
#include <stdint.h>

#define DATABASE_CAPABILITY_CONTACT_FORM_APPEND                 0x0001
#define DATABASE_CAPABILITY_CONTACT_FORM_GET                    0x0002
#define DATABASE_CAPABILITY_CONTACT_FORM_DELETE                 0x0004
#define DATABASE_CAPABILITY_CONTACT_FORM_COUNT_GET              0x0008
#define DATABASE_CAPABILITY_CONTACT_FORM_LIST_GET               0x0010
#define DATABASE_CAPABILITY_TRUNCATE                            0x0020

#define DATABASE_ROLE_WEB_APPLICATION \
    (DATABASE_CAPABILITY_CONTACT_FORM_APPEND)

#define DATABASE_ROLE_ADMIN_TOOL \
    (   DATABASE_CAPABILITY_CONTACT_FORM_APPEND \
      | DATABASE_CAPABILITY_CONTACT_FORM_GET \
      | DATABASE_CAPABILITY_CONTACT_FORM_DELETE \
      | DATABASE_CAPABILITY_CONTACT_FORM_COUNT_GET \
      | DATABASE_CAPABILITY_CONTACT_FORM_LIST_GET \
      | DATABASE_CAPABILITY_TRUNCATE)

typedef struct contactdb_connection contactdb_connection;

typedef struct contactdb_context contactdb_context;
struct contactdb_context
{
    char* db_path;
    char* socket_path;
    int sock;
    bool listen_socket;
    uint64_t root_capabilities;
    contactdb_connection* db;
};

/**
 * \brief Given an argument count and vector, create a contactdb context.
 *
 * \brief ctx           Pointer to the context pointer to be populated with the
 *                      context on success.
 * \brief argc          The argument count.
 * \brief argv          The argument vector.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactdb_context_create_from_arguments(
    contactdb_context* ctx, int argc, char* argv[]);

/**
 * \brief Release a contactdb context.
 *
 * \param ctx           The context to release.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactdb_context_release(contactdb_context* ctx);
