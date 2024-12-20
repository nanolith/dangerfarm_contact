SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/shadow/kcgi/prop_valid_request_method.c
    main.c)

ADD_EXECUTABLE(model_prop_valid_request_method ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_prop_valid_request_method PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_prop_valid_request_method
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_prop_valid_request_method
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_prop_valid_request_method
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS} "--verbosity" "9" model_prop_valid_request_method
    USES_TERMINAL)
