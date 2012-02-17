
#include <hysh/helper.h>
#include <hysh/data_buffer.h>

HYDeclareClass1(hy_simple_data_buffer, hy_data_buffer) {
    char* mBuffer;
    size_t mSize;
};

hy_simple_data_buffer_init(hy_simple_data_buffer *self, size_t size);

