
#pragma once

#include <hysh/types.h>
#include <hysh/helper.h>

#define HY_OK NULL

struct hy_error;
typedef struct hy_error *hyresult;
typedef unsigned long hy_error_code_t;

HYDefineInterface(hy_error) {
    hyresult (*error_code)(void *self, hy_error_code_t *retval);
    
    hyresult (*error_message)(void *self, const char **retval);
    
    hyresult (*line_num)(void *self, long *retval);
    
    hyresult (*file_name)(void *self, const char **retval);
    
    hyresult (*prev_error)(void *self, struct hy_error **retval);
};

hyresult hy_add_traceback(hyresult result, const char *file_name, int line_num);

bool hy_is_error(hyresult result);

hyresult hy_stack_results(hyresult result1, hyresult result2);