#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

int num = 0, p_loop = 0, p_once = 1;

struct node{
    int n_list;
    char nama[30];
    node *next;
    node *prev;
}*h, *t, *c, *now;

void print_now(node *now){
    printf("%-10s\n", p_loop ? "Loop" : "Once");
    if (now == NULL){
        puts("No Song Available");
        return;
    }
    printf("%-15s\n", now->nama);
    puts(" <<     |>    []     >> ");
}

void print_list(){
    if (!h){
        puts("No song availble");
        return;
    }
    node *temp = h;
    while (temp != NULL){
        printf("%02d. %-30s\n", temp->n_list, temp->nama);
        temp = temp->next;
        if (temp == h) break;
    }
}

void loop(){
    if (!h){
        puts("No song availble");
        return;
    }
    h->prev = t;
    t->next = h;
    p_loop = 1; p_once = 0;
}

void once(){
    if (!h){
        puts("No song availble");
        return;
    }
    h->prev = NULL;
    t->next = NULL;
    p_loop = 0; p_once = 1;
}

void push(char *title){
    c = (node *)malloc(sizeof(node));
    strcpy(c->nama, title);
    num++;
    c->n_list = num; c->prev = NULL; c->next = NULL;

    if (!h) h = t = c;
    else {
        t->next = c; c->prev = t;
        t = c;
    }
    if (p_loop) loop();
    if (p_once) once();
}

void add(){
    char *title;
    do {
        printf("Song Title : "); scanf("%[^\n]", title);getchar();
        if (strlen(title) > 30) puts("Title is too long");
    }while (strlen(title) > 30);

    push(title);
}

void prev(){
    if (!h){
        puts("No song availble");
        return;
    }
    if (now->prev == NULL){
        puts("There is no previous song");
    }else{
        now = now->prev;
    }
}

void next(){
    if (!h){
        puts("No song availble");
        return;
    }
    if (now->next == NULL){
        puts("There is no next song");
    }else{
        now = now->next;
    }
}

int search(int n){
    node *temp = h;
    int loop = 0;
    while (temp != NULL){
        if (temp->n_list == n){
            return 1;
        }if (temp == h) loop++;
        if (loop == 2) break;;
        temp = temp->next;
    }
    return 0;
}

void play(){
    if (!h){
        puts("No song to play");
        return;
    }else {
        print_list();
        int valid, input;
        do {
            printf("Song number to play : "); scanf("%d", &input);getchar();
            valid = search(input);
            if (!valid) puts("No song in that number");
        }while (!valid);

        node *temp = h;
        while (temp->n_list != input){
            temp = temp->next;
        }

        now = temp;
    }
}

void press(){
    puts("press anything to continue");getchar();
}

int main(){
    int input;
    do {
        system("cls");
        print_now(now);
        puts("---------------------------------");
        puts("1. Play Song");
        puts("2. Add Song");
        puts("3. View Song");
        puts("4. Next Song");
        puts("5. Prev Song");
        puts("6. Loop Mode");
        puts("7. Play Once Mode");
        puts("8. Exit");
        do {
            printf(">> ");scanf("%d", &input);getchar();
        } while (!(1 <= input && input <= 8));

        switch(input){
            case 1: play(); press(); break;
            case 2: add(); press(); break;
            case 3: print_list(); press(); break;
            case 4: next(); press(); break;
            case 5: prev(); press(); break;
            case 6: loop(); press(); break;
            case 7: once(); press(); break;
            case 8: return 0; break;
        }
    }while (1);

    return 0;
}