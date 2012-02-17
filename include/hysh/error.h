
#pragma once

typedef unsigned long hy_error_code_t;

HYDefineInterface(hy_traceback) {
    hyresult (*line_num)(void *self, long *retval);
    
    hyresult (*file_name)(void *self, const char **retval);
};

HYDefineChain(hy_traceback_chain, hy_traceback*);

HYDefineInterface(hy_error_code) {
    hyresult (*error_code)(void *self, hy_error_code_t *retval);
    
    hyresult (*error_message)(void *self, const char **retval);
    
    hyresult (*tracebacks)(void *self, hy_traceback_chain **retval);
};