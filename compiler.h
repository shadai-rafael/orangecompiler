/*
MIT License

Copyright (c) 2023 shadai-rafael

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef ORANGE_COMPILER_H
#define ORANGE_COMPILER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils/vector.h"

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

enum lexical_analysis_status{
    LEXICAL_ANALYSIS_SUCCESSFULL,
    LEXICAL_ANALYSIS_INPUT_ERROR
};

enum compilation_status 
{
    COMPILATION_FINISHED_SUCCESSFULLY = 0,
    COMPILATION_FINISHED_WITH_ERRORS = 1
};

/* structs */
struct position
{
    int line;
    int column;
    const char* filename;
};

struct token
{
    int type;
    int flags;
    struct position pos;
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


struct compile_process
{
    int flags;

    struct position pos;

    struct compile_process_input_file
    {
        FILE* input_file;
        const char* absolute_path;

    }code_file;

    FILE* output_file;    
};

struct lexer_process;

typedef char (*LEX_PROCESS_NEXT_CHAR)(struct lexer_process*);
typedef char (*LEX_PROCESS_PEEK_CHAR)(struct lexer_process*);
typedef void (*LEX_PROCESS_PUSH_CHAR)(struct lexer_process*, char c );

struct lexer_process_functions
{
    LEX_PROCESS_NEXT_CHAR next_char;
    LEX_PROCESS_PEEK_CHAR peek_char;
    LEX_PROCESS_PUSH_CHAR push_char;
};

struct lexer_process
{
    struct position pos;
    struct vector* vec_tokens;
    struct compile_process* compiler;
    int current_expression_count;
    struct buffer* parentheses_buffer;
    struct lexer_process_functions* functions;
    void* private;
};

/* prototypes */

/*Compile Functions*/
void compiler_error(struct compile_process* compiler,const char* msg, ...);
int compile_file(const char* file_input_name, const char * file_output_name,int flags);
struct compile_process* compile_process_create(const char* file_input_name, const char * file_output_name, int flags);
char compile_process_next_char(struct lexer_process* lexer_process);
char compile_process_peek_char(struct lexer_process* lexer_process);
void compile_process_push_char(struct lexer_process* lexer_process, char c);
void compiler_warning(struct compile_process* compiler,const char* msg, ...);

/*Lexer Functions*/
int lexer(struct lexer_process* lexer_process_p);
struct lexer_process* lexer_process_create(struct compile_process* compile_process_p,
    struct lexer_process_functions* lexer_process_functions_p, void* private_p);
void lexer_process_free(struct lexer_process* lexer_process_p);
void* get_lexer_process_private(struct lexer_process* lexer_process_p);
struct vector* get_lexer_process_tokens(struct lexer_process* lexer_process_p);

#endif /*ORANGE_COMPILER_H*/