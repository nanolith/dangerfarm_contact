SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/sigemptyset.c
    main.c)

ADD_EXECUTABLE(model_unix_sigemptyset ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_unix_sigemptyset PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_unix_sigemptyset
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_unix_sigemptyset
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_unix_sigemptyset
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS} model_unix_sigemptyset
    USES_TERMINAL)
