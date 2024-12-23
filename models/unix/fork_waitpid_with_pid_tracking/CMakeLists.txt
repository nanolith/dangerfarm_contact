SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/fork_with_pid_tracking.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/waitpid_with_pid_tracking.c
    main.c)

ADD_EXECUTABLE(model_unix_fork_waitpid_with_pid_tracking ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_unix_fork_waitpid_with_pid_tracking PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_unix_fork_waitpid_with_pid_tracking
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_unix_fork_waitpid_with_pid_tracking
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_unix_fork_waitpid_with_pid_tracking
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS} model_unix_fork_waitpid_with_pid_tracking
    USES_TERMINAL)
