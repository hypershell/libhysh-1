
#pragma once

#include <hysh/hysh.h>

HYDefineInterface(hy_allocator) {
    hyresult (*allocate)(void *self, uint64_t size, void **retval);
    hyresult (*deallocate)(void *self, void *ptr);
};

HYDefineInterface(hy_reference_pool) {
    hyresult (*managed_add_ref)(void *self, hy_object *object);
    
    hyresult (*managed_de_ref)(void *self, hy_object *object);
    
    hyresult (*create_subpool)(void *self, hy_reference_pool **retval);
};

inline hyresult hy_alloc(hy_object *parent, uint64_t size, hy_object **retval) {
    hyresult result;
    
    hy_allocator *allocator = parent->base->allocator;
    hy_reference_pool *pool = parent->base->pool;
    
    hy_object *new_object;
    
    HYCall(allocator, allocate, size, (void**) &new_object);
    
    // Ignore addref error from allocator, as we assume
    // the lifetime of allocator is global.
    HYTryAddRef(allocator);
    
    new_object->base->allocator = allocator;
    
    hy_reference_pool *subpool;
    
    result = HYTryCall(pool, create_subpool, &subpool);
    if(hy_is_error(result)) {
        HYCall(allocator, deallocate, (void*) new_object);
        HYReturnError(result);
    }
    
    new_object->base->pool = subpool;
    
    *retval = new_object;
    return HY_OK;
}

inline hyresult hy_dealloc(hy_object *obj) {
    hy_reference_pool *pool = obj->base->pool;
    hy_allocator *alloc = obj->base->allocator;
    
    hyresult result1 = HYTryDeRef(pool);
    hyresult result2 = HYTryCall(alloc, deallocate, (void*) obj);
    
    return hy_stack_results(result1, result2);
}