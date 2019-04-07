#include <stdio.h>
#include <string.h>
#define __USE_GNU
#include <dlfcn.h>

typedef struct {
    char f[128];
    int val;
} wrapS;

#define MAX_WRAPS   128
wrapS g_wraps[MAX_WRAPS];
int g_wrapCnt = 0;

#define LOAD_FUNC(F, RET, ...) \
static RET (*org_##F)(__VA_ARGS__);\
if(!(org_##F)) \
{\
    org_##F = dlsym(RTLD_NEXT, #F);\
}

int stub(char *f, int val)
{
    int i;
    wrapS *w = NULL;

    for(i = 0; i < g_wrapCnt; i++) {
        w = &g_wraps[i];
        if(!strcmp(f, w->f)) {
            w->val = val;
            return 0;
        }
    }
    if(i >= MAX_WRAPS) {
        printf("setWrapCondition wraps exceeded\n");
        return 1;
    }
    w = &g_wraps[g_wrapCnt++];
    strncpy(w->f, f, sizeof(w->f));
    w->val = val;
    return 0;
}

void unstubAll(void)
{
    int i;
    for(i = 0; i < g_wrapCnt; i++) {
        g_wraps[i].f[0] = 0;
        g_wraps[i].val = 0;
    }
}

int getWrapVal(const char *f)
{
    int i;
    wrapS *w;

    for(i = 0; i < g_wrapCnt; i++) {
        w = &g_wraps[i];
        if(!strcmp(f, w->f)) {
            return w->val;
        }
    }
    return 0;
}

int xyz(void)
{
    LOAD_FUNC(xyz, int, void);
    int wv = getWrapVal(__FUNCTION__);
    if(0 == wv) {
        return org_xyz();
    }
    return 0xface;
}

int abc(void)
{
    LOAD_FUNC(abc, int, void);
    int wv = getWrapVal(__FUNCTION__);
    if(0 == wv) {
        return org_abc();
    }
    return 0xbabe;
}

