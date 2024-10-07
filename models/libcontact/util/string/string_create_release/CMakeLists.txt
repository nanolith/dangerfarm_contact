SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/string/prop_string_valid.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/string_create.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/string_release.c
    main.c)

ADD_EXECUTABLE(model_string_create_release ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_string_create_release PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_string_create_release PRIVATE -DCBMC ${C_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_string_create_release
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_string_create_release
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS} model_string_create_release
    USES_TERMINAL)
