#include "compilertest.h"

void setUp(void) {    
}

void tearDown(void) {
    void cprocess_test_cleanup(void);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_compile_process_create);
    RUN_TEST(test_lexer_process_create);
    RUN_TEST(test_lexer_process_functions);
    return UNITY_END();
}