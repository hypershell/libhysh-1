
#include <hysh/object.h>
#include <hysh/simple_data_buffer.h>

HYDefineCommonImpl1(hy_simple_data_buffer, hy_data_buffer);
HYDataBufferConstructMethodTable(hy_simple_data_buffer);

HYDefineInitMethod(hy_simple_data_buffer, init_with_size, 
                        size_t size) 
{
    self->private.size = size;
    hyresult result = hy_pool_alloc(self->base.pool, size, &self->private.buffer);
    return result;
}

HYDefineClassMethodImpl(hy_simple_data_buffer, hy_data_buffer, buffer, 
                        const char **retval) 
{
    *retval = self->private.buffer;
    return HY_OK;
}

HYDefineClassMethodImpl(hy_simple_data_buffer, hy_data_buffer, size, 
                        size_t *retval) 
{
    *retval = self->private.size;
    return HY_OK;
}

HYDefineClassCleanup(hy_simple_data_buffer) {
    
}

