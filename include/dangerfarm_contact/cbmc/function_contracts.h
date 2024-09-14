#pragma once

#ifdef CBMC
#define MODEL_CONTRACT_PRECONDITION_BEGIN(function, ...) \
    inline bool function_precondition_begin(function, #__VA_ARGS__) {
#else
#define MODEL_CONTRACT_PRECONDITION_BEGIN(function)
#endif
