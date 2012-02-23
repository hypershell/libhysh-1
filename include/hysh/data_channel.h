
#pragma once

#include <hysh/hysh.h>
#include <hysh/data_buffer.h>

struct hy_data_channel_listener;

HYDefineInterface(hy_data_channel) {
    hyresult (*open_data_channel)(void *self,
                    struct hy_data_channel_listener *listener);
                    
    hyresult (*peek_data_channel)(void *self,
                    struct hy_data_channel_listener *listener);
                    
    hyresult (*pause_data_stream)(void *self);
    
    hyresult (*resume_data_stream)(void *self,
                    struct hy_data_channel_listener *listener);

    hyresult (*close_data_channel)(void *self);
};


HYDefineInterface(hy_data_channel_listener) {
    hyresult (*on_data_receive)(void *self,
                        hy_data_buffer_chain *buffers);
                        
    hyresult (*on_data_close)(void *self, hyresult result);
};