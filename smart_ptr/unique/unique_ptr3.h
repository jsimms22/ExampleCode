#ifndef SHARED_PTR3_H
#define SHARED_PTR3_H

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int m_int;
    double m_double;
} Foo;

Foo* createObj(int value1, double value2)
{
    Foo* output = (Foo*)malloc(sizeof(Foo));
    output->m_int = value1;
    output->m_double = value2;

    printf("Foo created.\n");
    return output;
}

void destroyObj(Foo* obj)
{
    free(obj);
    printf("Foo destroyed.\n");
}

#endif