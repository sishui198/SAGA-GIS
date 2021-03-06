/******************************************************************************
 *
 * File:           istack.c
 *
 * Created:        06/06/2001
 *
 * Author:         Pavel Sakov
 *                 CSIRO Marine Research
 *
 * Purpose:        Handling stack of integers
 *
 * Description:    None
 *
 * Revisions:      None
 *
 *****************************************************************************/

#define STACK_NSTART 50
#define STACK_NINC 50

#include <stdlib.h>
#include <string.h>
#include "istack.h"

static void istack_init(istack* s)
{
    s->n = 0;
    s->nallocated = STACK_NSTART;
    s->v = (int *)malloc(STACK_NSTART * sizeof(int));
}

istack* istack_create()
{
    istack* s = (istack *)malloc(sizeof(istack));

    istack_init(s);
    return s;
}

void istack_reset(istack* s)
{
    s->n = 0;
}

int istack_contains(istack* s, int v)
{
    int i;

    for (i = 0; i < s->n; ++i)
        if (s->v[i] == v)
            return 1;
    return 0;
}

void istack_push(istack* s, int v)
{
    if (s->n == s->nallocated) {
        s->v = (int *)realloc(s->v, (s->nallocated + STACK_NINC) * sizeof(int));
        s->nallocated += STACK_NINC;
    }

    s->v[s->n] = v;
    s->n++;
}

int istack_pop(istack* s)
{
    s->n--;
    return s->v[s->n];
}

void istack_destroy(istack* s)
{
    if (s != NULL) {
        free(s->v);
        free(s);
    }
}
