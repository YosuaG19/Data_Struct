#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define max_table 10

struct nodes{
    char name[10];
    nodes *next;
}*h[max_table];


nodes *create(char *name){
    nodes *cur = (nodes*) malloc(sizeof(nodes));
    strcpy(cur->name, name);
    cur->next = NULL;
    return cur;
}

int Hash_index(char *name){
    int key = 0;
    for (int i = 0 ; i < strlen(name) ; i++){
        key += name[i];
    }
    return key % max_table;
}

void push(char *name){
    nodes *cur = create(name);
    // Calculate Hash Index
    int Index = Hash_index(name);
    if (h[Index] == NULL) h[Index] = cur;
    else {
        nodes *temp = h[Index];
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = cur;
    }
}

void print(){
    for (int i = 0 ; i < max_table ; i++){
        nodes *temp = h[i];
        printf("%d. ", i+1);
        while(temp != NULL){
            printf("%s -> ", temp->name);
            temp = temp->next;
        }
        printf("NUll\n");
    }
}

void pop(char *name){
    int index = Hash_index(name);

    if (h[index] == NULL) {
        puts("Not Found"); return;
    }else{
        nodes *temp1 = h[index], *temp2 = temp1->next;
        if (strcmp(name, temp1->name) == 0){
            free(temp1);h[index] = temp2;
            puts("Name Deleted"); return;
        }else {
            while (strcmp(name, temp2->name) != 0){
                temp1 = temp2;
                temp2 = temp2->next;
            }
            if (temp2 == NULL){
                puts("Not found");return;
            }
            temp1->next = temp2->next;
            free(temp2);
            puts("Name Deleted"); return;
        }
        
    }

}



int main(){
    char nama[10][10]{
        "budi", "lala", "andi", "neo", "jaden", "nana", "webe"
    };

    for (int i = 0 ; i < 7 ; i++){
        push(nama[i]);
    }
    print();

    puts("======================");

    pop(nama[0]);
    pop(nama[5]);

    print();
}