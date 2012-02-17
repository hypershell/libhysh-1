

#define HYDoConcat2(token1, token2) token1 ## _ ## token2
#define HYDoConcat3(token1, token2, token3) token1 ## _ ## token2 ## _ ## token3
#define HYDoConcat4(token1, token2, token3, token4) token1 ## _ ## token2 ## _ ## token3 ## _ ## token4

#define HYConcat2(token1, token2) HYDoConcat2(token1, token2)
#define HYConcat3(token1, token2, token3) HYDoConcat3(token1, token2, token3)
#define HYConcat4(token1, token2, token3, token4) HYDoConcat4(token1, token2, token3, token4)


#define HYMethodsStructName(class_name) HYConcat2(class_name, methods)
#define HYClassMethodName(class, interface, method) HYConcat3(class, interface, method)

#define HYDefineInterface(class_name) \
    struct HYMethodsStructName(class_name); \
    typedef struct class_name { \
        hy_object *base; \
        struct HYMethodsStructName(class_name)  *methods; \
    } class_name; \
    struct HYMethodsStructName(class_name)


#define HYDefineChain(chain_name, node_type)    \
    HYDefineInterface(chain_name) {         \
        hyresult (*value)(void *self, node_type *retval); \
          \
        hyresult (*has_next)(void *self, hy_bool *retval); \
          \
        hyresult (*next)(void *self, chain_name **retval); \
          \
    }
    
#define HYDeclareClass1(class, interface1) \
    struct HYConcat2(class, private); \
    typedef struct class { \
        hy_object base; \
        hy_common_impl  m_hy_common_impl; \
        interface1      HYConcat2(m, interface1); \
        struct HYConcat2(class, private)    private; \
    } class; \
    struct HYConcat2(class, private) \

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

#define HYCommonImplRefCount(class) \
    void HYClassMethodName(class, common, add_ref)(class *self) { \
        HYAtomicIncrease(self->m_hy_common_impl.refcount); \
    } \
      \
    void HYClassMethodName(class, common, de_ref)(class *self) { \
        int new_count = HYAtomicDecrease(self->m_hy_common_impl.refcount); \
        if(new_count < 0) { \
            self->cleanup(self); \
        } \
    } \
    
#define HYCommonImplDefineMethodStruct(class) \
    static hy_common_methods HYConcat3(class, common, methods) = { \
        HYClassMethodName(class, common, add_ref), \
        HYClassMethodName(class, common, de_ref), \
        HYClassMethodName(class, common, query_interface), \
        HYClassMethodName(class, common, metaclass) \
    }
    
#define HYDefineCommonImpl1(class, interface1) \
    HYCommonImplDefineRefCount(class); \
    HYCommonImplDefineQueryInterface1(class, interface1); \
    HYCommonImplDefineMethodStruct(class); \
    
#define HYDefineClassInit(class, ...) \
    HYDeclareMethod(class, common, do_init); \
    HYDefineMethod(class, common, init, __VA_ARGS__) { \
        self->base.self = self; \
        hy_pool_init(self->base.pool); \
        self->base.common_methods = ; \
        self->hy_data_buffer_body.base = &self->base; \
        self->hy_data_buffer_body.methods = &hy_simple_data_buffer_hy_data_buffer_methods; \
    }; \
    hyresult HYClassMethodName(class, common, do_init)(class *self, __VA_ARGS__)
    
    
#define HYAddRef(obj) hy_add_ref((hy_object*) obj)
#define HYDeRef(obj) hy_de_ref((hy_object**) &obj);
#define HYQueryInterface(obj, id) hy_query_interface((hy_object*) obj, id)
#define HYCall(obj, method, ...) obj->methods->method(obj->self, )
