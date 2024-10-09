SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/close.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/prop_is_open_fd.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/socket.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/unix_shadow_init.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/socket/socket_read_uint32.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/string/string_filter_no_op.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/string/string_release.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/string/prop_string_valid.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/database_read_database_truncate_response.c
    main.c)

ADD_EXECUTABLE(model_database_read_database_truncate_response ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_database_read_database_truncate_response PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_database_read_database_truncate_response
        PRIVATE -DCBMC -I ${CMAKE_SOURCE_DIR}/models ${C_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_database_read_database_truncate_response
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_database_read_database_truncate_response
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS} model_database_read_database_truncate_response
    USES_TERMINAL)
