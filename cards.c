#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct node {
    int data;
    struct node *next;
} NodeT;

struct linkedList {
    NodeT *head;
    int size;
};

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

char *showRank(int num) {
    if (num % 13==0) {
        return "ace";
    } else if (num % 13==1) {
        return "2";
    } else if (num % 13==2) {
        return "3";
    } else if (num % 13==3) {
        return "4";
    } else if (num % 13==4) {
        return "5";
    } else if (num % 13==5) {
        return "6";
    } else if (num % 13==6) {
        return "7";
    } else if (num % 13==7) {
        return "8";
    } else if (num % 13==8) {
        return "9";
    } else if (num % 13==9) {
        return "10";
    } else if (num % 13==10) {
        return "jack";
    } else if (num % 13==11) {
        return "queen";
    } else {
        return "king";
    }
}

char *cardName(char cardname[], char rank[], char suit[]) {
    sprintf(cardname, "%s of %s", rank, suit);
    return cardname;
}

char *showCard(int num) {
    char *rank=showRank(num);
    char cardname[25], c[6]="clubs", d[10]="diamonds", h[7]="hearts", s[7]="spades";
    if (num / 13 < 1) {
        char *name=cardName(cardname, rank, c);
        printf("%s\n", name);
        return name;
    } else if (num / 13 == 1) {
        char *name=cardName(cardname, rank, d);
        printf("%s\n", name);
        return name;
    } else if (num / 13 == 2) {
        char *name=cardName(cardname, rank, h);
        printf("%s\n", name);
        return name;
    } else {
        char *name=cardName(cardname, rank, s);
        printf("%s\n", name);
        return name;
    }
}

void printCards(NodeT *head) {
    NodeT* curr = head;
    while (curr->next != NULL) {
        showCard(curr->data);
        curr=curr->next;
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

int main() {
    //generate random seed and perform Fisher-Yates shuffle
    srand(3484773);
    int cardnumbers[52];
    for (int a=0; a<52; a++) {
        cardnumbers[a]=a;
    }
    for (int n=51; n>0; n--) {
        int j = rand() % 52;
        int temp = cardnumbers[j];
        cardnumbers[j]=cardnumbers[51];
        cardnumbers[51]=temp;
    }
    //convert shuffled array to linked list
    NodeT *head=createNode(cardnumbers[0]);
    for (int j=1; j<52; j++) {
        head=insertNode(head, cardnumbers[j]);
    }
    printLinkedList(head);
    //deal two hands of seven cards
    NodeT *curr=head, *handone_head, *handtwo_head;
    for (int k=0; k<16; k++) {
        if (k % 2==0) {
            handone_head=insertNode(handone_head, curr->data);
        } else {
            handtwo_head=insertNode(handtwo_head, curr->data);;
        }
        deleteNode(&head, curr->data);
        curr=curr->next;
    }

    printf("\nThe first hand is\n");
    printCards(handone_head);
    printf("\nThe second hand is\n");
    printCards(handtwo_head);
    printf("\nThe new linked list is\n");
    printLinkedList(head);

    //create a discard plie
    printf("\nThe first card is ");
    int base=head->data;
    showCard(head->data);
    printf("%d\n", base);
    NodeT *discard;
    deleteNode(&head, head->data);
    printf("Please choose a card that is of the same rank or suit to discard\n");
    char throw[50];

    //scanf("%s", &*throw)
    //readCard(throw[0]);

    //free memory for hands, pick up and discard piles
    freeLL(handone_head);
    freeLL(handtwo_head);
    freeLL(head);
    return 0;
}
