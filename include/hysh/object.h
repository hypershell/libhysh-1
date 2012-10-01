
#pragma once

#include <hysh/helper.h>
#include <hysh/types.h>
#include <hysh/error.h>

struct hy_meta_class;
struct hy_meta_interface;
struct hy_meta_method;
struct hy_common_methods;
struct hy_allocator;

HYDefineChainInterface(hy_meta_interface_chain, struct hy_meta_interface*);
HYDefineChainInterface(hy_meta_method_chain, struct hy_meta_method*);

typedef struct hy_object_base {
    void *self;
    
    struct hy_memory_pool *pool;
    
    struct hy_common_methods *methods;

} hy_object_base;

typedef struct hy_object {
    hy_object_base *base;
} hy_object;

HYDefineChainInterface(hy_object_chain, hy_object*);


typedef struct hy_common_methods {
    hyresult (*add_ref)(void *self);

    hyresult (*de_ref)(void *self);
    
    hyresult (*metaclass)(void *self, struct hy_meta_class **retval);
    
    hyresult (*query_interface)(void *self, 
            struct hy_meta_interface *interface, hy_object **retval);

} hy_common_methods;


HYDefineInterface(hy_meta_class) {
    hyresult (*name)(void *self, const char **retval);
    
    hyresult (*description)(void *self, const char **retval);
    
    hyresult (*supported_interfaces)(void *self, hy_meta_interface_chain **retval);
};


HYDefineInterface(hy_meta_interface) {
    hyresult (*name)(void *self, const char **retval);
    
    hyresult (*description)(void *self, const char **retval);
    
    hyresult (*supported_methods)(void *self, hy_meta_method_chain **retval);
    
    hyresult (*get_method)(void *self, const char *method_name, 
                                struct hy_meta_method **retval);
};


HYDefineInterface(hy_meta_method) {
    hyresult (*name)(void *self, const char **retval);
    
    hyresult (*description)(void *self, const char **retval);
    
    hyresult (*args_count)(void *self, int *inputs_retval, int *outputs_retval);
    
    hyresult (*args)(void *self, hy_meta_interface **inputs_retval, 
                        hy_meta_interface **outputs_retval);
                        
    hyresult (*call)(void *self, hy_object **args, hy_object ***retvals);
};
