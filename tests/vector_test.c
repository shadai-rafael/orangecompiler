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

#include "../utils/vector.h"
#include "vector_test.h"

void test_vector_push_pop(void){
    
    struct vector* vec_point = vector_create(sizeof(struct point_test));
    struct point_test* point1 = calloc(1,sizeof(struct point_test));
    struct point_test* point2 = calloc(1,sizeof(struct point_test));
    struct point_test* point3 = calloc(1,sizeof(struct point_test));
    
    point1->x = 1; point1->y = 1;
    point2->x = 2; point2->y = 2;
    point3->x = 3; point3->y = 3;

    vector_push(vec_point, point1);
    vector_push(vec_point, point2);
    vector_push(vec_point, point3);

    TEST_ASSERT_FALSE(vector_empty(vec_point));
    TEST_ASSERT_EQUAL(3,vector_count(vec_point));
    struct point_test* _point = (struct point_test*) vector_peek(vec_point);
    TEST_ASSERT_EQUAL(1,_point->x);
    
    vector_pop(vec_point);
    TEST_ASSERT_EQUAL(2,vector_count(vec_point));

    _point = (struct point_test*) vector_back_or_null(vec_point);
    TEST_ASSERT_EQUAL(2,vector_count(vec_point));
    TEST_ASSERT_EQUAL(2,_point->x);

    vector_clear(vec_point);
    TEST_ASSERT_TRUE(vector_empty(vec_point));

    vector_free(vec_point);
}
