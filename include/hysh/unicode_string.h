
#pragma once

#include <hysh/object.h>
#include <hysh/data_buffer.h>

typedef unsigned long hy_codepoint_t;

struct hy_unicode_string_iterator;

HYDefineChainInterface(hy_codepoint_chain, hy_codepoint_t);

HYDefineInterface(hy_unicode_string) {
    hyresult (*codepoint_length)(void *self, hy_uint_64 *retval);
    
    hyresult (*codepoint_iter)(void *self, hy_codepoint_chain **retval);
            
    hyresult (*encoding)(void *self, const char ** retval);
    
    hyresult (*raw_bytes)(void *self, hy_data_buffer ** retval);
};

HYDefineInterface(hy_unicode_string_builder) {
    hyresult (*append_codepoint)(void *self, hy_codepoint_t codepoint);
    
    hyresult (*generate_string)(void *self, hy_unicode_string **retval);
};

HYDefineInterface(hy_unicode_common_service) {
    hyresult (*make_unicode_string_builder)(void *self, 
                hy_unicode_string_builder **retval);
    
    hyresult (*has_equal_codepoint_sequence)(void *self, 
                hy_codepoint_chain *codepoints1, 
                hy_codepoint_chain *codepoints2, bool *retval);
                
    hyresult (*has_equal_unicode_characters)(void *self,
                hy_codepoint_chain *codepoints1, 
                hy_codepoint_chain *codepoints2, bool *retval);
    
    hyresult (*is_unicode_less_than)(void *self,
                hy_codepoint_chain *codepoints1, 
                hy_codepoint_chain *codepoints2, bool *retval);
};

HYDefineInterface(hy_unicode_normalization_service) {
    hyresult (*nfd_normalize)(void *self, hy_codepoint_chain *codepoints,
                hy_unicode_string_builder *builder);
    hyresult (*nfc_normalize)(void *self, hy_codepoint_chain *codepoints,
                hy_unicode_string_builder *builder);

    hyresult (*nfkd_normalize)(void *self, hy_codepoint_chain *codepoints,
                hy_unicode_string_builder *builder);
                
    hyresult (*nfkc_normalize)(void *self, hy_codepoint_chain *codepoints,
                hy_unicode_string_builder *builder);
};