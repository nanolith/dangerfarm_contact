SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/close.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/prop_is_open_fd.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/read.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/socket.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/unix_shadow_init.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/socket_read_uint32.c
    main.c)

ADD_EXECUTABLE(model_socket_read_uint32 ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_socket_read_uint32 PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_socket_read_uint32
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_socket_read_uint32
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_socket_read_uint32
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS} model_socket_read_uint32
    USES_TERMINAL)
