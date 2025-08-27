SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/src/contactform/contactform_context_create.c
    ${CMAKE_SOURCE_DIR}/src/contactform/contactform_context_release.c
    ${CMAKE_SOURCE_DIR}/src/contactform/contactform_context_child_cleanup.c
    ${CMAKE_SOURCE_DIR}/models/shadow/contactform/contactform_database_helper_create.c
    ${CMAKE_SOURCE_DIR}/models/shadow/contactform/prop_valid_contactform_context.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/close.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/close_fd_nop.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/fork_with_pid_tracking.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/kill_with_pid_tracking.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/prop_is_open_fd.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/prop_is_valid_unix_pid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/socketpair.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/socket.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/waitpid_with_pid_tracking.c
    main.c)

ADD_EXECUTABLE(model_contactform_contexct_child_cleanup ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_contactform_contexct_child_cleanup PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_contactform_contexct_child_cleanup
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_contactform_contexct_child_cleanup
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_contactform_contexct_child_cleanup
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS} model_contactform_contexct_child_cleanup
    USES_TERMINAL)
