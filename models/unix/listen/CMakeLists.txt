SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/shadow/stdlib/strlcpy_nop.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/bind_nop.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/close.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/listen.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/prop_is_open_fd.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/socket.c
    main.c)

ADD_EXECUTABLE(model_unix_listen ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_unix_listen PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_unix_listen
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_unix_listen
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_unix_listen
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS} model_unix_listen
    USES_TERMINAL)
