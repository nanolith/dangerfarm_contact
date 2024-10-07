SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/data/contact_form_create_nondet.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/data/contact_form_extract_subject_nondet.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/data/prop_valid_contact_form.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/string/string_release.c
    ${CMAKE_SOURCE_DIR}/models/shadow/libcontact/string/prop_string_valid.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/contact_form_compute_size.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/contact_form_release.c
    ${CMAKE_SOURCE_DIR}/src/libcontact/contact_form_verify.c
    main.c)

ADD_EXECUTABLE(model_contact_form_extract_subject_nondet ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_contact_form_extract_subject_nondet PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_contact_form_extract_subject_nondet PRIVATE -DCBMC ${C_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_contact_form_extract_subject_nondet
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_contact_form_extract_subject_nondet
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS} model_contact_form_extract_subject_nondet
    USES_TERMINAL)
