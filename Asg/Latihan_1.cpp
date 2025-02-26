#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_PEOPLE 1000

struct ticket{
    int type;
    char nama[100], type_name[100];
    ticket* next;
    ticket* prev;
}*h, *t;


void print_ticket(){
    if (h == NULL){
        puts("No Queue");
        return;
    }
    ticket *temp = h;
    int i = 1;
    puts(" No | Name     | Ticket_Type");
    while(temp != NULL){
        printf("%-04d. %-10s %s\n", i, temp->nama, temp->type_name);
        i++;
        temp = temp->next;
    }
}

void Call_ticket(){
    if (h == NULL){
        puts("No Queue");
        return;
    }
    for (int i = 0 ; i < 4 ; i++){

    }
}

ticket* create_node(char nama[], int type){
    ticket* current = (ticket*) malloc (sizeof(ticket));
    strcpy(current->nama, nama);
    if (type == 1) strcpy(current->type_name,"FAST_TRACK");
    else strcpy(current->type_name,"REGULER_TRACK");
    current->type = type;
    current->next = NULL;
    current->prev = NULL;
    return current;
}

void remove_node(char nama[]){
    if (h == NULL){
        puts("No Queue");
        return;
    }
    ticket* temp = h;
    while(strcmp(temp->nama, nama) != 0) temp = temp->next;
    if (strcmp(h->nama, nama) == 0) h = h->next;
    else if (strcmp(t->nama, nama) == 0) t = t->prev;
    else{
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        temp->next= temp->prev = NULL;
    }    
    free(temp);
}


void build_node(int type, char nama[]){
    ticket* current = create_node(nama, type);
    if (h == NULL){
        h = t = current;
    }else if (type == 2){
        t->next = current;
        current->prev = t;
        t = current;
    }else if (type == 1){
        ticket* temp = h;
        while (temp->next->type == 1) temp = temp->next;
        if (h->type == 2){
            current->next = h;
            h->prev = current;
            h = current;
        }else{
            current->next = temp->next;
            temp->next->prev = current;
            temp->next = current;
            current->prev = temp;
        }
    }
}

int main(){
    char input_menu[10], input_name[100];
    int input_total = 0, input_type = 0;

    while(1){
        scanf("%s", input_menu);getchar();
        if (strcmp(input_menu, "REGISTER") == 0){
            scanf("%d", &input_total);getchar();
            puts("NAME [1 -> Fast | 2 -> Reguler]");

            for (int i = 0 ; i < input_total ; i++){
                scanf("%s %d", input_name, &input_type);getchar();
                build_node(input_type, input_name);
            }

            print_ticket();
        }
        else if (strcmp(input_menu, "REMOVE") == 0){
            scanf("%d", &input_total);getchar();
            puts("NAME");
            for (int i = 0 ; i < input_total ; i++){
                scanf("%s", input_name);getchar();
                remove_node(input_name);
            }

            print_ticket();
        }
        else if (strcmp(input_menu, "CALL") == 0){
            Call_ticket();
        }
        else print_ticket();
    }
}
