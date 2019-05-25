#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct node {
    int data;
    struct node *next;
} NodeT;

typedef struct listrep {
    int size;
    NodeT *head;
} listrep;

typedef struct listrep *List;

List newLL() {
   List L = malloc(sizeof(listrep));
   assert(L != NULL);
   L->size = 0;
   L->head = NULL;
   return L;
}

NodeT *createNode(int val) {
    NodeT *new_node = malloc(sizeof(NodeT));
    assert(new_node != NULL);
    new_node->data=val;
    new_node->next=NULL;
    return new_node;
}

NodeT *insertNode(List listr, int val) {
    NodeT *new_head = createNode(val);
    new_head->next=listr->head;
    listr->head=new_head;
    listr->size++;
    return new_head;
}

void deleteNode(List listr, int val) {
    if (listr->head == NULL) {
        return;
    }
    NodeT *curr = listr->head;
    if (curr->data==val) {
        listr->head=curr->next;
        free(curr);
        listr->size--;
        return;
    }
    while (curr->next != NULL) {
        if (curr->next->data == val) {
            curr->next=curr->next->next;
            free(curr->next);
            listr->size--;
            return;
        }
    }
}

void printLinkedList(List listr) {
    NodeT *curr = listr->head;
    while (curr->next != NULL) {
        printf("%d -- ", curr->data);
        curr=curr->next;
    }
    printf("%d\n", curr->data);
}

void freeLL(List listr) {
    NodeT *temp;
    while (listr->head != NULL) {
        temp=listr->head;
        listr->head=listr->head->next;
        free(temp);
    }
    free(listr);
}
