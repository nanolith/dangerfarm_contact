SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/shadow/contactform/prop_valid_contactform_context.c
    main.c)

ADD_EXECUTABLE(model_prop_valid_contactform_context ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_prop_valid_contactform_context PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_prop_valid_contactform_context
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_prop_valid_contactform_context
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_prop_valid_contactform_context
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS} model_prop_valid_contactform_context
    USES_TERMINAL)
