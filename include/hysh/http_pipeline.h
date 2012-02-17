
#pragma once

#include <hysh/http.h>
#include <hysh/chain.h>

HYDefineInterface(hy_http_pipeline_node) {
    hyresult (*open_http_pipeline_node)(hy_self_ptr self,
                        hy_string_table *request_headers,
                        hy_data_channel *request_body,
                        hy_http_response_listener *listener);
};

HYDefineChain(hy_http_pipeline_chain, hy_http_pipeline_node*);


HYDefineInterface(hy_http_pipeline_factory) {
    hyresult (*create_http_pipeline)(hy_self_ptr self,
                        hy_http_pipeline_chain *nodes, 
                        hy_http_pipeline_node **retval);
    
    hyresult (*create_filtered_http_pipeline)(hy_self_ptr self,
                        hy_http_pipeline_chain *before_filters,
                        hy_http_pipeline_chain *main_pipeline,
                        hy_http_pipeline_chain *after_filters,
                        hy_http_pipeline_node **retval);
};


HYDefineInterface(hy_http_handler_to_pipeline_converter) {
    hyresult (*create_pipeline_node)(hy_self_ptr self,
                        hy_http_handler *handler,
                        hy_http_request_line *request_line,
                        hy_string_table *request_headers);                       
};