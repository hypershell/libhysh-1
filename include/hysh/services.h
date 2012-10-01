
#include <hysh/hysh.h>

DefineInterface(hy_meta_interface_directory) {
    hy_result (*get_meta_interface)(void *self, 
            hy_interface_id interface_id, hy_meta_interface **retval);
}

DefineInterface(hy_meta_class_directory) {
    hyresult (*get_meta_class)(void *self, 
            hy_class_id class_id, hy_meta_class **retval);
};

DefineInterface(hy_service_manager) {
    
};
