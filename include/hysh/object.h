
#pragma once

#include <hysh/helper.h>
#include <hysh/types.h>
#include <hysh/error.h>

struct hy_meta_class;
struct hy_meta_interface;
struct hy_meta_method;
struct hy_common_methods;

HYDefineChain(hy_meta_interface_chain, struct hy_meta_interface*);
HYDefineChain(hy_meta_method_chain, struct hy_meta_method*);

typedef struct hy_object {
    void *self;
    
    struct hy_common_methods *common_methods;
} hy_object;

HYDefineChain(hy_object_chain, hy_object*);


typedef struct hy_common_methods {
    hyresult (*metaclass)(void *self, struct hy_metaclass **retval);
    
    hyresult (*add_ref)(void *self, hy_refcount_t *retval);

    hyresult (*de_ref)(void *self, hy_refcount_t *retval);
    
    hyresult (*query_interface)(void *self, hy_metainterface *interface, void **retval);
    
    hyresult (*is_multithreaded)(void *self, hy_bool *retval);

} hy_common_methods;


HYDefineInterface(hy_meta_class) {
    hyresult (*name)(void *self, const char **retval);
    
    hyresult (*description)(void *self, const char **retval);
    
    hyresult (*supported_interfaces)(void *self, hy_meta_interface_chain **retval);
    
    hyresult (*call_method)(void *self, hy_object *object, 
                hy_meta_interface *interface, hy_meta_method *method, 
                hy_object_chain *args, hy_object_chain **retvals);
};


HYDefineInterface(hy_meta_interface) {
    hyresult (*name)(void *self, const char **retval);
    
    hyresult (*description)(void *self, const char **retval);
    
    hyresult (*supported_methods)(void *self, hy_meta_method_chain **retval);
};


HYDefineInterface(hy_meta_method) {
    hyresult (*name)(void *self, const char **retval);
    
    hyresult (*description)(void *self, const char **retval);
    
    hyresult (*args)(void *self, hy_meta_interface_chain **inputs_retval, 
                        hy_meta_interface_chain **outputs_retval);
};


void hy_add_ref(hy_generic_object *obj) {
    if(obj) {
        obj->base->base_methods->add_ref(obj->self);
    }
}

void hy_de_ref(hy_generic_object **obj) {
    if(*obj) {
        (*obj)->base->base_methods->de_ref((*obj)->self);
        (*obj) = 0;
    }
}

void* hy_query_interface(hy_object *obj, hy_interface_id iid) {
    if(obj) {
        hy_metaclass *metaclass = obj->base->base_methods->metaclass(obj->self);
        void *retval = 0;
        hyresult result = metaclass->query_interface(metaclass->self, obj, iid, &retval);
        return retval;
    } else {
        return 0;
    }
}

