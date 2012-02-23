
#pragma once

#include <hysh/object.h>
#include <hysh/data_buffer.h>

typedef unsigned long hy_codepoint_t;

struct hy_unicode_string_iterator;

HYDefineInterface(hy_unicode_string) {
    hyresult (*length)(hy_self_ptr self, hy_uint_64 *retval);
    
    hyresult (*iter)(hy_self_ptr self, 
            struct hy_unicode_string_iterator **retval);
            
    hyresult (*encoding)(hy_self_ptr self, const char ** retval);
    
    hyresult (*raw_bytes)(hy_self_ptr self, hy_data_buffer ** retval);
    
};

HYDefineInterface(hy_unicode_string_iterator) {
    hyresult (*next)(hy_self_ptr self);
    
    hyresult (*has_next)(hy_self_ptr self, hy_bool *retval);
    
    hyresult (*codepoint)(hy_self_ptr self, hy_codepoint *retval);
    
};
