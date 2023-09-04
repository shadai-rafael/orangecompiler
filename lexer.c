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
#include <string.h>
#include "utils/buffer.h"

/* Static variables */
static struct lexer_process* process;
static struct token tmp_token;

/* Macros */
#define LEX_GETC_IF(buffer, c, expression) \
    for (char c = peek_char(); expression; c = peek_char()) \
    { \
        buffer_write(buffer, c); \
        nextc(); \
    } 

#define NUMERIC_CASES \
    case '1': \
    case '2': \
    case '3': \
    case '4': \
    case '5': \
    case '6': \
    case '7': \
    case '8': \
    case '9': \
    case '0': 

/* Functions */

static char nextc(){
    char c = process->functions->next_char(process);
    //improvement note: lexer is changing the position
    process->pos.column++;
    if(c == '\n')
    {
        process->pos.column = 1;
        process->pos.line++; 
    }
    return c;
}

static peek_char()
{
    return process->functions->peek_char(process);
}

void push_char(char c)
{
    process->functions->push_char(process, c);
}


static struct position lex_file_position()
{
    return process->pos;
}

struct token* token_create(struct token* _token)
{
    memcpy(&tmp_token, _token, sizeof(struct token));
    tmp_token.pos = lex_file_position();
    return &tmp_token;
}

const char* read_number_str()
{
    const char* number = NULL;
    struct buffer* buffer = buffer_create();
    char c = peek_char();
    LEX_GETC_IF(buffer, c, (c>=0 && c<=9) );
    buffer_write(buffer, 0x00);
    return buffer_ptr(buffer);
}

unsigned long long read_number(){
    const char* s = read_number_str();
    return atoll(s);
}

struct token* token_make_number_for_value(unsigned long number)
{
    return token_create(&(struct token){.type=TOKEN_TYPE_NUMBER,.llnum=number});
}

struct token* token_make_number()
{
    return token_make_number_for_value(read_number());
}


struct token* next_token()
{
    struct token* token_p = NULL;
    char c = peek_char();

    switch (c)
    {
    NUMERIC_CASES
        token_make_number();
        break;
    case EOF:
        break;
    default:
        compiler_error(process->compiler ,"Unexpected token");
        break;
    }

    return token_p;
}

int lexer(struct lexer_process* lexer_process_p)
{
    lexer_process_p->current_expression_count = 0;
    lexer_process_p->parentheses_buffer = NULL;
    lexer_process_p->pos.filename = lexer_process_p->compiler->code_file.absolute_path;
    process = lexer_process_p;

    struct token* token_p = next_token();

    while (token_p)
    {
        vector_push(process->vec_tokens, token_p);
        token_p = next_token();
    }
    
    return LEXICAL_ANALYSIS_SUCCESSFULL;
}