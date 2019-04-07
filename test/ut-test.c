#include <stdio.h>
#include "minunit.h"
#include "../src/sample.h"

extern void unstubAll(void);
extern void stub(char *, int);

void setup(void)
{
}

void teardown(void)
{
    unstubAll();
}

MU_TEST(test_abc)
{
    stub("abc", 1);
    mu_check(abc() == 0xbabe);
    mu_check(xyz() == 0);
}

MU_TEST(test_xyz)
{
    stub("xyz", 1);
    mu_check(xyz() == 0xface);
    mu_check(abc() == 0);
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(setup, teardown);
    MU_RUN_TEST(test_abc);
    MU_RUN_TEST(test_xyz);
}

int main(int argc, char *argv[])
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return minunit_status;
}
