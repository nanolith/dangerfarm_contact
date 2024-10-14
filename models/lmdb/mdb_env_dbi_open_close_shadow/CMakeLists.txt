SET(MC_SOURCES
    ${LMDB_SOURCES}
    main.c)

ADD_EXECUTABLE(model_mdb_env_dbi_open_close_shadow ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_mdb_env_dbi_open_close_shadow PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_mdb_env_dbi_open_close_shadow
        PRIVATE -DCBMC ${LMDB_BUILD_OPTIONS}
                -I ${CMAKE_SOURCE_DIR}/models ${C_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_mdb_env_dbi_open_close_shadow
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_mdb_env_dbi_open_close_shadow
    POST_BUILD
    COMMAND
        cbmc ${CBMC_OPTIONS} ${LMDB_UNWINDSET}
             model_mdb_env_dbi_open_close_shadow
    USES_TERMINAL)
