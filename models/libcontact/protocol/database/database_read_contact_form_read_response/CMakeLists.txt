SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/close.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/prop_is_open_fd.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/socket.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/unix_shadow_init.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/socket/socket_read_uint32.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/socket/socket_read_uint64.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/socket/socket_read_contact_form_data.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/socket/socket_read_contact_form_header.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/string/string_filter_no_op.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/string/string_release.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/string/prop_string_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/data/contact_form_create_nondet.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/data/contact_form_read.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/data/contact_form_extract_name_nondet.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/data/contact_form_extract_email_nondet.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/data/contact_form_extract_subject_nondet.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/data/contact_form_extract_comment_nondet.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/data/prop_valid_contact_form.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/contact_form_compute_size.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/contact_form_release.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/contact_form_verify.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/database_read_contact_form_read_response.c
    main.c)

ADD_EXECUTABLE(model_database_read_contact_form_read_response ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_database_read_contact_form_read_response PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_database_read_contact_form_read_response
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_database_read_contact_form_read_response
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_database_read_contact_form_read_response
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS} model_database_read_contact_form_read_response
    USES_TERMINAL)
