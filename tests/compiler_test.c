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
#include <stdio.h>
#include "compiler_test.h"
#include "commons_test.h"
#include "../compiler.h"

/* tests */
void test_compile_process_create(void) {

    struct lexer_process_functions lexer_functions_test = {
    .next_char = generic_next_char,
    .peek_char = generic_peek_char,
    .push_char = generic_push_char
    };
    struct compile_process* cprocess = NULL;
    struct lexer_process* lexer_process_p = NULL;


    create_input_file("a\n\n");
    cprocess = compile_process_create(TEST_INPUT_FILE, TEST_OUTPUT_FILE, 0);
    lexer_process_p = lexer_process_create(cprocess, &lexer_functions_test, NULL);    
    TEST_ASSERT_NOT_NULL(lexer_process_p);
    cprocess_cleanup(&cprocess, &lexer_process_p);
    TEST_ASSERT_NULL(lexer_process_p);
}

void test_lexer_process_functions(void)
{

    struct lexer_process_functions lexer_functions_test = {
    .next_char = generic_next_char,
    .peek_char = generic_peek_char,
    .push_char = generic_push_char
    };

    struct compile_process* cprocess = NULL;
    struct lexer_process* lexer_process_p = NULL;

    create_input_file("a\n\n");
    cprocess = compile_process_create(TEST_INPUT_FILE, TEST_OUTPUT_FILE, 0);
    lexer_process_p = lexer_process_create(cprocess, &lexer_functions_test, NULL);    
    TEST_ASSERT_NOT_NULL(lexer_process_p);

    TEST_ASSERT_EQUAL('a', lexer_process_p->functions->peek_char(lexer_process_p));
    TEST_ASSERT_EQUAL(1, lexer_process_p->compiler->pos.column);
    TEST_ASSERT_EQUAL(1, lexer_process_p->compiler->pos.line);
    TEST_ASSERT_EQUAL('a', lexer_process_p->functions->next_char(lexer_process_p));
    TEST_ASSERT_EQUAL(2, lexer_process_p->compiler->pos.column);
    TEST_ASSERT_EQUAL(1, lexer_process_p->compiler->pos.line);
    TEST_ASSERT_EQUAL('\n', lexer_process_p->functions->peek_char(lexer_process_p));
    TEST_ASSERT_EQUAL(2, lexer_process_p->compiler->pos.column);
    TEST_ASSERT_EQUAL(1, lexer_process_p->compiler->pos.line);
    TEST_ASSERT_EQUAL('\n', lexer_process_p->functions->next_char(lexer_process_p));
    TEST_ASSERT_EQUAL(1, lexer_process_p->compiler->pos.column);
    TEST_ASSERT_EQUAL(2, lexer_process_p->compiler->pos.line);
    lexer_process_p->functions->push_char(lexer_process_p,'b');
    TEST_ASSERT_EQUAL('b', lexer_process_p->functions->peek_char(lexer_process_p));
    cprocess_cleanup(&cprocess, &lexer_process_p);
    TEST_ASSERT_NULL(lexer_process_p);
}