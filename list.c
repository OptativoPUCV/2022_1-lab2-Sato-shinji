#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List *list = (List *) malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;

    return list;
}

void * firstList(List * list) {
    if (list->head != NULL)
    {
        list->current = list->head;

        return list->head->data;
    }

    return NULL;
}

void * nextList(List * list) {
    if (list->current != NULL && list->current->next != NULL)
    {
        list->current = list->current->next;

        return list->current->data;
    }

    return NULL;
}

void * lastList(List * list) {
    if (list->tail != NULL)
    {
        list->current = list->tail;

        return list->current->data;
    }

    return NULL;
}

void * prevList(List * list) {
    if (list->current != NULL && list->current->prev != NULL)
    {
        list->current = list->current->prev;

        return list->current->data;
    }

    return NULL;
}

void pushFront(List * list, void * data) {
    Node *nodo = createNode(data);

    if (list->head == NULL)
    {
        list->head = nodo;
        list->tail = nodo;
    }
    else
    {
        nodo->next = list->head;
        list->head->prev = nodo;
        list->head = nodo;
    }

}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node *nodo = createNode(data);

    nodo->prev = list->current;

    if (list->current->next != NULL)
    {
        nodo->next = list->current->next;
        list->current->next->prev = nodo;
        list->current->next = nodo;
    }
    else
    {
        list->tail = nodo;
        list->current->next = nodo;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    Node *pop = list->current;

    if (pop->prev != NULL)
    {
        pop->prev->next = pop->next;
    }
    else
    {
        list->head = pop->next;
        pop->next->prev = NULL;
    }
    if (pop->next != NULL)
    {
        pop->next->prev = pop->prev;
    }
    else
    {
        list->tail = pop->prev;
        pop->prev->next = NULL;
    }

    free(list->current);
    
    return pop->data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}