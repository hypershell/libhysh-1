
#include <hysh/data_buffer.h>

/*
 * A hy_string is almost the same as hy_data_buffer, except
 * that it guarantees a \0 terminator at the end of buffer
 */
HYDefineInterface(hy_string) {
    hyresult (*to_hy_data_buffer)(void *self, hy_data_buffer **retval);
    
    /*
     * Get the size of the string excluding the trailing \0
     */
    hyresult (*size)(void *self, uint64_t *retval);
    
    hyresult (*buffer)(void *self, const char** retval);
    
    hyresult (*is_equal)(void *self, const char *cstring, bool *retval);
};

HYDefineChainInterface(hy_string_chain, hy_string*);

HYDefineInterface(hy_md5_hashed_string) {
    hyresult (*to_hy_string)(void *self, hy_string **retval);
    
    hyresult (*md5_value)(void *self, uint64_t *retval);
};

HYDefineInterface(hy_string_service) {
    hyresult (*concat_string)(void *self, hy_string_chain *strings, 
                        hy_string **retval);
                        
    hyresult (*substring)(void *self, hy_string *string, 
        uint64_t start, uint64_t size, hy_string **retval);
};