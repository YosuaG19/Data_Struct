#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct RS{
    int umur, prio;
    char nama[30];
    RS *next;
}*h, *t, *c;

/*
Logika Yang Dipake
1. Urutan Nodes dari kecil ke Besar (High -> Mid -> Low)
2. Push menggunakan Head, Mid, dan Tail
3. Pop menggunakan pop Head
4. View akan dilakukan dari Head ke Tail
*/

void printQueue(){
    int count = 1;
    if (!h){
        puts("No Queue");getchar();
        return;
    }
    RS *temp = h;
    puts("|No.|Nama      |Umur|Prio|");
    puts("--------------------------");
    while(temp != NULL){
        printf("|%02d |%-10s| %02d | %02d |\n", count, temp->nama, temp->umur, temp->prio);
        // switch(temp->prio){
        //     case 1: puts("High|");break;
        //     case 2: puts("Mid |");break;
        //     case 3: puts("Low |");break;
        // }
        count++;
        temp = temp->next;
    }
    getchar();
}

void push(){
    if (!h){
        h = t = c;
    }else {
        // untuk Push Tail
        if (c->prio == t->prio || c->prio > t->prio){
            t->next = c;
            t = c;
        }
        // untuk Push Head
        else if (c->prio < h->prio){
            c->next = h;
            h = c;
        }
        // untuk Push Mid
        else{
            RS *temp = h;
            while(temp->next->prio <= c->prio) temp = temp->next;
            c->next = temp->next;
            temp->next = c;
        }
    }
    puts("Patient Added!");
    puts("Press Anything to continue");getchar();
}

void print_patient(RS *p){
    printf("|%-10s| %02d |", p->nama, p->umur);
    switch(p->prio){
        case 1: puts("High|");break;
        case 2: puts("Mid |");break;
        case 3: puts("Low |");break;
    }
}

void AddQueue(){
    // Masukin Semua Value dari Current
    c = (RS*) malloc (sizeof(RS));
    printf("Nama : ");scanf("%s", c->nama);getchar();
    printf("Umur : ");scanf("%d", &c->umur);getchar();
    // do {
    //     printf("Prio : ");scanf("%d", &c->prio);getchar();
    // }while (!(1<=c->prio && c->prio<=3));
    char priority[5] = "";
    do {
        printf("Prio : ");scanf("%s", priority);getchar();
    }while (!(strcmp(priority, "High") == 0 || strcmp(priority, "Mid") == 0 || strcmp(priority, "Low") == 0));

    if (strcmp(priority, "High") == 0 ){
        c->prio = 1;
    }else if(strcmp(priority, "Mid") == 0){
        c->prio = 2;
    }else{
        c->prio = 3;
    }
    c->next = NULL;
    push();
}

void DeQueue(){
    for (int i = 0 ; i < 3 ; i++){
        if (!h){
            puts("No Queue");getchar();
            return;
        }
        RS *temp = h;
        // Ketika Queue tinggal 1
        if (h==t){
            printf("Taken Care : ");print_patient(h);getchar();
            free(h);
            h = t = NULL;
        }
        // Masih ada Queue
        else{
            printf("Taken Care : ");print_patient(temp);getchar();
            h = temp->next;
            free(temp);
        }
    }
    
}

int main(){
    int input; 
    do{
        system("cls");
        puts("Hospital Queue Priority System");
        puts("--------------------------------");
        puts("1. Add Patient");
        puts("2. Take Care Patient");
        puts("3. View Queue");
        puts("4. Exit");
        do{
            printf(">> ");scanf("%d", &input);getchar();
        } while(!(1<=input && input<=4));

        switch(input){
            case 1: AddQueue();break;
            case 2: DeQueue();break;
            case 3: printQueue();break;
            case 4: return 0;break;
        }
    }while (1);
}