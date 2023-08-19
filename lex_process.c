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