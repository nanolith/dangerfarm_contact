SET(MC_SOURCES
    ${LMDB_SOURCES}
    ${CMAKE_SOURCE_DIR}/models/shadow/contactdb/contactdb_connection_counter_get_and_decrement.c
    ${CMAKE_SOURCE_DIR}/models/shadow/contactdb/prop_is_valid_counter_id.c
    ${CMAKE_SOURCE_DIR}/models/shadow/contactdb/prop_is_valid_contactdb_connection.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/data/contact_form_create_nondet.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/string/prop_string_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/data/prop_valid_contact_form.c
    ${CMAKE_SOURCE_DIR}/src/contactdb/contactdb_connection_create.c
    ${CMAKE_SOURCE_DIR}/src/contactdb/contactdb_connection_release.c
    ${CMAKE_SOURCE_DIR}/src/contactdb/contactdb_connection_form_delete.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/contact_form_compute_size.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/contact_form_release.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/contact_form_verify.c
    main.c)

ADD_EXECUTABLE(model_contactdb_connection_form_delete ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_contactdb_connection_form_delete PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_contactdb_connection_form_delete
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_contactdb_connection_form_delete
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_contactdb_connection_form_delete
    POST_BUILD
    COMMAND
        cbmc ${CBMC_OPTIONS} ${LMDB_UNWINDSET}
             model_contactdb_connection_form_delete
    USES_TERMINAL)
