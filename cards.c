#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "linkedlist.c"

#define LINE_LENGTH 1024
#define ERROR_NO 222

typedef struct listrep *List;

char *findSuit(int num) {
    if (num==0) {
        return "hearts";
    }
    else if (num==1) {
        return "diamonds";
    }
    else if (num==2) {
        return "hearts";
    }
    else {
        return "spades";
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
int checkCard(List listr, int pos, int disc, int chosenSuit) {
    NodeT *p;
    int n=0;
    for (p=listr->head; p!=NULL; p=p->next) {
        n++;
        if (n==pos) {
           if (p->data % 13 == 7) {
               return p->data; //if player has a crazy 8
           }
           if (p->data % 13 == disc % 13) {
               return p->data;
           }
           //if previous player played a crazy 8
           if (chosenSuit!=-1) {
               if (p->data / 13 == chosenSuit) {
                   return p->data;
               }
           } else {
               if (p->data / 13 == disc / 13) {
                   return p->data;
               }
           }
        }
    }
    return ERROR_NO;
}

//check if hand has any cards that can be played
int checkHand(List listr, int n, int chosenSuit) {
    NodeT *p;
    for (p=listr->head; p!=NULL; p=p->next) {
        if (p->data % 13 == 7) {
            return 1; //if player has a crazy eight
        }
        if (p->data % 13 == n % 13) {
            return 1;
        }
        if (chosenSuit != -1) {
            if (p->data / 13 == chosenSuit) {
                return 1;
            }
        } else {
            if (p->data / 13 == n / 13) {
                return 1;
            }
        }
    }
    return 0;
}

void printCards(List listr) {
    NodeT* curr = listr->head;
    int i=1;
    while (curr->next != NULL) {
        printf("%d %s\n", i, showCard(curr->data));
        curr=curr->next;
        i++;
    }
    printf("%d %s\n", i, showCard(curr->data));
}

//confirm input is valid int
int readInt(void) {
    char input[LINE_LENGTH];
    int  n;
    fgets(input, LINE_LENGTH, stdin);
    if ((sscanf(input, "%d", &n) != 1) || n < 0 )
        return ERROR_NO;
    else
        return n;
}

int readTxt() {
    char input[LINE_LENGTH];
    char k;
    fgets(input, LINE_LENGTH, stdin);
    if ((sscanf(input, "%c", &k)==1) && ((k=='Y') || (k=='y'))) {
        return 1;
    }
    return ERROR_NO;
}


int checkValidCard(List hand, int base, int chosenSuit) {
    int exit=0;
    int position;
    int m;
    do {
        position=readInt();
        m=checkCard(hand, position, base, chosenSuit);
        if ((position != ERROR_NO) && (m != ERROR_NO)) {
            exit=1;
        } else {
            printf("Wrong card. Enter another card number:\n");
        }
    } while (exit==0);
    return m;
}

int move(int correct, List deck, List hand, int base, int chosenSuit) {
    int played;
    if (correct) {
        played=checkValidCard(hand, base, chosenSuit);
        return played;
    } else {
        printf("You must pick up a card\n");
        do {
            printf("Here it is: %s\n", showCard(deck->head->data));
            insertNode(hand, deck->head->data);
            deleteNode(deck, deck->head->data);
        } while ((hand->head->data / 13 != base/13) && (hand->head->data % 13 != base % 13) && (hand->head->data % 13 != 7));
        printf("You must play %s\n", showCard(hand->head->data));
        int exit=0;
        do {
            printf("Type Y or y to confirm.\n");
            if (readTxt()!=ERROR_NO) {
               exit=1;
            }
        } while (exit==0);
        return hand->head->data;
    }
}

int pickSuit(void) {
    printf("You have played a crazy eight! Choose a suit for the next player to play.\n");
    printf("1 clubs\n");
    printf("2 diamonds\n");
    printf("3 hearts\n");
    printf("4 spades\n");
    int exit=0;
    int chosensuit;
    do {
        chosensuit=readInt();
        if ((chosensuit!=ERROR_NO) && (chosensuit>=1) && (chosensuit<=4)) {
            exit=1;
        } else {
            printf("That is not a suit. Please enter the number corresponding to a suit:\n");
        }
    } while (exit==0);
    chosensuit-=1;
    return chosensuit;
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
    for (int j=0; j<52; j++) {
        insertNode(deck, cardnumbers[j]);
    }
    List handone=newLL();
    List handtwo=newLL();
    //deal two hands of seven cards
    NodeT *curr=deck->head;
    for (int k=0; k<14; k++) {
        if (k % 2==0) {
            insertNode(handone, curr->data);
        } else {
            insertNode(handtwo, curr->data);;
        }
        deleteNode(deck, curr->data);
        curr=curr->next;
    }

    printf("The first hand is\n");
    printCards(handone);
    printf("\n");
    printf("The second hand is\n");
    printCards(handtwo);
    printf("\n");

    //create a discard plie
    printf("The first card is ");
    printf("%s\n", showCard(deck->head->data));
    int base=deck->head->data;
    deleteNode(deck, deck->head->data);
    List discard=newLL();
    insertNode(discard, base);
    int chosen=-1, right1, right2, m;
    if (base % 13 == 7) {
        printf("The first card is an eight. Player two must choose a suit for player one.\n");
        chosen=pickSuit();
        printf("Player one, you must play a card in the suit of %s or an eight of any suit.\n", findSuit(chosen));
    } else {
        printf("Player one, please choose a card that is of the same rank or suit as %s to discard or play an eight.\n", showCard(base));
    }
    right1=checkHand(handone, base, chosen);
    m=move(right1, deck, handone, base, chosen);
    insertNode(discard, m);
    deleteNode(handone, m);
    base=m;
    printf("Now there are %d cards in player one's hand and %d in the discard pile.\n", handone->size, discard->size);
    chosen=-1;
    do {
        //if player one plays a crazy eight
        for (int n=0; n<15;n++) {
            printf("\n");
        }
        if (m % 13 == 7) {
            printf("Player one has played a crazy eight.\n");
            chosen=pickSuit();
            printf("Player two, your hand is:\n");
            printCards(handtwo);
            printf("Player two, you must play a card in the suit of %s or an eight of any suit.\n", findSuit(chosen));
        } else {
            printf("Player two, your hand is:\n");
            printCards(handtwo);
            printf("Player two, now choose a card that is the same suit or rank as %s\n or play an eight.\n", showCard(base));
        }
        right2=checkHand(handtwo, base, chosen);
        m=move(right2, deck, handtwo, base, chosen);
        insertNode(discard, m);
        deleteNode(handtwo, m);
        printf("Now there are %d cards in player two's hand and %d in the discard pile.\n", handtwo->size, discard->size);
        base=m;
        chosen=-1;
        for (int n=0; n<15;n++) {
            printf("\n");
        }
        //if player two plays a crazy eight
        if (m % 13 == 7) {
            printf("Player two has played a crazy eight.\n");
            chosen=pickSuit();
            printf("Player one, your hand is:\n");
            printCards(handone);
            printf("Player one, you must play a card in the suit of %s or an eight of any suit.\n", findSuit(chosen));
        } else {
            printf("Player one, your hand is:\n");
            printCards(handone);
            printf("Player one, now choose a card that is of the same rank or suit as %s to discard or play an eight.\n", showCard(base));
        }
        right1=checkHand(handone, base, chosen);
        m=move(right1, deck, handone, base, chosen);
        insertNode(discard, m);
        deleteNode(handone, m);
        printf("Now there are %d cards in player one's hand and %d in the discard pile.\n", handone->size, discard->size);
        base=m;
        chosen=-1;
    } while ((handone->size > 0) && (handtwo->size > 0));
    if (handone->size==0) {
        printf("Player one is the winner");
    } else {
        printf("Player two is the winner.");
    }
    freeLL(handone);
    freeLL(handtwo);
    freeLL(discard);
    freeLL(deck);
    return 0;
}
