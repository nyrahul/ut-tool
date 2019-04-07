# UnitTest Tool

Basic unit test tool which provides:
1. test fixtures (for e.g. setup/teardown way)
2. test report (count tests, verify assertions, report failures)
3. stub existing functions

For (1) and (2), I use [minunit](https://github.com/siu/minunit) and for (3), I use LD\_PRELOAD and helpers functions (stub()/unstubAll()) defined by me.

Assumption: The code to be unit-tested is compiled as dynamic library.

## Sample Code

```c
#include <stdio.h>
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
}

int main(int argc, char *argv[])
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return minunit_status;
}
```
