#pragma once

#ifdef CBMC
#define MODEL_CONTRACT_PRECONDITION_BEGIN1(function, ...) \
    inline void function ## _precondition_begin(__VA_ARGS__) {
#define MODEL_CONTRACT_PRECONDITION_BEGIN(function, ...) \
    MODEL_CONTRACT_PRECONDITION_BEGIN1(function, __VA_ARGS__)
#define MODEL_CONTRACT_PRECONDITION_END(function) \
    }
#define MODEL_CONTRACT_POSTCONDITION_BEGIN1(function, ...) \
    inline void function ## _postcondition_begin(__VA_ARGS__) {
#define MODEL_CONTRACT_POSTCONDITION_BEGIN(function, ...) \
    MODEL_CONTRACT_POSTCONDITION_BEGIN1(function, __VA_ARGS__)
#define MODEL_CONTRACT_POSTCONDITION_END(function) \
    }
#else
#define MODEL_CONTRACT_PRECONDITION_BEGIN(function, ...)
#define MODEL_CONTRACT_PRECONDITION_END(function)
#define MODEL_CONTRACT_POSTCONDITION_BEGIN(function, ...)
#define MODEL_CONTRACT_POSTCONDITION_END(function)
#endif
