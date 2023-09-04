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
#include "compiler.h"
#include <stdarg.h>

struct lexer_process_functions lexer_functions = {
    .next_char = compile_process_next_char,
    .peek_char = compile_process_peek_char,
    .push_char = compile_process_push_char
};

void compiler_error(struct compile_process* compiler,const char* msg, ...){
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
    fprintf(stderr,"Error on line %i, col %i, file %s \n", compiler->pos.line,
            compiler->pos.column, compiler->code_file.input_file);
    exit(-1);
}

void compiler_warning(struct compile_process* compiler,const char* msg, ...){
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
    fprintf(stderr,"Warning on line %i, col %i, file %s \n", compiler->pos.line,
            compiler->pos.column, compiler->code_file.input_file);
}

int compile_file(const char* file_input_name, const char * file_output_name, int flags){
    struct compile_process* cprocess = compile_process_create(file_input_name,
        file_output_name,flags);

    if(!cprocess){
        return COMPILATION_FINISHED_WITH_ERRORS;
    }

    struct lexer_process* lexer_process_p = lexer_process_create(cprocess, &lexer_functions, NULL);

    if(!lexer_process_p){
        return COMPILATION_FINISHED_WITH_ERRORS;
    }

    if (lexer(lexer_process_p) != LEXICAL_ANALYSIS_SUCCESSFULL)
    {
        return COMPILATION_FINISHED_WITH_ERRORS;
    }

    return COMPILATION_FINISHED_SUCCESSFULLY;
}