#include<stdio.h>
#include<stdlib.h>

struct node{
    int value;
    node *next;
}*h, *t, *c;

void printList(node *head){
    while (head != NULL){
        printf("%d->", head->value);
        head = head->next;
    }
    puts("NULL");
}

void pushHead(int value){
    c = (node*) malloc (sizeof(node));
    c->value = value;
    c->next = NULL;
    if (!h) { //input pertama kali
        h = t = c;
    }
    else{
        c->next = h;
        h = c;
    }
}

void pushTail(int value){
    c = (node*) malloc (sizeof(node));
    c->value = value;
    c->next = NULL;
    if (!h) { //input pertama kali
        h = t = c;
    }
    else{
        t->next = c;
        t = c;
    }
}

void pushMid(int value){
    c = (node*) malloc (sizeof(node));
    c->value = value;
    c->next = NULL;
    if (!h) { //input pertama kali
        h = t = c;
    }
    else if (h->value > value){
        c->next = h;
        h = c;
    }
    else if (t->value < value){
        t->next = c;
        t = c;
    }
    else{
        node* temp;
        temp = h;
        while (value > temp->next->value){
            temp = temp->next;
        }
        c->next = temp->next;
        temp->next = c;
    }
}

void popHead(){
    if (h == NULL) return;
    node *temp = h;
    h = h->next;
    //bisa langsung free ngak harus temp->NULL;
    free(temp);
}

void popTail(){
    if (t == NULL) return;
    node* temp = h;
    while (temp->next->value != t->value){
        temp = temp->next;
    }

    t = temp;
    node *del;
    del = temp->next;
    t->next = NULL;
    free(del);
}

void popMid(int value){
    if (h == NULL) return;
    node* temp1 = h, * temp2 = h;
    if (h->value == value) popHead();
    else if (t->value == value) popTail();
    else {
        while (temp1->next->value != value){
            temp1 = temp1->next;
        }
        while (temp2->value != value){
            temp2 = temp2->next;
        }

        temp1->next = temp2->next;
        temp2->next = NULL;
        free(temp2);
    }
}

int main(){
    pushMid(10);
    pushMid(20);
    pushMid(30);
    printList(h);
    popMid(30);
    printList(h);
    return 0;
}