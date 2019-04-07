#include <stdio.h>

int xyz(void)
{
    //printf("XYZ %s -- %s -- %d called\n", __FILE__, __FUNCTION__, __LINE__);
    return 0;
}

int abc(void)
{
    xyz();
    //printf("ABC %s -- %s -- %d called\n", __FILE__, __FUNCTION__, __LINE__);
    return 0;
}
