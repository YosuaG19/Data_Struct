#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int count = 1, price = 100;

struct Asg1{
    char card[30];
    int id, price;
    Asg1 *next;
}*h, *t, *c;

void printList(Asg1 *head){
    while (head != NULL){
        printf("%d. %s -- %d\n", head->id, head->card, head->price);
        head = head->next;
    }
}


void pushMid(char value[]){
    // printf("%s\n", value);
    c = (Asg1*) malloc (sizeof(Asg1));
    strcpy(c->card, value);
    srand(time(NULL));
    c->id = count, c->price = price += rand() % 1000;
    c->next = NULL;
    if (!h) { //input pertama kali
        h = t = c;
    }
    else if (strcmp(h->card, value) > 0){
        c->next = h;
        h = c;
    }
    else if (strcmp(t->card, value) < 0){
        t->next = c;
        t = c;
    }
    else{
        Asg1* temp;
        temp = h;
        while (strcmp(value, temp->next->card) > 0){
            temp = temp->next;
        }
        c->next = temp->next;
        temp->next = c;
    }
    count++;
}

void popHead(){
    if (h == NULL) return;
    Asg1 *temp = h;
    h = h->next;
    //bisa langsung free ngak harus temp->NULL;
    free(temp);
}

void popTail(){
    if (t == NULL) return;
    Asg1* temp = h;
    while (strcmp(temp->next->card,t->card) != 0){
        temp = temp->next;
    }

    t = temp;
    Asg1 *del;
    del = temp->next;
    t->next = NULL;
    free(del);
}

void popMid(char value[]){
    if (h == NULL) return;
    Asg1* temp1 = h, * temp2 = h;
    printf("Head : %s \nTail : %s\n", h->card, t->card);
    if (strcmp(h->card, value) == 0) popHead();
    else if (strcmp(t->card, value) == 0) popTail();
    else {
        while (strcmp(temp1->next->card, value) != 0){
            temp1 = temp1->next;
        }
        while (strcmp(temp2->card, value) != 0){
            temp2 = temp2->next;
        }

        temp1->next = temp2->next;
        temp2->next = NULL;
        free(temp2);
    }
}

void menu(){
    puts("1. Insert Card");
    puts("2. buy Card");
    puts("3. Exit");
}
void menu1(){
    char nama[30];
    printf("Nama : ");scanf("%s", nama);getchar();
    pushMid(nama);
    printList(h);getchar();
}

void menu2(){
    char nama[30];
    printf("Nama : ");scanf("%s", nama);getchar();
    popMid(nama);
    printList(h);getchar();
}

int main(){
    char name[30];
    
    do {
        system("cls");
        int input;
        menu();
        do {
            printf(">> ");scanf("%d", &input);getchar();
        }while (!(1 <= input && input <= 3));

        switch (input){
            case 1: menu1();break;
            case 2: menu2();break;
            case 3: return 0;
        }

    }while (1);
}
