
#pragma once

#include <hysh/hysh.h>
#include <hysh/data_buffer.h>
#include <hysh/string_table.h>
#include <hysh/unicode_string.h>

HYDefineInterface(hy_http_request_line) {
    hyresult (*http_version)(hy_self_ptr self,
                        hy_data_buffer **retval);
    
    hyresult (*request_method)(hy_self_ptr self,
                        hy_data_buffer **retval);
                            
    hyresult (*request_path)(hy_self_ptr self,
                        hy_data_buffer **retval);
                        
    hyresult (*query_string)(hy_self_ptr self,
                        hy_data_buffer **retval);
                        
    hyresult (*hostname)(hy_self_ptr self,
                        hy_data_buffer **retval);
};


HYDefineInterface(hy_http_parsed_request_line) {
    hyresult (*http_version)(hy_self_ptr self,
                        hy_data_buffer **retval);
    
    hyresult (*request_method)(hy_self_ptr self,
                        hy_data_buffer **retval);
    
    hyresult (*request_path)(hy_self_ptr self,
                        hy_unicode_string **retval);
                        
    hyresult (*query_params)(hy_self_ptr self,
                        hy_unicode_string_table **retval);
                        
    hyresult (*hostname)(hy_self_ptr self,
                        hy_unicode_string **retval);
};


HYDefineInterface(hy_http_response_line) {
    hyresult (*http_version)(hy_self_ptr self,
                        hy_data_buffer **retval);
                        
    hyresult (*status_code)(hy_self_ptr self,
                        int *retval);
                        
    hyresult (*status_message)(hy_self_ptr self,
                        hy_data_buffer **retval);
};


HYDefineInterface(hy_http_handler) {
    hyresult (*accept_http_request_channel)(hy_self_ptr self,
                        hy_http_request_channel *request_channel,
                        struct hy_http_handler_listener *listener);
};


HYDefineInterface(hy_http_response_listener) {
    hy_object_base *base;
    
    hyresult (*on_http_response_ready)(hy_self_ptr self,
                        hy_http_response_channel *response_channel);

    hyresult (*on_error)(hy_self_ptr self, hyresult error);
};


HYDefineInterface(hy_http_request_channel) {
    hyresult (*open_request_channel)(hy_self_ptr self,
                        struct hy_http_request_channel_listener *listener);

    hyresult (*on_error)(hy_self_ptr self, hyresult error);
};


HYDefineInterface(hy_http_request_channel_listener) {
    hyresult (*on_http_request_ready)(hy_self_ptr self,
                        hy_http_request_line *request_line,
                        hy_string_table *request_headers,
                        hy_data_channel *request_body);
};


HYDefineInterface(hy_http_response_channel) {
    hyresult (*open_response_channel)(hy_self_ptr self,
                        struct hy_http_response_channel_listener *listener);
};


HYDefineInterface(hy_http_response_channel_listener) {
    hyresult (*on_http_response_ready)(hy_self_ptr self,
                        hy_http_response_line *response_line,
                        hy_string_table *response_headers,
                        hy_data_channel *response_body);
};