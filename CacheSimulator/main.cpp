#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include <initializer_list>

#include "CacheSimulator.h"

#define __FILENAME__    (strrchr(__FILE__, '\\') )
#define __LOGINFO__ __FILENAME__, __FUNCTION__, __LINE__
#define MakeInfo(var) (AccessInfo{&var, #var})

int main()
{
    int a = 0;
    char b = 1;
    double c = 3;
    long long d = 5;

    CacheEntry ce1(&a);
    CacheEntry ce2(&b);
    CacheEntry ce3(&c);
    CacheEntry ce4(&d);

    auto& cs = CacheSimulator::GetInstance();

    cs.Simulate({ MakeInfo(a), MakeInfo(b), MakeInfo(c), MakeInfo(d) }, __LOGINFO__);

    printf("%p | %p\n", (void*)GetTag(&a), (void*)GetIndex(&a));
    printf("%p | %p\n", (void*)GetTag(&b), (void*)GetIndex(&b));
    printf("%p | %p\n", (void*)GetTag(&c), (void*)GetIndex(&c));
    printf("%p | %p\n", (void*)GetTag(&d), (void*)GetIndex(&d));


    return 0;
}