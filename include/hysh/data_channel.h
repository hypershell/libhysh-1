
#pragma once

#include <hysh/hysh.h>
#include <hysh/data_buffer.h>

struct hy_downstream_data_channel_callback;
struct hy_upstream_data_channel_callback;

HYDefineInterface(hy_downstream_data_channel) {
    hyresult (*receive_data)(void *self,
            struct hy_downstream_data_channel_callback *callback);
            
    hyresult (*close_channel)(void *self, hyresult result);
};

HYDefineInterface(hy_downstream_data_channel_listener) {
    hyresult (*on_data_receive)(void *self,
                hy_data_buffer *buffer);
                        
    hyresult (*on_data_close)(void *self, hyresult result);
};

HYDefineInterface(hy_upstream_data_channel) {
    hyresult (*to_downstream_data_channel_listener)(void *self, 
                hy_downstream_data_channel_listener **retval);
    
    hyresult (*prepare_send)(void *self, 
                hy_upstream_data_channel_callback *callback);
    
    hyresult (*send_data)(void *self, 
                hy_data_buffer *buffer, struct hy_upstream_data_channel_callback *callback);
            
    hyresult (*close_channel)(void *self, hyresult result);
};

HYDefineInterface(hy_upstream_data_channel_listener) {
    hyresult (*on_next_data_ready_send)(void *self);
            
    hyresult (*on_data_close)(void *self, hyresult result);
};

HYDefineInterface(hy_data_channel_factory) {
    hyresult (*create_dual_channel_pipe)(void *self,
            hy_upstream_data_channel **ret_upstream,
            hy_downstream_data_channel **ret_downstream);
};

HYDefineInterface(hy_channel_copy_maker) {
    hyresult (*make_channel_copy)(void *self, hy_downstream_data_channel **ret_clone);
};

HYDefineInterface(hy_copyable_channel) {
    hyresult (*get_copy_maker)(void *self, hy_channel_copier **retval);
};