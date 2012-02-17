
#include <hysh/object.h>

struct hy_reference_transversal_callback;

HYDefineInterface(hy_reference_pool) {
    hyresult (*managed_add_ref)(void *self, hy_object *object);
    
    hyresult (*managed_de_ref)(void *self, hy_object *object);
    
    hyresult (*attach_subpool)(void *self, hy_reference_pool *pool);
    
    hyresult (*detach_subpool)(void *self, hy_reference_pool *pool);
    
    hyresult (*transverse_objects)(void *self, struct hy_reference_transversal_callback *callback);
    
    hyresult (*alloc)(void *self, size_t size, void **retval);
    
    hyresult (*dealloc)(void *self, void *ptr);
};