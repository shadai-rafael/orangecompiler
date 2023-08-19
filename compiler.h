#ifndef ORANGE_COMPILER_H
#define ORANGE_COMPILER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* structs */
struct pos
{
    int line;
    int column;
    const char* filename;
};

struct token
{
    int type;
    int flags;

    union
    {
        char cval;
        const char* sval;
        unsigned int inum;
        unsigned long lnum;
        unsigned long long llnum;
        void* any;
    };

    bool withespace;
    const char* betweeen_brakets;    
};


struct compile_process{
    int flags;

    struct compile_process_input_file
    {
        FILE* input_file;
        const char* absolute_path;

    }code_file;

    FILE* output_file;
    
};

/* enums */

enum token_type
{
    TOKEN_TYPE_IDENTIFIER,
    TOKEN_TYPE_KEYWORD,
    TOKEN_TYPE_OPERATOR,
    TOKEN_TYPE_SYMBOL,
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_COMMENT,
    TOKEN_TYPE_NEWLINE
};

enum compilation_status 
{
    COMPILATION_FINISHED_SUCCESSFULLY = 0,
    COMPILATION_FINISHED_WITH_ERRORS = 1
};

/* prototype */
int compile_file(const char* file_input_name, const char * file_output_name,int flags);
struct compile_process* compile_process_create(const char* file_input_name, const char * file_output_name, int flags);

#endif /*ORANGE_COMPILER_H*/