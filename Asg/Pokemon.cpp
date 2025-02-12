#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

struct kartu{
    int harga, id;
    char nama[30];
    kartu* next;
}*h, *t, *c;

int gen = 1, money = 1400;

void print(){
    kartu *temp = h;
    if (temp == NULL) {
        puts("No Card available");
        return;
    }
    puts("----------------------");
    printf("Money : $%d\n", money);
    puts("Card List : ");
    while (temp != NULL){
        puts("----------------------");
        printf("%s\n", temp->nama);
        printf(" $%d\n", temp->harga);
        printf(" #%d\n", temp->id);
        temp = temp->next;
    }
    puts("----------------------");
}

void push(char *nama){
    // Input value ke Current
    c = (kartu *) malloc (sizeof(kartu));
    strcpy(c->nama, nama);
    c->harga = 100;
    c->id = gen;
    gen++;
    c->next = NULL;

    // Push & Sorting

    // belum ada entry sama sekali
    if (!h){
        //                      kosong 
        // h = t = c ->NULL     data baru 1
        h = t = c;
    }

    // ketika Head.nama > Current.nama
    else if (strcmp(h->nama, c->nama) > 0){
        // c -> NUll  h -> t -> NUll        Bentuk awal Current dengan data awal
        c->next = h;
        // c -> h -> t -> NULL              memindahkan Current.next ke Head (melepas NULL)
        h = c;
        // h = c -> x -> t -> NULL          memindahkan address Head ke Current
    }

    // ketika Current.nama > Tail.nama
    else if (strcmp(t->nama, c->nama) < 0){
        // c -> NUll  h -> t -> NUll        Bentuk awal Current dengan data awal
        t->next = c;
        // h -> t -> c -> NULL              memindahkan Tail.next ke Current (melepas NULL)
        t = c;
        // h -> x -> c = t -> NULL          memindahkan address Tail ke Current
    }

    // ketika Head.nama < Current.nama < Tail.nama
    else {
        kartu* temp = h;
        // mengecheck apakah Current.nama sama dengan Temp.next.nama
        while (strcmp(temp->next->nama, c->nama) < 0){
            // h = temp -> x1 -> x2 -> t -> NULL  c -> NULL         awal
            temp = temp->next;
            // h -> x1 = temp -> x2 -> t -> NUll c-> NULL           kalo x1.nama < c.nama
            // h -> x1 = temp -> x2 -> t -> NUll c-> NULL           kalo x2.nama > c.nama, jadi berhenti
        }
        c->next = temp->next;
        // h -> x1 = temp -> x2 -> t -> NULL          memindahkan Cuurent.next ke x2 (melepas NULL)
        //                c -^         
        temp->next = c;
        // h -> x1 = temp    x2 -> t -> NULL          memindahkan x1/temp.next ke c
        //             \->c -^         
    }
}

void pop(char *nama){

    // ketika nama yang dicari == dengan nama pada Head
    if (strcmp(nama, h->nama) == 0){
        kartu* temp = h;
        // temp = h -> x... -> t -> NULL        menyamakan temp dengan Head
        h = h->next;
        // temp -> h -> x... -> t -> NULL       memindahkan h ke h.next
        free(temp);
        // h -> x... -> t -> NULL               free temp
    }

    // ketika nama yang dicari == dengan nama pada Tail
    else if (strcmp(nama, t->nama) == 0){
        kartu *temp = h;
        // mencari value sebelum search
        while (temp->next != t){
            //temp1 -> search -> t      belum sama
            temp = temp->next;
            //h -> temp1 -> t           stop
        }
        t = temp;
        kartu *del = temp->next;
        t->next = NULL;
        free(del);
    }

    // ketika nama yang dicari ada di antara Head dan Tail
    else {
        kartu *temp1 = h, *temp2 = h->next;
        // mencari search sebelum dan search itu sendiri di struct
        while (strcmp(temp2->nama, nama) != 0){
            //temp1 -> temp2 -> search -> x...
            temp1 = temp1->next;
            temp2 = temp2->next;
            //h -> temp1 -> temp2 == search -> x...
        }

        // temp1 -> temp2 -> x          Awal
        temp1->next = temp2->next;
        // temp1 -> x <- temp2             Perpindahan temp1.nexr ke temp2.next
        temp2->next = NULL;
        // temp1 -> x temp2 -> NULL     Perpindahana temp2.next ke NULL
        free(temp2);
        // temp1 -> x                   free temp2
    }
}

int search(char *input){
    kartu *temp = h;
    int valid = 0;
    while (temp != NULL){
        if (strcmp(temp->nama, input) == 0){
            valid = 1;
        }
        temp = temp->next;
    }
    return valid;
}

void swap(char *search, char *change){
    kartu *temp = h;
    c = (kartu *)malloc(sizeof(kartu));
    while (strcmp(temp->nama, search) != 0){
        temp = temp->next;
    }
    strcpy(c->nama, change);
    c->id = temp->id;
    c->harga = temp->harga;
    c->next = NULL;
    pop(search);

    if (strcmp(change, h->nama) < 0){
        c->next = h; h = c;
    }else if (strcmp(change, t->nama) > 0){
        t->next = c ; t = c;
    }else{
        temp = h;
        while (strcmp(temp->next->nama, change) < 0) temp = temp->next;
        c->next = temp->next;
        temp->next = c;
    }
    
}

void buy(){
    char input[30];
    printf("Nama  : ");scanf("%s", input);getchar();

    push(input);
    money -= 100;
}

void exchange(){
    char input1[30], input2[30];
    int valid = 0;
    do {
        printf("Card to Exhange : ");scanf("%s", input1);getchar();
        valid = search(input1);
        if (!valid) puts("Card not found");
    } while (!valid);
    printf("Card to Get : ");scanf("%s", input2);getchar();

    swap(input1, input2);
}

void press(){
    puts("press anything to continue");getchar();
}

void sell(){
    char input[30];
    int valid = 0;
    do {
        printf("Nama  : ");scanf("%s", input);getchar();
        valid = search(input);
        if (!valid) puts("Card not found");
    } while (valid != 1);

    pop(input);
    money += 100;
    return;
}

int main(){
    system("cls");
    int input;
    char kartu_awal [4][30] = {
        "Nidoran",
        "Diglett", 
        "Zubat",
        "Vulpix"     
    };

    for (int i = 0 ; i < 4 ; i++){
        push(kartu_awal[i]);
    }

    do{
        system("cls");
        puts("1. View");
        puts("2. Exchange");
        puts("3. Buy");
        puts("4. Sell");
        puts("5. Exit");
        do{
            printf(">> ");scanf("%d", &input);getchar();
        }while (!(1 <= input && input <= 5));

        switch(input){
            case 1: print();press();break;
            case 2: print();exchange();press();break;
            case 3: print();buy();press();break;
            case 4: print();sell();press();break;
            case 5: return 0;
        }
    } while (1);
    
    return 0;
}