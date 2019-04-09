#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"
#include "wrap/wrap.h"
#include "../src/sample.h"

void setup(void)
{
    printf("setting up");
}

void teardown(void)
{
    unstubAll();
}

MU_TEST(test_malloc)
{
    stub("malloc", 1); // stub function abc
    mu_check(malloc(100) == NULL);  // stubbed function malloc returns NULL

    unstubAll();
    void *ptr = malloc(100);
    mu_check(ptr != NULL);  // stubbed function malloc returns NULL
    free(ptr);
}

MU_TEST(test_check)
{
    stub("abc", 1); // stub function abc
    stub("xyz", 1); // stub function xyz

    mu_check(abc() == 0xbabe);  // stubbed function abc returns 0xbabe
    mu_check(xyz() == 0xface);  // stubbed function abc returns 0xface

    unstubAll();    // unstub all functions

    mu_check(abc() == 0);  // original function abc returns 0
    mu_check(xyz() == 0);  // original function xyz return 0
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(setup, teardown);
    MU_RUN_TEST(test_check);
    MU_RUN_TEST(test_malloc);
}

int main(int argc, char *argv[])
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return minunit_status;
}
