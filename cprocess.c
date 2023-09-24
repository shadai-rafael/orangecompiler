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

struct compile_process* compile_process_create(const char* file_input_name, const char* file_output_name, int flags){

    FILE* file_input = fopen(file_input_name ,"r");
    if(!file_input){
        fprintf(stderr,"Error at open the input file \n");
        return NULL;
    }

    FILE* file_output = fopen(file_output_name ,"w");
    if(!file_output){
        fprintf(stderr,"Error at open the output file \n");
        return NULL;
    }

    struct compile_process* cprocess = calloc(1,sizeof(struct compile_process));

    cprocess->flags = flags;
    cprocess->code_file.input_file = file_input;
    cprocess->code_file.absolute_path = file_input_name;
    cprocess->output_file = file_output;
    cprocess->pos.column = 1;
    cprocess->pos.line = 1;
        
    return cprocess;
}

char generic_next_char(struct lexer_process* lexer_process)
{
    struct compile_process* compiler = lexer_process->compiler;
    //improvement note: compiler is changing the position
    compiler->pos.column++;
    char c = getc(compiler->code_file.input_file);
    if(c == '\n')
    {
        compiler->pos.column = 1;
        compiler->pos.line++; 
    }
    return c;
}

char generic_peek_char(struct lexer_process* lexer_process)
{
    struct compile_process* compiler = lexer_process->compiler;
    char c = getc(compiler->code_file.input_file);
    ungetc(c,compiler->code_file.input_file);
    return c;
}

void generic_push_char(struct lexer_process* lexer_process, char c)
{
    struct compile_process* compiler = lexer_process->compiler;
    ungetc(c,compiler->code_file.input_file);
    return;
}