#include "compiler.h"

int compile_file(const char* file_input_name, const char * file_output_name, int flags){
    struct compile_process* process = compile_process_create(file_input_name,
        file_output_name,flags);

    if(!process){
        return COMPILATION_FINISHED_WITH_ERRORS;
    }

    return COMPILATION_FINISHED_SUCCESSFULLY;
}