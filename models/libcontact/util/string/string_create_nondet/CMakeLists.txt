SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/string/prop_string_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/string/string_create_nondet.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/string/string_release.c
    main.c)

ADD_EXECUTABLE(model_string_create_nondet ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_string_create_nondet PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_string_create_nondet PRIVATE -DCBMC ${C_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_string_create_nondet
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_string_create_nondet
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS} model_string_create_nondet
    USES_TERMINAL)
