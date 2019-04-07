# UnitTest Tool

Basic unit test tool which provides:
1. test fixtures (for e.g. setup/teardown way)
2. test report (count tests, verify assertions, report failures)
3. stub existing functions

For (1) and (2), I use [minunit](https://github.com/siu/minunit) and for (3), I use LD\_PRELOAD and helpers functions (stub()/unstubAll()) defined by me.

My assumptions:
1. The code to be unit-tested is compiled as dynamic library.

