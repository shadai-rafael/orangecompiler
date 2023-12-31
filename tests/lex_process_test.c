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

#include "commons_test.h"
#include "lex_process_test.h"

#include <string.h>


void test_lexer_get_numbers(void) {

    struct lexer_process_functions lexer_functions_test = {
    .next_char = generic_next_char,
    .peek_char = generic_peek_char,
    .push_char = generic_push_char
    };

    struct compile_process* cprocess = NULL;
    struct lexer_process* lexer_process_p = NULL;
    
    create_input_file(" 2345   678 911");
    
    cprocess = compile_process_create(TEST_INPUT_FILE, TEST_OUTPUT_FILE, 0);
    lexer_process_p = lexer_process_create(cprocess, &lexer_functions_test, NULL);

    TEST_ASSERT_EQUAL(LEXICAL_ANALYSIS_SUCCESSFULL, lexer(lexer_process_p));
    struct vector* tokens =  lexer_process_p->vec_tokens;
    TEST_ASSERT_EQUAL(3, vector_count(tokens));

    struct token* tmp_token = vector_back_or_null(tokens);
    TEST_ASSERT_EQUAL(911, tmp_token->llnum);
    TEST_ASSERT_EQUAL(1,tmp_token->pos.line);
    TEST_ASSERT_EQUAL(15,tmp_token->pos.column);
 
    tmp_token = vector_at(tokens,1);
    TEST_ASSERT_EQUAL(678, tmp_token->llnum);
    TEST_ASSERT_EQUAL(1,tmp_token->pos.line);
    TEST_ASSERT_EQUAL(11,tmp_token->pos.column);

    tmp_token = vector_at(tokens,0);
    TEST_ASSERT_EQUAL(2345, tmp_token->llnum);
    TEST_ASSERT_EQUAL(1,tmp_token->pos.line);
    TEST_ASSERT_EQUAL(5,tmp_token->pos.column);

    cprocess_cleanup(&cprocess,&lexer_process_p);
    TEST_ASSERT_NULL(lexer_process_p);
    return;
}

void test_lexer_get_strings(void) 
{
    struct lexer_process_functions lexer_functions_test = {
    .next_char = generic_next_char,
    .peek_char = generic_peek_char,
    .push_char = generic_push_char
    };

    struct compile_process* cprocess = NULL;
    struct lexer_process* lexer_process_p = NULL;
    
    create_input_file("\"hello\" \"world!!\"");
    
    cprocess = compile_process_create(TEST_INPUT_FILE, TEST_OUTPUT_FILE, 0);
    lexer_process_p = lexer_process_create(cprocess, &lexer_functions_test, NULL);

    TEST_ASSERT_EQUAL(LEXICAL_ANALYSIS_SUCCESSFULL, lexer(lexer_process_p));
    
    struct vector* tokens =  lexer_process_p->vec_tokens;
    TEST_ASSERT_EQUAL(2, vector_count(tokens));
    struct token* tmp_token = vector_back_or_null(tokens);
    TEST_ASSERT_EQUAL(0, strcmp("world!!", tmp_token->sval));
    TEST_ASSERT_EQUAL(1,tmp_token->pos.line);
    TEST_ASSERT_EQUAL(17,tmp_token->pos.column);
    
    tmp_token = vector_at(tokens,0);
    TEST_ASSERT_EQUAL(0, strcmp("hello", tmp_token->sval));
    TEST_ASSERT_EQUAL(1,tmp_token->pos.line);
    TEST_ASSERT_EQUAL(7,tmp_token->pos.column);

    cprocess_cleanup(&cprocess,&lexer_process_p);
    TEST_ASSERT_NULL(lexer_process_p);
    return;
}

void test_lexer_get_strings_numbers(void) {

    struct lexer_process_functions lexer_functions_test = {
    .next_char = generic_next_char,
    .peek_char = generic_peek_char,
    .push_char = generic_push_char
    };

    struct compile_process* cprocess = NULL;
    struct lexer_process* lexer_process_p = NULL;
    
    create_input_file("\"hello\" \"world!!\" 3342 5568");

    cprocess = compile_process_create(TEST_INPUT_FILE, TEST_OUTPUT_FILE, 0);
    lexer_process_p = lexer_process_create(cprocess, &lexer_functions_test, NULL);

    TEST_ASSERT_EQUAL(LEXICAL_ANALYSIS_SUCCESSFULL, lexer(lexer_process_p));
    struct vector* tokens =  lexer_process_p->vec_tokens;
    TEST_ASSERT_EQUAL(4, vector_count(tokens));
    
    struct token* tmp_token = vector_back_or_null(tokens);
    TEST_ASSERT_EQUAL(5568, tmp_token->llnum);
    TEST_ASSERT_EQUAL(1,tmp_token->pos.line);
    TEST_ASSERT_EQUAL(27,tmp_token->pos.column);
    
    tmp_token = vector_at(tokens,2);
    TEST_ASSERT_EQUAL(3342, tmp_token->llnum);
    TEST_ASSERT_EQUAL(1,tmp_token->pos.line);
    TEST_ASSERT_EQUAL(22,tmp_token->pos.column);

    tmp_token = vector_at(tokens,1);
    TEST_ASSERT_EQUAL("world!!", tmp_token->sval);
    TEST_ASSERT_EQUAL(1,tmp_token->pos.line);
    TEST_ASSERT_EQUAL(17,tmp_token->pos.column);

    tmp_token = vector_at(tokens,1);
    TEST_ASSERT_EQUAL("hello", tmp_token->sval);
    TEST_ASSERT_EQUAL(1,tmp_token->pos.line);
    TEST_ASSERT_EQUAL(7,tmp_token->pos.column);

    cprocess_cleanup(&cprocess,&lexer_process_p);
    TEST_ASSERT_NULL(lexer_process_p);
    return;
}