#pragma once

#define MODEL_CONTRACT_PRECONDITION_BEGIN1(function, ...) \
    DANGERFARM_CONTACT_BEGIN_CONTRACT_HELPER \
    inline void function ## _precondition(__VA_ARGS__) {
#define MODEL_CONTRACT_PRECONDITION_BEGIN(function, ...) \
    MODEL_CONTRACT_PRECONDITION_BEGIN1(function, __VA_ARGS__)
#define MODEL_CONTRACT_PRECONDITION_END(function) \
    } \
    DANGERFARM_CONTACT_END_CONTRACT_HELPER
#define MODEL_CONTRACT_POSTCONDITION_BEGIN1(function, ...) \
    DANGERFARM_CONTACT_BEGIN_CONTRACT_HELPER \
    inline void function ## _postcondition(__VA_ARGS__) {
#define MODEL_CONTRACT_POSTCONDITION_BEGIN(function, ...) \
    MODEL_CONTRACT_POSTCONDITION_BEGIN1(function, __VA_ARGS__)
#define MODEL_CONTRACT_POSTCONDITION_END(function) \
    } \
    DANGERFARM_CONTACT_END_CONTRACT_HELPER
