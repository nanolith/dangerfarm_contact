#pragma once

#include <stdint.h>

#ifdef   __cplusplus
extern "C" {
#endif /*__cplusplus*/

typedef struct contact_form contact_form;

/**
 * \brief Write a contact form append request to the socket.
 *
 * \param s         The socket to which this request is written.
 * \param form      The contact form to write.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int database_write_contact_form_append_request(
    int s, const contact_form* form);

/**
 * \brief Read a contact form append response from the socket.
 *
 * \param status    Pointer to receive the status code on success.
 * \param s         The socket from which this response is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int database_read_contact_form_append_response(
    uint32_t* status, int s);

/**
 * \brief Write a get count request to the socket.
 *
 * \param s         The socket to which this request is written.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int database_write_contact_form_get_count_request(int s);

/**
 * \brief Read a contact form get count response from the socket.
 *
 * \param status    Pointer to receive the status code on success.
 * \param count     Pointer to receive the count on success.
 * \param s         The socket from which this response is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int database_read_contact_form_get_count_response(
    uint32_t* status, uint64_t* count, int s);

/**
 * \brief Write a list contact forms request to the socket.
 *
 * \param s         The socket to which this request is written.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int database_write_contact_form_list_request(int s);

/**
 * \brief Read a list contact forms response from the socket.
 *
 * \param status    Pointer to receive the status code on success.
 * \param count     Pointer to receive the count of items to be read.
 * \param id_list   Pointer to receive the array of contact IDs.
 * \param s         The socket from which this response is read.
 *
 * \note id_list is updated with a dynamically allocated array which is owned
 * by the caller on success.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int database_read_contact_form_list_response(
    uint32_t* status, uint64_t* count, uint64_t** id_list, int s);

#ifdef   __cplusplus
}
#endif /*__cplusplus*/
