#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cmocka.h>

#include "../src/1.h"

static void test_full_program(void **s) {
    int old_stdout = dup(1);
    freopen("/dev/null", "w", stdout);
    
    char *argv1[] = {"./prgm"};
    assert_int_equal(aoc(1,argv1), 0);
    char *argv2[] = {"./prgm", "INPUT"};
    assert_int_equal(aoc(2,argv2), 0);
    char *argv3[] = {"./prgm", "invalid"};
    assert_int_equal(aoc(2,argv3), 1);
    
    fclose(stdout);
    stdout = fdopen(old_stdout, "w");
}

static void test_parsing(void **s) {
    int x1,x2,x3,x4,x5;
    struct inst *t1,*t2,*t3,*t4,*t5;
    t1 = parse_input("R2, L3",&x1);
    t2 = parse_input("R2, R2, R2",&x2);
    t3 = parse_input("R5, L5, R5, R3",&x3);
    t4 = parse_input("",&x4);
    t5 = parse_input(",,,",&x5);
    assert_non_null(t1);
    assert_non_null(t2);
    assert_non_null(t3);
    assert_null(t4);
    assert_null(t5);
    assert_int_equal(x1,2);
    assert_int_equal(x2,3);
    assert_int_equal(x3,4);
    test_free(t1);
    test_free(t2);
    test_free(t3);
}

static void test_part_one_examples(void **s) {
    int t1,t2,t3,r1,r2,r3;
    struct inst *test1 = parse_input("R2, L3",&t1);
    struct inst *test2 = parse_input("R2, R2, R2",&t2);
    struct inst *test3 = parse_input("R5, L5, R5, R3",&t3);
    r1 = part_one(test1,t1);
    r2 = part_one(test2,t2);
    r3 = part_one(test3,t3);
    assert_int_equal(r1,5);
    assert_int_equal(r2,2);
    assert_int_equal(r3,12);
    test_free(test1);
    test_free(test2);
    test_free(test3);
}

static void test_part_two_examples(void **s) {
    int t1,r1;
    struct inst *test1 = parse_input("R8, R4, R4, R8",&t1);
    r1 = part_two(test1,t1);
    assert_int_equal(r1,4);
    test_free(test1);
}

int main(void) {
    const struct UnitTest tests[] = {
	unit_test(test_parsing),
	unit_test(test_part_one_examples),
	unit_test(test_part_two_examples),
	unit_test(test_full_program),
    };
    return run_group_tests(tests);
}
