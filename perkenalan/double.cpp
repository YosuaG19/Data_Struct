#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

struct node{
    int value;
    node* next;
    node* prev;
}*h, *t, *c;

void print(){
    node *temp = h;
    int count = 0;
    while (temp != NULL){
        if (count == 0) printf("NULL ");
        printf("<- %d -> ", temp->value);
        if (temp->next == NULL) puts("NULL");
        count++;
        temp = temp->next;
    }
}

void push(int angka){
    c = (node *)malloc(sizeof(node));
    c->value = angka;
    c->next = NULL;
    c->prev = NULL;

    if (!h) h = t = c;  // no data
    else if (angka < h->value){         // push head
        c->next = h; h->prev = c; h = c;
    }else if (t->value < angka){        // push tail
        t->next = c; c->prev  = t ; t = c;
    }else {                             // push mid
        node *temp = h->next;
        while(temp->value < angka){
            temp = temp->next;
        }
        c->next = temp->next;
        temp->next->prev = c;
        temp->next = c;
        c->prev = temp;
    }

}

void pop(int angka){
    if (angka == h->value){             // pop head
        node *temp = h;
        h = h->next; h->prev = NULL;
        free(temp);
    }else if (angka == t->value){       // pop tail
        node *temp = t;
        t = t->prev; t->next = NULL;
        free(temp);
    }else {                             // pop mid
        node *temp = h->next;
        while (temp->value != angka){
            temp = temp->next;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        free(temp);
    }
}


int main(){
    for (int i = 1 ; i < 6 ; i++){
        push(i);
        print();
    }

    srand(time(NULL));
    pop(rand() % 5 + 1);
    print();
}