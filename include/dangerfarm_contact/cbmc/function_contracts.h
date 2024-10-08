#pragma once

#define MODEL_CONTRACT_PRECONDITIONS_BEGIN1(function, ...) \
    DANGERFARM_CONTACT_BEGIN_CONTRACT_HELPER \
    inline void function ## _preconditions(__VA_ARGS__) {
#define MODEL_CONTRACT_PRECONDITIONS_BEGIN(function, ...) \
    MODEL_CONTRACT_PRECONDITIONS_BEGIN1(function, __VA_ARGS__)
#define MODEL_CONTRACT_PRECONDITIONS_END(function) \
    } \
    DANGERFARM_CONTACT_END_CONTRACT_HELPER
#define MODEL_CONTRACT_POSTCONDITIONS_BEGIN1(function, ...) \
    DANGERFARM_CONTACT_BEGIN_CONTRACT_HELPER \
    inline void function ## _postconditions(__VA_ARGS__) {
#define MODEL_CONTRACT_POSTCONDITIONS_BEGIN(function, ...) \
    MODEL_CONTRACT_POSTCONDITIONS_BEGIN1(function, __VA_ARGS__)
#define MODEL_CONTRACT_POSTCONDITIONS_END(function) \
    } \
    DANGERFARM_CONTACT_END_CONTRACT_HELPER

#ifdef CBMC
#define MODEL_CONTRACT_CHECK_PRECONDITIONS1(function, ...) \
    function ## _preconditions(__VA_ARGS__)
#define MODEL_CONTRACT_CHECK_PRECONDITIONS(function, ...) \
    MODEL_CONTRACT_CHECK_PRECONDITIONS1(function, __VA_ARGS__)
#define MODEL_CONTRACT_CHECK_POSTCONDITIONS1(function, ...) \
    function ## _postconditions(__VA_ARGS__)
#define MODEL_CONTRACT_CHECK_POSTCONDITIONS(function, ...) \
    MODEL_CONTRACT_CHECK_POSTCONDITIONS1(function, __VA_ARGS__)
#else
#define MODEL_CONTRACT_CHECK_PRECONDITIONS(function, ...) \
    ; \
    REQUIRE_SEMICOLON_HERE
#define MODEL_CONTRACT_CHECK_POSTCONDITIONS(function, ...) \
    ; \
    REQUIRE_SEMICOLON_HERE
#endif
