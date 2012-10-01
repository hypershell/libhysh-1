

HYDefineInterface(hy_big_number) {
    hyresult (*to_decimal_string)(void *self, hy_string **retval);
    
    hyresult (*to_scientific_string)(void *self, hy_string **retval);
    
    hyresult (*is_signed)(void *self, bool *retval);
    
    hyresult (*is_exponent_signed)(void *self, bool *retval);
    
    hyresult (*significand_bits_count)(void *self, uint64_t *retval);
    
    hyresult (*exponent_bits_count)(void *self, uint64_t *retval);
    
    hyresult (*significand_bits)(void *self, void **retval);
    
    hyresult (*exponent_bits)(void *self, void **retval);
};

HYDefineInterface(hy_big_integer) {
    hyresult (*to_hy_big_number)(void *self, hy_big_number **retval);
    
    hyresult (*to_decimal_string)(void *self, hy_string **retval);
    
    hyresult (*to_hex_string)(void *self, hy_string **retval);
    
    hyresult (*is_signed)(void *self, bool *retval);
    
    hyresult (*total_bits)(void *self, uint64_t *retval);
    
    hyresult (*raw_bits)(void *self, void **retval);
};

HYDefineInterface(hy_basic_big_number_service) {
    hyresult (*parse_number)(void *self, hy_string *string, hy_big_number **retval);
    
    hyresult (*addition)(void *self, 
        hy_big_number_chain *numbers, hy_big_number **retval);
};