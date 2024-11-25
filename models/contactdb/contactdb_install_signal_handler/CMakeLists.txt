SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/shadow/contactdb/contactdb_context_create_from_arguments.c
    ${CMAKE_SOURCE_DIR}/models/shadow/contactdb/contactdb_connection_create.c
    ${CMAKE_SOURCE_DIR}/models/shadow/contactdb/contactdb_connection_release_nop.c
    ${CMAKE_SOURCE_DIR}/models/shadow/contactdb/prop_is_valid_contactdb_connection_stub.c
    ${CMAKE_SOURCE_DIR}/models/shadow/contactdb/prop_is_valid_contactdb_context.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/string/prop_string_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/string/string_release.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/sigemptyset.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/sigaction.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/socket.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/close.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/prop_is_open_fd.c
    ${CMAKE_SOURCE_DIR}/src/contactdb/contactdb_install_signal_handler.c
    ${CMAKE_SOURCE_DIR}/src/contactdb/contactdb_context_release.c
    ${CMAKE_SOURCE_DIR}/src/contactdb/contactdb_disable_signal_handler.c
    main.c)

ADD_EXECUTABLE(model_contactdb_install_signal_handler ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_contactdb_install_signal_handler PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_contactdb_install_signal_handler
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_contactdb_install_signal_handler
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_contactdb_install_signal_handler
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS} model_contactdb_install_signal_handler
    USES_TERMINAL)
