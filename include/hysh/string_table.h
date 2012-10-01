
#pragma once

#include <hysh/hysh.h>
#include <hysh/data_buffer.h>
#include <hysh/unicode_string.h>

struct hy_string_table_visitor;

HYDefineInterface(hy_string_table) {
    hyresult (*has_value)(void *self, hy_string *key, bool *retval);
    
    hyresult (*get_value)(hy_self_ptr self,
                        hy_string *key,
                        hy_string **retval);
                        
    hyresult (*accept_table_visitor)(hy_self_ptr self,
                        struct hy_string_table_visitor *visitor);

};


HYDefineInterface(hy_string_table_visitor) {
    hyresult (*visit_entry)(hy_self_ptr self,
                        hy_data_buffer *key,
                        hy_data_buffer *value);
};


HYDefineInterface(hy_unicode_string_table) {
    hyresult (*get_value)(hy_self_ptr self,
                        hy_unicode_string *key,
                        hy_unicode_string **retval);
                        
    hyresult (*accept_table_visitor)(hy_self_ptr self,
                        struct hy_unicode_string_table_visitor *visitor);
                        
};


HYDefineInterface(hy_unicode_string_table_visitor) {
    hyresult (*visit_entry)(hy_self_ptr self,
                        hy_unicode_string *key,
                        hy_unicode_string *value);

};
