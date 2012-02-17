
#include <hysh/helper.h>
#include <hysh/common.h>
#include <hysh/simple_data_buffer.h>

HYDefineCommonImpl1(hy_simple_data_buffer, hy_data_buffer);
HYDataBufferDefineMethodStruct(hy_simple_data_buffer);

HYDefineClassInit(hy_simple_data_buffer, size_t size) {
    self->private.mSize = size;
    hyresult result = hy_pool_alloc(self->base.pool, size, &self->private.mBuffer);
    return result;
}

HYDefineClassMethodImpl(hy_simple_data_buffer, hy_data_buffer, buffer, const char **retval) {
    *retval = self->buffer;
    return HY_OK;
}

HYDefineClassMethodImpl(hy_simple_data_buffer, hy_data_buffer, size, size_t *retval) {
    *retval = self->size;
    return HY_OK;
}

HYDefineClassCleanup(hy_simple_data_buffer) {
    
}

