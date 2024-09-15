#pragma once

#ifdef CBMC
#define MODEL_CONTRACT_PRECONDITION_BEGIN(function, ...) \
    inline void function_precondition_begin(function, #__VA_ARGS__) {
#define MODEL_CONTRACT_PRECONDITION_END(function) \
    }
#define MODEL_CONTRACT_POSTCONDITION_BEGIN(function, ...) \
    inline void function_precondition_begin(function, #__VA_ARGS__) {
#define MODEL_CONTRACT_POSTCONDITION_END(function) \
    }
#else
#define MODEL_CONTRACT_PRECONDITION_BEGIN(function, ...)
#define MODEL_CONTRACT_PRECONDITION_END(function)
#define MODEL_CONTRACT_POSTCONDITION_BEGIN(function, ...)
#define MODEL_CONTRACT_POSTCONDITION_END(function)
#endif
