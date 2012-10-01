
#pragma once

#include <hysh/hysh.h>
#include <hysh/data_buffer.h>
#include <hysh/string_table.h>
#include <hysh/unicode_string.h>

HYDefineInterface(hy_http_request_line) {
    hyresult (*http_version)(void *self,
                        hy_data_buffer **retval);
    
    hyresult (*request_method)(void *self,
                        hy_data_buffer **retval);
                            
    hyresult (*request_path)(void *self,
                        hy_data_buffer **retval);
                        
    hyresult (*query_string)(void *self,
                        hy_data_buffer **retval);
                        
    hyresult (*hostname)(void *self,
                        hy_data_buffer **retval);
};

HYDefineInterface(hy_http_parsed_request_line) {
    hyresult (*http_version)(void *self,
                        hy_data_buffer **retval);
    
    hyresult (*request_method)(void *self,
                        hy_data_buffer **retval);
    
    hyresult (*request_path)(void *self,
                        hy_unicode_string **retval);
                        
    hyresult (*query_params)(void *self,
                        hy_unicode_string_table **retval);
                        
    hyresult (*hostname)(void *self,
                        hy_unicode_string **retval);
};

HYDefineInterface(hy_http_response_line) {
    hyresult (*http_version)(void *self,
                        hy_data_buffer **retval);
                        
    hyresult (*status_code)(void *self,
                        int *retval);
                        
    hyresult (*status_message)(void *self,
                        hy_data_buffer **retval);
};

HYDefineInterface(hy_http_handler) {
    hyresult (*accept_http_request_channel)(void *self,
                        hy_http_request_channel *request_channel,
                        struct hy_http_handler_listener *listener);
};

HYDefineInterface(hy_http_headers) {
    hyresult (*to_raw_headers)(void *self, hy_string_table **retval);
    
    hyresult (*content_type)(void *self, hy_string **retval);
    
    hyresult (*content_length)(void *self, int64_t *retval);
    
    hyresult (*transfer_encoding)(void *self, hy_string **retval);
};

HYDefineInterface(hy_http_response_listener) {
    hyresult (*on_http_response_ready)(void *self,
                        hy_http_response_channel *response_channel);

    hyresult (*on_error)(void *self, hyresult error);
};

HYDefineInterface(hy_http_request_channel) {
    hyresult (*open_request_channel)(void *self,
                        struct hy_http_request_channel_listener *listener);

    hyresult (*on_error)(void *self, hyresult error);
};

HYDefineInterface(hy_http_request_channel_listener) {
    hyresult (*on_http_request_ready)(void *self,
                        hy_http_request_line *request_line,
                        hy_string_table *request_headers,
                        hy_data_channel *request_body);
};

HYDefineInterface(hy_http_response_channel) {
    hyresult (*open_response_channel)(void *self,
                        struct hy_http_response_channel_listener *listener);
};

HYDefineInterface(hy_http_response_channel_listener) {
    hyresult (*on_http_response_ready)(void *self,
                        hy_http_response_line *response_line,
                        hy_string_table *response_headers,
                        hy_data_channel *response_body);
};