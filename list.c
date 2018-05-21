#include "list.h"

typedef struct _Element {
    void * data;
    struct _Element *next;
    struct _Element *prev;
} Element;


struct _List {
    int size;
    Element * firstElement;
    Element * lastElement;
    Element * lastElemIndexed;
    Element * iterator;
    Element * iteratorPos;
    int indexOfLastIndexed;
};


List * NewList() {
    List * new = (List*) malloc(sizeof(List));
    if ( new == NULL ) {
        printf("Failed to initialize list.\n");
    }
    new->size=0;
    new->firstElement = NULL;
    new->lastElement = NULL;
    new->lastElemIndexed = NULL;
    new->indexOfLastIndexed = 0;

    return new;
}

void AppendElement( List *l, void* data ) {
    
    if ( l == NULL ) {
        printf("Invalid list");
        return;
    }

    Element * new = (Element *)malloc(sizeof(Element));
    if ( new == NULL ) {
        printf("Error allocating new list element");
        return;
    }

    new->data = data;
    new->next = NULL;
    l->size+=1;

    if ( l->lastElement == NULL ) {
        l->firstElement = new;
        l->lastElement = new;
        new->prev = NULL;
    } else {
        l->lastElement->next = new;
        new->prev = l->lastElement;
    }
    l->lastElement = new;
    
    return;
}

void * GetElement( List *l, int pos ) {
    int i;
    Element *el;

    // we can access negative positions like in python
    if ( pos < 0 ) {

        if ( -pos > l->size ) {
            printf("Invalid index");
            return NULL;
        }
        el = l->lastElement;
        for ( i = 0; i<-pos-1; i++ ) el = el->prev;
        l->indexOfLastIndexed = l->size + pos;

    } else {

        if ( pos >= l->size ) {
            printf("Invalid index or empty list.\n");
            return NULL;
        }

        // if the last indexed element was pos-1, we don't have to re-iterate
        // the whole list
        if ( pos == 0 )
            el = l->firstElement;
        else if ( pos - l->indexOfLastIndexed == 1 )
            el = l->lastElemIndexed->next;
        else {
            el = l->firstElement;
            for ( i=0; i<pos; i++ ) el = el->next;
        }
        l->indexOfLastIndexed = pos;
    }

    l->lastElemIndexed = el;
    return el->data;
}

void * startIteration( List *l ) {
    if(l->size!=0) {
        l->iteratorPos = 0;
        l->iterator=l->firstElement;
        return l->firstElement->data;
    }
    return NULL;
}

void * getNext( List *l ) {
    if( l->iterator->next == NULL ) {
        return NULL;
    }

    l->iteratorPos += 1;
    l->iterator = l->iterator->next;
    return l->iterator->data;

}
    

int ListSize( List *l ) {
    return l->size;
}

void PopThisElem(List *l,void *data ){
    Element *el = l->firstElement, *prev=NULL;

    if ( el == NULL ) {
        printf("List is empty.");
        return;
    }

    // look for the data
    while( el->data != data ) {
        el = el->next;
        if(el==NULL) break;
    }
    
    if ( el != NULL ) {
        prev = el->prev;
        if(prev==NULL)
            l->firstElement = el->next;
        else
            prev->next = el->next;
        if ( el->next != NULL ) 
            el->next->prev = prev;
        else
            l->lastElement = el;
        
        l->size-=1;
        free(el);
        l->lastElemIndexed = l->firstElement;
        l->indexOfLastIndexed=0;
    } else 
        printf("That element is not in list.\n");

}

void PopElement( List *l, int pos ) {
    Element * el=NULL, *prev=NULL;
    int i;
    
    if ( pos >= l->size ) {
        printf("Invalid index or empty list.\n");
        return;
    }

    el = l->firstElement;

    for ( i=0; i<pos; i++ ) {
        prev = el;
        el = el->next;
    }

    if ( prev!=NULL )
        prev->next = el->next;

    if( el->next != NULL )
        el->next->prev = prev;
    else
        l->lastElement = el;

    if( el == l->firstElement )
        l->firstElement = el->next;

    free(el);
    l->size-=1;

    l->lastElemIndexed = l->firstElement;
    l->indexOfLastIndexed=0;

}

void ListPrinter(List *l, void (*printer) (void*)) {
    if(l->size == 0)
        printf("List is empty.\n");
    else 
        printf("Will print a list of %d elements.\n",l->size);

    for(int i = 0; i<l->size; i++)
        printer(GetElement(l, i));        
}

void PurgeList( List *l ) {
    Element *el = l->firstElement, *next =NULL;

    while(el!=NULL) {
        next = el->next;
        free(el);
        el=next;
    }

    free(l);
}


// vim:foldmethod=syntax
