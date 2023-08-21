#include "compiler.h"

struct compile_process* compile_process_create(const char* file_input_name, const char* file_output_name, int flags){

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
    cprocess->pos.column = 1;
    cprocess->pos.line = 1;
        
    return cprocess;
}

char compile_process_next_char(struct lexer_process* lexer_process)
{
    struct compile_process* compiler = lexer_process->compiler;
    compiler->pos.column++;
    char c = getc(compiler->code_file.input_file);
    if(c == '\n')
    {
        compiler->pos.column = 1;
        compiler->pos.line++; 
    }
    return c;
}

char compile_process_peek_char(struct lexer_process* lexer_process)
{
    struct compile_process* compiler = lexer_process->compiler;
    char c = getc(compiler->code_file.input_file);
    ungetc(c,compiler->code_file.input_file);
    return c;
}

void compile_process_push_char(struct lexer_process* lexer_process, char c)
{
    struct compile_process* compiler = lexer_process->compiler;
    ungetc(c,compiler->code_file.input_file);
    return;
}