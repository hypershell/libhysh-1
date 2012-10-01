
#include <hysh.h>

HYDefineInterface(hy_time) {
    
};

HYDefineInterface(hy_time_callback) {
    hyresult (*on_timeout_reached)(void *self);
};

HYDefineInterface(hy_time_manager) {
    hyresult (*now)(void *self, hy_time **retval);
    
    hyresult (*add_timer)(void *self, uint64_t milliseconds,
            hy_time_callback *callback);
};

HYDefineInterface(hy_http_time_services) {
    hyresult (*now_string)(void *self, hy_string **retval);
    
    hyresult (*strig_to_time)(void *self, hy_string *string, hy_time **retval);
    
    hyresult (*time_to_string)(void *self, hy_time *time, hy_string **retval);
};