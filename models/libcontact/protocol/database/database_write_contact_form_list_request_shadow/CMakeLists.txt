SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/close.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/prop_is_open_fd.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/socket.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/unix_shadow_init.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/protocol/database/database_write_contact_form_list_request.c
    main.c)

ADD_EXECUTABLE(model_database_write_contact_form_list_request_shadow ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_database_write_contact_form_list_request_shadow PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_database_write_contact_form_list_request_shadow
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_database_write_contact_form_list_request_shadow
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_database_write_contact_form_list_request_shadow
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS}
                 model_database_write_contact_form_list_request_shadow
    USES_TERMINAL)
