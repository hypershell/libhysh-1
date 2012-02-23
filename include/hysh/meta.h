
#include <object.h>
#include <helper.h>

HYDeclareClass1(hy_meta_class_impl, hy_meta_class) {
    hy_meta_interface_chain *meta_interfaces;
};

HYDeclareClass1(hy_meta_interface_impl, hy_meta_interface) {
    
};

HYDeclareClass1(hy_meta_method_impl, hy_meta_method) {
    
};

hyresult hy_meta_class_impl_init(hy_meta_class_impl *self, 
        const char *name, hy_meta_interface_chain *meta_interfaces);