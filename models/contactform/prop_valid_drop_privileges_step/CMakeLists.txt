SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/shadow/contactform/prop_valid_drop_privileges_step.c
    main.c)

ADD_EXECUTABLE(model_prop_valid_drop_privileges_step ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_prop_valid_drop_privileges_step PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_prop_valid_drop_privileges_step
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_prop_valid_drop_privileges_step
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_prop_valid_drop_privileges_step
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS} model_prop_valid_drop_privileges_step
    USES_TERMINAL)
