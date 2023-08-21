#include <stdio.h>
#include "compilertest.h"
#include "../compiler.h"

#define TEST_INPUT_FILE "testinput.txt"
#define TEST_OUTPUT_FILE "testoutput.txt"

struct lexer_process_functions lexer_functions_test = {
    .next_char = compile_process_next_char,
    .peek_char = compile_process_peek_char,
    .push_char = compile_process_push_char
};

struct compile_process* cprocess = NULL;
struct lexer_process* lexer_process_p = NULL;

void cprocess_test_cleanup(void){
    fclose(cprocess->code_file.input_file);
    fclose(cprocess->output_file);
    remove(TEST_INPUT_FILE);
    remove(TEST_OUTPUT_FILE);
    free(cprocess);
    lexer_process_free(lexer_process_p);
}

void create_file_for_test(void){
   FILE *fp = fopen(TEST_INPUT_FILE, "w+");
   fputs("a\n\n", fp);
   fclose(fp);
}

/* tests */
void test_compile_process_create(void) {
    create_file_for_test();
    cprocess = compile_process_create(TEST_INPUT_FILE, TEST_OUTPUT_FILE, 0);
    TEST_ASSERT_NOT_NULL(cprocess);
}

void test_lexer_process_create(void) {
    create_file_for_test();
    lexer_process_p = lexer_process_create(cprocess, &lexer_functions_test, NULL);
    TEST_ASSERT_NOT_NULL(lexer_process_p);
}

void test_lexer_process_functions(void)
{
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

    cprocess_test_cleanup();
}