SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/shadow/contactdb/contactdb_context_create_from_arguments_bind_local_socket.c
    ${CMAKE_SOURCE_DIR}/models/shadow/contactdb/contactdb_context_create_from_arguments_read_args.c
    ${CMAKE_SOURCE_DIR}/models/shadow/contactdb/contactdb_connection_create.c
    ${CMAKE_SOURCE_DIR}/models/shadow/contactdb/contactdb_connection_release_nop.c
    ${CMAKE_SOURCE_DIR}/models/shadow/contactdb/contactdb_disable_signal_handler.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/string/prop_string_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/string/string_release.c
    ${CMAKE_SOURCE_DIR}/src/contactdb/contactdb_context_create_from_arguments.c
    ${CMAKE_SOURCE_DIR}/src/contactdb/contactdb_context_release.c
    main.c)

ADD_EXECUTABLE(model_contactdb_context_create_from_arguments ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_contactdb_context_create_from_arguments PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_contactdb_context_create_from_arguments
        PRIVATE -DCBMC ${LMDB_BUILD_OPTIONS} ${C_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_contactdb_context_create_from_arguments
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_contactdb_context_create_from_arguments
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS} model_contactdb_context_create_from_arguments
    USES_TERMINAL)
