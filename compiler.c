#include "compiler.h"

struct lexer_process_functions lexer_functions = {
    .next_char = compile_process_next_char,
    .peek_char = compile_process_peek_char,
    .push_char = compile_process_push_char
};

int compile_file(const char* file_input_name, const char * file_output_name, int flags){
    struct compile_process* cprocess = compile_process_create(file_input_name,
        file_output_name,flags);

    if(!cprocess){
        return COMPILATION_FINISHED_WITH_ERRORS;
    }

    struct lexer_process* lexer_process_p = lexer_process_create(cprocess, &lexer_functions, NULL);

    if(!lexer_process_p){
        return COMPILATION_FINISHED_WITH_ERRORS;
    }

    if (lexer(lexer_process_p) != LEXICAL_ANALYSIS_SUCCESSFULL)
    {
        return COMPILATION_FINISHED_WITH_ERRORS;
    }

    return COMPILATION_FINISHED_SUCCESSFULLY;
}