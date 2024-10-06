SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/data/prop_valid_contact_form.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/string/prop_string_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/string/string_create_nondet.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/string/string_release.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/contact_form_compute_size.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/contact_form_create.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/contact_form_extract_name.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/contact_form_extract_email.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/contact_form_extract_subject.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/contact_form_extract_comment.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/contact_form_release.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/contact_form_verify.c
    main.c)

ADD_EXECUTABLE(model_contact_form_create_release ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_contact_form_create_release PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_contact_form_create_release PRIVATE -DCBMC ${C_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_contact_form_create_release
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_contact_form_create_release
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS} model_contact_form_create_release
    USES_TERMINAL)
