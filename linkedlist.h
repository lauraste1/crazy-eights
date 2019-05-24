#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int data;
    struct node *next;
} NodeT;

NodeT *createNode(int val) {
    NodeT *new_node = malloc(sizeof(NodeT));
    assert(new_node != NULL);
    new_node->data=val;
    new_node->next=NULL;
    return new_node;
}

NodeT *insertNode(NodeT *head, int val) {
    NodeT *new_head = createNode(val);
    new_head->next=head;
    head=new_head;
    return new_head;
}

void deleteNode(NodeT **head, int val) {
    if (head == NULL) {
        return;
    }
    NodeT *curr = *head;
    if (curr->data==val) {
        *head=curr->next;
        free(curr);
        return;
    }
    while (curr->next != NULL) {
        if (curr->next->data == val) {
            curr->next=curr->next->next;
            return;
        }
    }
}

void printLinkedList(NodeT *head) {
    NodeT *curr = head;
    while (curr->next != NULL) {
        printf("%d -- ", curr->data);
        curr=curr->next;
    }
    printf("%d\n", curr->data);
}

void freeLL(NodeT *head) {
    NodeT *temp;
    while (head != NULL) {
        temp=head;
        head=head->next;
        free(temp);
    }
}
