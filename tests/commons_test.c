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

void create_input_file(const char* file_content){
   FILE *fp = fopen(TEST_INPUT_FILE, "w+");
   fputs(file_content, fp);
   fclose(fp);
   return;
}

void cprocess_cleanup(struct compile_process** cprocess, struct lexer_process** lexer_process_p){
    fclose((*cprocess)->code_file.input_file);
    fclose((*cprocess)->output_file);
    remove(TEST_INPUT_FILE);
    remove(TEST_OUTPUT_FILE);
    free(*cprocess);
    cprocess = NULL;
    lexer_process_free(*lexer_process_p);
    *lexer_process_p = NULL;
}
