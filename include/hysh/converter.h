
#include <hysh/hysh.h>

HYDefineInterface(hy_object_converter) {
    hyresult (*convert_object)(void *self, hy_object *object, hy_object **retval);
};

HYDefineInterface(hy_converter_service) {
    hyresult (*get_converter)(void *self, hy_meta_interface *from_interface, 
            hy_meta_interface *to_interface, hy_object_converter **retval);
};