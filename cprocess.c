#include "compiler.h"

struct compile_process* compile_process_create(const char* file_input_name, const char * file_output_name, int flags){

    FILE* file_input = fopen(file_input_name ,"r");
    if(!file_input){
        return NULL;
    }

    FILE* file_output = fopen(file_output_name ,"w");
    if(!file_output){
        return NULL;
    }

    struct compile_process* cprocess = calloc(1,sizeof(struct compile_process));

    cprocess->flags = flags;
    cprocess->code_file.input_file = file_input;
    cprocess->output_file = file_output;
    
    return cprocess;
}