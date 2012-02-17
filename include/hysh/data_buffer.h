
#pragma once

#include <hysh/object.h>
#include <hysh/chain.h>

HYDefineInterface(hy_data_buffer) {
    hyresult (*size)(void *self, size_t *retval);
    
    hyresult (*buffer)(void *self, const char** retval);
};

typedef hy_data_buffer hy_string;

#define HYDataBufferDeclareMethods(class) \
    HYDeclareMethod(class, hy_data_buffer, size, size_t *retval); \
        HYDeclareMethod(class, hy_data_buffer, buffer, const char** retval)

#define HYDataBufferDefineMethodStruct(class) \
    HYDataBufferDeclareMethods(class); \
    static hy_data_buffer_methods HYConcat3(class, hy_data_buffer, methods) = { \
        HYClassMethodName(class, hy_data_buffer, size), \
        HYClassMethodName(class, hy_data_buffer, buffer) \
    }

HYDefineChain(hy_data_buffer_chain, hy_data_buffer*);

