#include "list.h"

struct _List {
	void *data;
	struct _List *next;
};

/* Insert a dummy head node into the list */
List * list_init() {
	List *new = (List *) malloc(sizeof(List));
	if (!new) {
		perror("Failed to create list\n");
		return NULL;
	}

	return new;
}

/* Insert element after the dummy head node of the list */
void list_insert(List *l, void *data) {
	if (l == NULL) {
		perror("Invalid list\n");
	}

	List *new = (List *) malloc(sizeof(List));

	new->data = data;
	new->next = l->next;
	l->next = new;
}

/* Find data in the list nodes */
List *list_find(List *l, void *data) {
	List *aux;
	for (aux=l; aux->next!=NULL; aux=aux->next) {
		if (aux->data == data) {
			return aux;
		}
	}

	return NULL;
}

/* Remove list by node index*/
void list_remove(List *l, List *element) {
	List **aux = &(l->next);

	while ((*aux) != element)
		aux = &(*aux)->next;

	*aux = element->next;

	free(element->data);
	free(element);
}

void *list_get(List *l){
	if (l == NULL) {
		perror("Invalid list\n");
	}
	return l->data;
}

List *list_next(List *l) {
	if (l==NULL) {
		perror("Invalid list\n");
		return NULL;
	}

	return l->next;
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
	
	printf("element: %p next: %p data: %p\n", l, l->next, l->data);
}
