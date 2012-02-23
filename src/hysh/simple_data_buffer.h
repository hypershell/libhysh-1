
#include <hysh/helper.h>
#include <hysh/data_buffer.h>

struct hy_simple_data_buffer_private {
    char* buffer;
    size_t size;
};

HYDefineClassStruct1(hy_simple_data_buffer, hy_data_buffer, hy_simple_data_buffer_private);

HYDeclareInitMethod(hy_simple_data_buffer, init_with_size, size_t size);

