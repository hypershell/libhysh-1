
#pragma once

#include <inttypes.h>
#include <hysh/hysh.h>

HYDefineInterface(hy_data_buffer) {
    hyresult (*size)(void *self, uint64_t *retval);
    
    hyresult (*buffer)(void *self, const char** retval);
};

HYDefineChainInterface(hy_data_buffer_chain, hy_data_buffer*);

typedef hy_data_buffer hy_string;


#define HYDataBufferDeclareMethodTable(class) \
    HYDeclareMethod(class, hy_data_buffer, size, uint64_t *retval); \
    HYDeclareMethod(class, hy_data_buffer, buffer, const char** retval)

#define HYDataBufferConstructMethodTable(class) \
    HYDataBufferDeclareMethodTable(class); \
    static hy_data_buffer_methods HYMethodTableInstanceName(class, hy_data_buffer, methods) = { \
        HYClassMethodName(class, hy_data_buffer, size), \
        HYClassMethodName(class, hy_data_buffer, buffer) \
    }


