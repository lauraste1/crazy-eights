#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "linkedlist.c"

#define LINE_LENGTH 1024
#define ERROR_NO 222

typedef struct listrep *List;

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
        return name;
    } else if (num / 13 == 1) {
        char *name=cardName(cardname, rank, d);
        return name;
    } else if (num / 13 == 2) {
        char *name=cardName(cardname, rank, h);
        return name;
    } else {
        char *name=cardName(cardname, rank, s);
        return name;
    }
}


//check if card can be played
int checkCard(List listr, int pos, int disc) {
    NodeT *p;
    int n=0;
    for (p=listr->head; p!=NULL; p=p->next) {
        n++;
        if (n==pos) {
           if (p->data % 13 == disc % 13) {
               return p->data;
           } else if (p->data / 13 == disc / 13) {
               return p->data;
           }
        }
    }
    return ERROR_NO;
}

//check if hand has any cards that can be played
int checkHand(List listr, int n) {
    NodeT *p;
    for (p=listr->head; p!=NULL; p=p->next) {
        if (n % 13 == p->data % 13) {
            return 0;
        } else if (n / 13 == p->data / 13) {
            return 0;
        }
    }
    return 1;
}

void printCards(List listr) {
    NodeT* curr = listr->head;
    int i=1;
    while (curr->next != NULL) {
        printf("%d %s\n", i, showCard(curr->data));
        curr=curr->next;
        i++;
    }
}

//confirm input is valid int
int readInt(void) {
    char input[LINE_LENGTH];
    int  n;
    fgets(input, LINE_LENGTH, stdin);
    if ( (sscanf(input, "%d", &n) != 1) || n < 0 )
        return ERROR_NO;
    else
        return n;
}

int checkValidCard(List hand, int base) {
    int exit=0;
    int position;
    int m;
    printf("Please choose a card that is of the same rank or suit to discard\n");
    do {
        position=readInt();
        if ((position!=ERROR_NO)) {
            m=checkCard(hand, position, base);
            exit=1;
        } else {
            printf("Wrong card. Try again");
        }
    } while (exit==0);
    return m;
}

int main() {
    //generate random seed and perform Fisher-Yates shuffle
    srand(time(0));
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
    List deck=newLL();
    insertNode(deck, cardnumbers[0]);
    for (int j=1; j<52; j++) {
        insertNode(deck, cardnumbers[j]);
    }
    printLinkedList(deck);
    List handone=newLL();
    List handtwo=newLL();
    //deal two hands of seven cards
    NodeT *curr;
    for (int k=0; k<16; k++) {
        if (k % 2==0) {
            insertNode(handone, curr->data);
        } else {
            insertNode(handtwo, curr->data);;
        }
        deleteNode(deck, curr->data);
        curr=curr->next;
    }

    printf("\nThe first hand is\n");
    printCards(handone);
    printf("\nThe second hand is\n");
    printCards(handtwo);
    printf("\nThe new linked list is\n");
    printLinkedList(deck);

    //create a discard plie
    printf("\nThe first card is ");
    printf("%s\n", showCard(deck->head->data));
    int base=deck->head->data;
    deleteNode(deck, deck->head->data);
    List discard=newLL();
    insertNode(discard, base);
    int right1=checkHand(handone, base);

    if (right1==0) {
        printf("Hand one contains a card you could play\n");
        int m=checkValidCard(handone, base);
        //if card entered is same suit or rank add to discard pile
        if (m!=ERROR_NO) {
            printf("Good choice!\n");
            insertNode(discard, m);
            deleteNode(handone, m);
            base=m;
        } else {
            printf("Wrong card. Try again\n");
        }
    } else {
        printf("You must pick up a card\n");
        do {
            printf("Here it is: %s\n", showCard(deck->head->data));
            insertNode(handone, deck->head->data);
            deleteNode(deck, deck->head->data);
        } while ((deck->head->data / 13 != base/13) && (deck->head->data % 13 != base % 13));
    }

    //free memory for hands, pick up and discard piles
    freeLL(handone);
    freeLL(handtwo);
    freeLL(discard);
    freeLL(deck);
    return 0;
}

/* do {
    int right1=checkHand(handone_head, base);
    int right2=checkHand(handtwo_head, base);
    if (right1==0) {
        checkValidCard(handone_head, base);
    } else {


    }
} while ((handone.size > 0)||(handtwo.size > 0))
*/
