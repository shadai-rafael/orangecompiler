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

#include <assert.h>
#include <string.h>

#include "compiler.h"
#include "utils/buffer.h"

/* Static variables */
static struct lexer_process* lex_process;
static struct token tmp_token;

/* Macros */
#define LEX_GETC_IF(buffer, c, expression) \
    for (c = nextc(); expression ; c = nextc()) \
    { \
        buffer_write(buffer, c); \        
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

#define WHITE_SPACE_CASES \
    case ' ': \
    case '\t': 

/* Functions */

static char nextc()
{
    char c = lex_process->functions->next_char(lex_process);
    //improvement note: lexer is changing the position
    lex_process->pos.column++;
    if(c == '\n')
    {
        lex_process->pos.column = 1;
        lex_process->pos.line++; 
    }
    return c;
}

static char peek_char()
{
    return lex_process->functions->peek_char(lex_process);
}

void push_char(char c)
{
    lex_process->functions->push_char(lex_process, c);
}

static struct position lex_file_position()
{
    return lex_process->pos;
}

struct token* token_create(struct token* _token)
{
    memcpy(&tmp_token, _token, sizeof(struct token));
    memcpy(&tmp_token.pos, &lex_process->pos, sizeof(struct position));    
    return &tmp_token;
}

const char* read_number_str()
{
    const char* number = NULL;
    struct buffer* buffer = buffer_create();
    char c = 0;
    LEX_GETC_IF(buffer, c, (c>='0' && c<='9') );    
    buffer_write(buffer, 0x00);
    return buffer_ptr(buffer);
}

unsigned long long read_number(){
    const char* s = read_number_str();
    return atoll(s);
}

struct token* token_make_number_for_value(unsigned long number)
{
    struct token* _token = token_create(&(struct token){.type=TOKEN_TYPE_NUMBER,.llnum=number,
            .withespace = false});
    _token->pos.column--;
    return _token;
}

struct token* token_make_number()
{
    return token_make_number_for_value(read_number());
}

struct token* handle_white_space()
{
    nextc();
    memset(&tmp_token, 0, sizeof(struct token));
    memcpy(&tmp_token.pos, &lex_process->pos, sizeof(struct position));
    tmp_token.withespace = true;
    tmp_token.pos.column--;
    return &tmp_token;
}

struct token* token_make_string(char init_delm, char final_delm)
{
    struct buffer* buffer = buffer_create();
    assert(nextc() == init_delm);
    for(char c = nextc(); c!= init_delm && c!= EOF; c = nextc())
    {
        if(c == '\\'){
            continue;
        }
        buffer_write(buffer, c);
    }
    buffer_write(buffer, 0x00);
    return token_create(&(struct token){.type=TOKEN_TYPE_STRING,.sval = buffer_ptr(buffer),
            .withespace = false});
}

struct token* next_token()
{
    struct token* token_p = NULL;
    char c = peek_char();

    switch (c)
    {
    NUMERIC_CASES
        token_p = token_make_number();
        break;
    case '"':
        token_p = token_make_string('"','"');
        break;
    WHITE_SPACE_CASES
        token_p = handle_white_space();
        break;
    case EOF:
        break;
    default:
        compiler_error(lex_process->compiler ,"Unexpected token");
        break;
    }
    return token_p;
}

int lexer(struct lexer_process* lexer_process_p)
{
    lexer_process_p->current_expression_count = 0;
    lexer_process_p->parentheses_buffer = NULL;
    lexer_process_p->pos.filename = lexer_process_p->compiler->code_file.absolute_path;
    lex_process = lexer_process_p;

    struct token* token_p = next_token();

    while (token_p)
    {
        if (!token_p->withespace)
        {
            vector_push(lex_process->vec_tokens, token_p);
        }
                
        token_p = next_token();
    }
    
    return LEXICAL_ANALYSIS_SUCCESSFULL;
}