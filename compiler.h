#ifndef ORANGE_COMPILER_H
#define ORANGE_COMPILER_H

#include <stdio.h>
#include <stdlib.h>

struct compile_process{
    int flags;

    struct compile_process_input_file
    {
        FILE* input_file;
        const char* absolute_path;

    }code_file;

    FILE* output_file;
    
};

enum compilation_status {COMPILATION_FINISHED_SUCCESSFULLY = 0,
    COMPILATION_FINISHED_WITH_ERRORS = 1};

int compile_file(const char* file_input_name, const char * file_output_name,int flags);
struct compile_process* compile_process_create(const char* file_input_name, const char * file_output_name, int flags);
#endif /*ORANGE_COMPILER_H*/