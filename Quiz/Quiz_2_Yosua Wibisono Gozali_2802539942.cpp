#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct nodes{
    int id, int_prio;
    char prio[15];
    bool impact = false, likelihood = false;
    nodes* next;
}*hash[10], *queue;

void print_queue(){
    nodes* temp = queue;    
    puts("Vunerability Queue: ");
    while (temp){
        printf("ID: %d - %s\n", temp->id, temp->prio);
        temp = temp->next;
    }
}

nodes *createnew(int id, bool impact, bool likelihood){
    nodes* curr = (nodes*) malloc(sizeof(nodes));
    curr->id = id; curr->impact = impact ; curr->likelihood = likelihood;
    if (impact && likelihood){
        strcpy(curr->prio, "Critical");
        curr->int_prio = 0;
    }else if (impact){
        strcpy(curr->prio, "High");
        curr->int_prio = 1;
    }else if (likelihood){
        strcpy(curr->prio, "Medium");
        curr->int_prio = 2;
    }else{
        strcpy(curr->prio, "Low");
        curr->int_prio = 3;
    }
    curr->next = NULL;

    return curr;
}

int hashing(int id){
    return id % 10;
}

void enqueue(int id, bool impact, bool likelihood){
    nodes* curr = createnew(id, impact, likelihood);
    if(!queue){
        queue = curr;
    }else{
        nodes* temp = queue;
        if (curr->int_prio < queue->int_prio || (queue->int_prio == curr->int_prio && queue->id > curr->id)){
            curr->next = queue; queue = curr;
        }else{
            while( temp->next != NULL && temp->next->int_prio < curr->int_prio || (temp->next->int_prio == curr->int_prio && temp->next->id <= curr->id)) temp = temp->next;
            curr->next = temp->next;temp->next = curr;
        }
    }
    // print_queue();
}

void print_hash(){
    puts("Stored Processed Vulnerabilities: ");
    for (int i = 0 ; i < 10 ; i++){
        if(hash[i] != NULL){
            printf("Index %d -> ", i);
            nodes* temp = hash[i];
            while(temp){
                if(temp->next == NULL) printf("ID: %d\n", temp->id);
                else printf("ID: %d, ", temp->id);
                temp = temp->next;
            }
        } 
    }   
}

void dequeue(){
    puts("Processing Vulnerabilities");
    int int_prio = queue->int_prio;
    while(queue->int_prio == int_prio){
        nodes* curr = queue;
        queue = queue->next;
        curr->next = NULL;
        int index = hashing(curr->id);
        if(!hash[index]){
            hash[index] = curr;
        }else{
            nodes* temp = hash[index];
            while(temp->next != NULL) temp = temp->next;
            temp->next = curr;
        }
        free(curr);
    }
}


int main(){
    enqueue(3001, 0, 0);
    enqueue(3002, 1, 1);
    enqueue(3003, 1, 0);
    enqueue(3004, 0, 1);
    enqueue(3005, 1, 1);
    print_queue();
    
    puts("");

    dequeue();

    puts("");

    print_hash();
    return 0;
}