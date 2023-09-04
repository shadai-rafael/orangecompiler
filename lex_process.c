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
#include <stdlib.h>

struct lexer_process* lexer_process_create(struct compile_process* compile_process_p,
    struct lexer_process_functions* lexer_process_functions_p, void* private_p)
{
    struct lexer_process* lexer_process_p = calloc(1,sizeof(struct lexer_process));
    lexer_process_p->functions = lexer_process_functions_p;
    lexer_process_p->vec_tokens = vector_create(sizeof(struct token));
    lexer_process_p->private = private_p;
    lexer_process_p->compiler = compile_process_p;
    lexer_process_p->pos.column = 1;
    lexer_process_p->pos.line = 1;

    return lexer_process_p;
}

void lexer_process_free(struct lexer_process* lexer_process_p)
{
    vector_free(lexer_process_p->vec_tokens);    
    free(lexer_process_p);
}

void* get_lexer_process_private(struct lexer_process* lexer_process_p){
    return lexer_process_p->private;
}

struct vector* get_lexer_process_tokens(struct lexer_process* lexer_process_p){
    return lexer_process_p->vec_tokens;
}