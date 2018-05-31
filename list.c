#include <stdbool.h>

#include "list.h"

struct _List {
	void *data;
	struct _List *next;
};

/* Insert a dummy head node into the list */
List * list_init() {
	List *new = (List *) malloc(sizeof(List));
	new->data = NULL;
	new->next = NULL;
	if (!new) {
		perror("Failed to create list\n");
		return NULL;
	}

	return new;
}

/* Insert element after the dummy head node of the list */
void list_insert(List *l, void *data) {
	if (l == NULL) {
		perror("Invalid list insertion\n");
	}

	List *new = (List *) malloc(sizeof(List));

	new->data = data;
	new->next = l->next;
	l->next = new;
}

/* Find data in the list nodes */
List *list_find(List *l, void *data) {
	List *aux;
	for (aux=l; aux!=NULL; aux=aux->next) {
		if (aux->data == data) {
			return aux;
		}
	}
	perror("list_find Cannot find element\n");
	return NULL;
}

/* Remove list by node index*/
void list_remove(List *l, List *element) {
	if (element == NULL) {
		printf("element is null\n");
		return;
	}
	List **aux = &(l->next);

	while ((*aux) != element)
		aux = &(*aux)->next;
	if (aux == NULL) {
		printf("cannot find element\n");
		return;
	}

	printf("removing list\n");
	*aux = element->next;

	free(element->data);
	free(element);
	printf("list removed\n");
}

void *list_get(List *l){
	if (l == NULL) {
		perror("Invalid list acess\n");
	}
	return l->data;
}

List *list_next(List *l) {
	if (l==NULL) {
		perror("Invalid list next\n");
		return NULL;
	}

	return l->next;
}

bool list_end(List *l) {
	return l == NULL;
}

void list_print(List *l){
	List *aux = l;
	for (; aux->next != NULL; aux=aux->next) {
		list_print_element(aux);
	}
}

void list_print_element(List *l) {
	if (l == NULL) {
		perror("Invalid element\n");
		return;	
	}
	
	printf("element: %p next: %p data: %p\n", ((size_t) l)/sizeof(void *), ((size_t) l->next)/sizeof(void *), ((size_t)l->data)/sizeof(void *));
}

void list_delete(List *l) {
	if (l == NULL)
		return;

	list_delete(l->next);
	if (l->data != NULL) {
		free(l->data);
	}
	free(l);
}
