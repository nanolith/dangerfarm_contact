SET(MC_SOURCES
    ${LMDB_SOURCES}
    ${CMAKE_SOURCE_DIR}/src/contactdb/contactdb_connection_counter_get_and_increment.c
    ${CMAKE_SOURCE_DIR}/src/contactdb/contactdb_connection_create.c
    ${CMAKE_SOURCE_DIR}/src/contactdb/contactdb_connection_release.c
    main.c)

ADD_EXECUTABLE(
    model_contactdb_connection_counter_get_and_increment ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_contactdb_connection_counter_get_and_increment PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_contactdb_connection_counter_get_and_increment
        PRIVATE -DCBMC ${LMDB_BUILD_OPTIONS} ${C_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_contactdb_connection_counter_get_and_increment
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_contactdb_connection_counter_get_and_increment
    POST_BUILD
    COMMAND
        cbmc ${CBMC_OPTIONS} ${LMDB_UNWINDSET}
             model_contactdb_connection_counter_get_and_increment
    USES_TERMINAL)
