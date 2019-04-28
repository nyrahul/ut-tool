# UnitTest Tool

Basic unit test tool which provides:
1. test fixtures (for e.g. setup/teardown way)
2. test report (count tests, verify assertions, report failures)
3. stub functions

For (1) and (2), I use [minunit](https://github.com/siu/minunit) and for (3), I use LD\_PRELOAD and helpers functions (stub()/unstubAll()) defined by me. Minunit is lightweight and does not require any other dependencies.

Assumption: The code to be unit-tested is compiled as dynamic library.

## Sample Code

```c
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
    mu_check(ptr != NULL);  // unstubbed malloc should returns non-NULL
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
```

## Adding stub function

Assuming we need to stub ```malloc()```:
1. Define the stub ```malloc``` function in wrap.c
2. Use LOAD\_FUNC to load the original function, it will be called ```org_malloc```
3. ```wv = getWrapVal("malloc")``` yields the value set using ```stub("malloc", 1);``` .. in this case, wv would be 1.
4. Handle ```malloc``` stub based on wv value


```c
void *malloc(size_t sz)
{
    LOAD_FUNC(malloc, void *, size_t);
    int wv = getWrapVal(__FUNCTION__);
    if(0 == wv) {
        return org_malloc(sz);
    }
    return NULL;
}
```
