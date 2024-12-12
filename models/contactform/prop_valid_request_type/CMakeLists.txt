SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/shadow/contactform/prop_valid_request_type.c
    main.c)

ADD_EXECUTABLE(model_prop_valid_request_type ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_prop_valid_request_type PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_prop_valid_request_type
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_prop_valid_request_type
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_prop_valid_request_type
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS} model_prop_valid_request_type
    USES_TERMINAL)
