#pragma once

#ifdef CBMC
#define MODEL_CONTRACT_PRECONDITION_BEGIN(function, ...) \
    inline bool function_precondition_begin(function, #__VA_ARGS__) {
#define MODEL_CONTRACT_PRECONDITION_END(function) \
    }
#else
#define MODEL_CONTRACT_PRECONDITION_BEGIN(function)
#define MODEL_CONTRACT_PRECONDITION_END(function)
#endif
