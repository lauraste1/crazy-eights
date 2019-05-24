int convertCard(char name[]) {
    for (int i=0; name[i]!='\0'; i++) {
       if
       return 0;
    }
    return 0;
}


    } else if (num / 13 == 1) {
        printf("%s of diamonds\n", rank);
    } else if (num / 13 == 2) {
        printf("%s of hearts\n", rank);
    } else if ((num / 13 == 3)) {
        printf("%s of spades\n", rank);
    }
}

void showCard(int num) {
    char *rank=showRank(num);
    if (num / 13 < 1) {
        printf("%s of clubs\n", rank);
    } else if (num / 13 == 1) {
        printf("%s of diamonds\n", rank);
    } else if (num / 13 == 2) {
        printf("%s of hearts\n", rank);
    } else if ((num / 13 == 3)) {
        printf("%s of spades\n", rank);
    }
}


    void readCard(char *n) {
    for (int i=0; n[i]!='\0'; i++) {
        if (n[i]=='a' || n[i]=='1' || )
    }
    }

    do {

    } while ()

    for (int n=0; n<51; n++) {
        int j = rand() % 52;
        int count = 0;
        for (int p=0; p<n; p++) {
            NodeT *curr = head;
            count++;
            while (curr->next != NULL) {
                if (count == j) {
                    int temp=head->data;
                    head->data=curr->data;
                    curr->data=temp;
                    continue;
                }
                curr=curr->next;
            }
        }
    }
        count++;
        NodeT *curr = head;
        while (curr->next != NULL) {
            if (count == j) {
            int temp=head->data;
                    head->data=curr->data;
                    curr->data=temp;
                }
            }

        }
    }
    printLinkedList(head);

    NodeT *link = head->next->data;

    for (int n=51; n>0; n--) {
        int j = rand() % 52;
        int temp = cardnumbers[j];
        cardnumbers[j]=cardnumbers[51];
        cardnumbers[51]=temp;
    }

    NodeT *newnode = createNode(4);
    newnode->next = createNode(52);
    newnode->next->next = createNode(17);

    printLinkedList(head);
    srand(247362);
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
    for (int m=0; m<52; m++) {
        printf("%d\n", cardnumbers[m]);
    }
