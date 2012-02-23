
#pragma once

struct hy_object_base;

#define HYDoConcat2(token1, token2) token1 ## _ ## token2
#define HYDoConcat3(token1, token2, token3) token1 ## _ ## token2 ## _ ## token3
#define HYDoConcat4(token1, token2, token3, token4) token1 ## _ ## token2 ## _ ## token3 ## _ ## token4

#define HYConcat2(token1, token2) HYDoConcat2(token1, token2)
#define HYConcat3(token1, token2, token3) HYDoConcat3(token1, token2, token3)
#define HYConcat4(token1, token2, token3, token4) HYDoConcat4(token1, token2, token3, token4)

// The struct name for the interface methods struct
#define HYInterfaceMethodsStructName(interface) HYConcat2(interface, methods)

// The member variable name for the interface struct in a class struct
#define HYClassMemberInterfaceBodyName(interface) HYConcat2(interface, body)

// The static variable name for the interface methods stuct instance for a particular class
#define HYClassMemberInterfaceMethodsName(class, interface) HYConcat3(class, interface, methods)

// The implementation function name for the interface method belongs to a class
#define HYClassMethodName(class, interface, method) HYConcat3(class, interface, method)

#define HYMethodTableInstanceName(class, interface) HYConcat3(class, interface, methods_table)

// stub
#define HYGetMetaInterface(interface) NULL

#define HYDefineInterface(interface) \
    struct HYInterfaceMethodsStructName(interface); \
    typedef struct interface { \
        struct hy_object_base *base; \
        struct HYInterfaceMethodsStructName(interface)  *methods; \
    } interface; \
    struct HYInterfaceMethodsStructName(interface)

#define HYDefineChainInterface(chain_name, node_type)    \
    HYDefineInterface(chain_name) {         \
        hyresult (*value)(void *self, node_type *retval); \
          \
        hyresult (*has_next)(void *self, bool *retval); \
          \
        hyresult (*next)(void *self, chain_name **retval); \
          \
    }
    
#define HYDeclareClass1(class, interface1, private_struct) \
    typedef struct class { \
        hy_object_base  base; \
        hy_common_impl  m_hy_common_impl; \
        interface1      HYClassMemberInterfaceBodyName(interface1); \
        private_struct  private; \
    } class

#define HYDeclareMethod(class, interface, method, ...) \
    hyresult HYClassMethodName(class, interface, method) (void *self, __VA_ARGS__)

#define HYDefineMethodImpl(class, interface, method, ...) \
    hyresult HYConcat4(class, interface, method, impl) (void *self, __VA_ARGS__) \
    hyresult HYClassMethodName(class, interface, method) (void *self, __VA_ARGS__) { \
        return HYConcat4(class, interface, method, impl) (void ((class*) self, __VA_ARGS__); \
    } \
    hyresult HYConcat4(class, interface, method, impl) (class *self, __VA_ARGS__)

#define HYCallObjectMethod(class, interface, method, obj, ...) \
    HYClassMethodName(class, interface, method)(obj->base->self, __VA_ARGS__)
    
    
#define HYAtomicIncrease(count) ++count
#define HYAtomicDecrease(count) --count


#define HYDefineInterfaceInit(class, interface) \
    self->HYClassMemberInterfaceName(interface1).base = &self->base; \
    self->HYClassMemberInterfaceName(interface1).methods = &HYClassInterfaceMethodsVar(class, interface1)

#define HYCommonImplDefineMethodStruct(class) \
    static HYInterfaceMethodStructName(common) HYClassInterfaceMethodsVar(class, common) = { \
        HYClassMethodName(class, common, add_ref), \
        HYClassMethodName(class, common, de_ref), \
        HYClassMethodName(class, common, query_interface), \
        HYClassMethodName(class, common, metaclass) \
    }
    
#define HYDefineCommonImpl1(class, interface1) \
    HYCommonImplDefineRefCount(class); \
    HYCommonImplDefineQueryInterface1(class, interface1); \
    HYCommonImplDefineMethodStruct(class); \
    HYDefineMethod(class, common, interface_init) { \
        HYDefineInterfaceInit(class, interface1); \
    }
    
#define HYDefineClassInit(class, init_name, ...) \
    HYDeclareMethod(class, common, HYConcat2(do, init_name)); \
    HYDefineMethod(class, common, init_name, __VA_ARGS__) { \
        self->base.self = self; \
        self->base.common_methods = HYClassInterfaceMethodsVarName(class, common); \
        HYDoInterfaceInit(class, self); \
    }; \
    hyresult HYClassMethodName(class, common, HYConcat2(do, init_name))(class *self, __VA_ARGS__)
    

#define HYReturnError(result) return hy_add_traceback(result, __FILE__, __LINE__)

#define HYTryCall(obj, method, ...) obj->methods->method(obj->base->self, __VA_ARGS__)

#define HYCall(obj, method, ...) { \
    hyresult result = HYTryCall(obj, method, __VA_ARGS__); \
    if(hy_is_error(result)) { \
        HYReturnError(result); \
    } \
} \

#define HYTryCall0(obj, method) obj->methods->method(obj->base->self)

#define HYCall0(obj, method) { \
    hyresult result = HYTryCall(obj, method); \
    if(hy_is_error(result)) { \
        HYReturnError(result); \
    } \
} \

#define HYTryCommonCall(obj, method, ...) obj->base->methods->method(obj->base->self, __VA_ARGS__)

#define HYCommonCall(obj, method, ...) { \
    hyresult result = HYTryCommonCall(obj, method, __VA_ARGS__); \
    if(hy_is_error(result)) { \
        HYReturnError(result); \
    } \
} \

#define HYTryCommonCall0(obj, method) obj->base->methods->method(obj->base->self)

#define HYCommonCall0(obj, method) { \
    hyresult _result = HYTryCommonCall(obj, method); \
    if(hy_is_error(_result)) { \
        HYReturnError(_result); \
    } \
}


#define HYAlloc(parent_obj, class, retvar) \
    hy_alloc((hy_object*) parent_obj, sizeof(class), (hy_object**) &retvar);

#define HYAddRef(obj) HYCommonCall0(obj, add_ref)

#define HYTryAddRef(obj) HYTryCommonCall0(obj, add_ref)

#define HYDeRef(obj) HYCommonCall0(obj, de_ref)

#define HYTryDeRef(obj) HYTryCommonCall0(obj, de_ref)

#define HYAutoAddRef(pool, obj) \
HYCall(pool, managed_add_ref, (hy_object*)obj)
#define HYAutoPool(self, pool_name) \
    hy_reference_pool *pool_name; \
    { \
        hy_reference_pool *__main_pool = self->base->pool; \
        HYCall(__main_pool, create_subpool, &pool_name); \
    } \
    
#define HYAutoRelease(pool_name) \
    HYDeRef(pool_name)
    
#define HYSafeCall(pool, obj, method, ...) {
    hyresult result = HYTryCall(obj, method, __VA_ARGS__); \
    if(hy_is_error(result)) { \
        HYAutoRelease(pool); \
        HYReturnError(result); \
    } \
}

#define HYSafeCommonCall(pool, obj, method, ...) { \
    hyresult result = HYTryCommonCall(obj, method, __VA_ARGS__); \
    if(hy_is_error(result)) { \
        HYAutoRelease(pool); \
        HYReturnError(result); \
    } \
}



#define HYQueryInterface(obj, interface, retvar) \
    HYTryCommonCall(obj, query_interface, HYGetMetaInterface(interface), (hy_object**) &retvar)
    
    
