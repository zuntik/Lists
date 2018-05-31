#ifndef _LIST_H
#define _LIST_H

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct _List List;

List * list_init();
void list_insert(List *l, void *data);
List *list_find(List *l, void *data);
void list_remove(List *l, List *element);
void *list_get(List *l);
List *list_next(List *l);
bool list_end(List *l);
void list_print(List *l);
void list_print_element(List *l);
void list_delete(List *l);

#endif
