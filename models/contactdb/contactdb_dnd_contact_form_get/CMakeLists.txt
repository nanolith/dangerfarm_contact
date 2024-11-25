SET(MC_SOURCES
    ${LMDB_SOURCES}
    ${CMAKE_SOURCE_DIR}/models/shadow/contactdb/contactdb_connection_form_get.c
    ${CMAKE_SOURCE_DIR}/models/shadow/contactdb/contactdb_connection_counter_get.c
    ${CMAKE_SOURCE_DIR}/models/shadow/contactdb/contactdb_context_create_from_arguments.c
    ${CMAKE_SOURCE_DIR}/models/shadow/contactdb/contactdb_disable_signal_handler.c
    ${CMAKE_SOURCE_DIR}/models/shadow/contactdb/contactdb_has_capability.c
    ${CMAKE_SOURCE_DIR}/models/shadow/contactdb/prop_is_valid_contactdb_connection.c
    ${CMAKE_SOURCE_DIR}/models/shadow/contactdb/prop_is_valid_contactdb_context.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/data/prop_valid_contact_form.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/data/prop_valid_contact_form.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/data/contact_form_create_nondet.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/data/contact_form_extract_comment_nondet.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/data/contact_form_extract_email_nondet.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/data/contact_form_extract_name_nondet.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/data/contact_form_extract_subject_nondet.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/data/contact_form_write.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/protocol/database/database_read_contact_form_read_request_payload.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/protocol/database/database_write_contact_form_read_response.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/socket/socket_read_contact_form_header.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/socket/socket_read_contact_form_data.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/socket/socket_read_uint64.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/socket/socket_write_uint32.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/string/prop_string_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/string/string_filter.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/string/string_release.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/close.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/prop_is_open_fd.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/socket.c
    ${CMAKE_SOURCE_DIR}/src/contactdb/contactdb_connection_create.c
    ${CMAKE_SOURCE_DIR}/src/contactdb/contactdb_connection_release.c
    ${CMAKE_SOURCE_DIR}/src/contactdb/contactdb_context_release.c
    ${CMAKE_SOURCE_DIR}/src/contactdb/contactdb_dnd_contact_form_get.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/contact_form_compute_size.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/contact_form_read.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/contact_form_release.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/contact_form_verify.c
    main.c)

ADD_EXECUTABLE(model_contactdb_dnd_contact_form_get ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_contactdb_dnd_contact_form_get PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_contactdb_dnd_contact_form_get
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_contactdb_dnd_contact_form_get
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_contactdb_dnd_contact_form_get
    POST_BUILD
    COMMAND
        cbmc ${CBMC_OPTIONS} ${LMDB_UNWINDSET}
             model_contactdb_dnd_contact_form_get
    USES_TERMINAL)
