#ifndef _LIST_H
#define _LIST_H

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct _List List;

List *NewList();

void AppendElement( List *l, void* data );

void *GetElement( List *l, int pos );

void PopThisElem(List *l,void *data );

void PopElement( List *l, int pos );

int ListSize( List *l );

void ListPrinter(List *l, void (*printer) (void*));

void PurgeList( List *l );

void * startIteration( List *l );

void * getNext( List *l );

#endif
