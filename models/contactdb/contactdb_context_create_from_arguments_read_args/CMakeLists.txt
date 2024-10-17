SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/string/prop_string_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/string/string_release.c
    ${CMAKE_SOURCE_DIR}/models/shadow/stdlib/strdup.c
    ${CMAKE_SOURCE_DIR}/models/shadow/stdlib/strcmp.c
    ${CMAKE_SOURCE_DIR}/models/shadow/contactdb/contactdb_context_create_from_arguments_set_string.c
    ${CMAKE_SOURCE_DIR}/models/shadow/contactdb/contactdb_connection_release_nop.c
    ${CMAKE_SOURCE_DIR}/models/shadow/contactdb/getopt.c
    ${CMAKE_SOURCE_DIR}/models/shadow/contactdb/contactdb_disable_signal_handler.c
    ${CMAKE_SOURCE_DIR}/models/../src/contactdb/contactdb_context_create_from_arguments_read_args.c
    ${CMAKE_SOURCE_DIR}/models/../src/contactdb/contactdb_context_release.c
    main.c)

ADD_EXECUTABLE(
    model_contactdb_context_create_from_arguments_read_args ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_contactdb_context_create_from_arguments_read_args PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_contactdb_context_create_from_arguments_read_args
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_contactdb_context_create_from_arguments_read_args
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_contactdb_context_create_from_arguments_read_args
    POST_BUILD
    COMMAND
        cbmc ${CBMC_OPTIONS}
             model_contactdb_context_create_from_arguments_read_args
    USES_TERMINAL)
