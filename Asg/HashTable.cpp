#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define Max 100

struct table{
    char nama[20], telp[13], email[17];
    table *next;
}*head[Max];

int key(char *nama){
    int l = strlen(nama);
    long long index = 0;
    
    // Penjumlahan Ascii
    for (int i = 0 ; i < l ; i++){
        index += nama[i];
    }

    // Pangkatin 2
    index *= index;

    //
    char convert[100];
    sprintf(convert, "%lld", index);
    l = strlen(convert);

    index = 0;
    if (l % 2 == 0){
        index += convert[l/2] - '0';
        index += (convert[l/2-1] - '0') * 10;
    }
    else index += convert[l/2] - '0';

    return index % Max;
}

int key2(char *nama){
    char convert[20];
    int l = strlen(nama);
    long long index = nama[0] + nama[l-1];
    index *= nama[l/2-1];
    index *= nama[1];
    sprintf(convert, "%lld", index);

    l = strlen(convert);

    if (l % 2 == 0){
        index += convert[l/2] - '0';
        index += (convert[l/2-1] - '0') * 10;
    }
    else index += convert[l/2] - '0';

    // index *= 7;

    return index%Max;
}

void push(char *nama, char *telp, char *email){
    int index = key(nama);
    table *input = (table*) malloc (sizeof(table));

    strcpy(input->nama, nama);
    strcpy(input->telp, telp);
    strcpy(input->email, email);
    input->next = NULL;

    if (head[index] == NULL) head[index] = input;
    else{
        input->next = head[index];
        head[index] = input;
    }

    // Print
    puts("_______________________________________________________");
    puts("| Key |    Name    |     telp     |       Email       |");
    puts("_______________________________________________________");
    printf("| %03d | %-10s | %-12s | %-17s |\n", index, input->nama, input->telp, input->email);
    puts("_______________________________________________________");

}

void Input_Data(){
    char nama[20] = {}, telp[13] = {}, email[18] = {};
    do{
        printf("Nama : "); scanf("%s", nama);getchar();
    }while(strlen(nama) > 20);

    do{
        printf("Telp : "); scanf("%s", telp);getchar();
    }while(strlen(telp) > 12);

    do{
        printf("Mail : "); scanf("%s", email);getchar();
    }while(strlen(email) > 17);

    push(nama, telp, email);
}

int search(char *nama){
    int found = 0; 

    for (int i = 0 ; i < Max ; i++){
        table *temp = head[i];    
        while(temp != NULL){
            if (strcmp(temp->nama, nama) == 0){
                found = 1;
                puts("_______________________________________________________");
                puts("| Key |    Name    |     telp     |       Email       |");
                puts("_______________________________________________________");
                printf("| %03d | %-10s | %-12s | %-17s |\n", i, temp->nama, temp->telp, temp->email);
                puts("_______________________________________________________");getchar();
                return found;
            }
            temp = temp->next;
        }
    }

    return found;
}

void Search_Data(){
    char *nama;
    printf("Nama : "); scanf("%s", nama);
    int found = search(nama);
    if (!found) {
        puts("Data not Found");getchar();
    }

    return;
}

void press(){
    puts("press anything to continue");getchar();
}


int del(char *nama){
    int del = 0;

    int index = key(nama);
    table *temp = head[index], *temp_next = temp->next;   
    if (strcmp(temp->nama, nama) == 0){
        head[index] = head[index]->next;
        puts("_______________________________________________________");
        puts("| Key |    Name    |     telp     |       Email       |");
        puts("_______________________________________________________");
        printf("| %03d | %-10s | %-12s | %-17s |\n", index, temp->nama, temp->telp, temp->email);
        puts("_______________________________________________________");getchar();
        free(temp);
        del = 1;
    }else {
        while(temp != NULL){
            if (strcmp(temp_next->nama, nama) == 0){
                del = 1;
                puts("_______________________________________________________");
                puts("| Key |    Name    |     telp     |       Email       |");
                puts("_______________________________________________________");
                printf("| %03d | %-10s | %-12s | %-17s |\n", index, temp_next->nama, temp_next->telp, temp_next->email);
                puts("_______________________________________________________");getchar();
                temp->next = temp_next->next;
                free(temp_next);
                return del;
            }
            temp = temp_next;
            temp_next = temp->next;
        }
    }

    return del;
}


void Delete_Data(){
    char *nama;
    printf("Nama : "); scanf("%s", nama);
    int found = del(nama);
    if (!found){
        puts("Data not Found");getchar();
    }

    return;
}

int main(){
    // int choice;
    // do {
    //     system("cls");
    //     puts("1. Input Data");
    //     puts("2. Search Data");
    //     puts("3. Delete Data");
    //     puts("4. Exit Program");
    //     do {
    //         printf(">> "); scanf("%d", &choice);getchar();
    //     }while (!(1 <= choice && choice <= 4));

    //     switch (choice){
    //         case 1:Input_Data();press();break;
    //         case 2:Search_Data();press();break;
    //         case 3:Delete_Data();press();break;
    //         case 4:return 0;break;
    //     }
    // }while (1);

    char nama[36][15]{
        "Adriel",
        "Agung",
        "Angger",
        "Clarissa",
        "Dara",
        "Darren",
        "Timotius",
        "Delicia",
        "Fance",
        "Gabriel",
        "Helen",
        "Jazzy",
        "Jonea",
        "Kent",
        "Jiovanni",
        "Tanwiputra",
        "Leonardo",
        "Lynel",
        "Qaishar",
        "Nathaniel",
        "Diah",
        "Nicholas",
        "Kimmy",
        "Olivia",
        "Ong",
        "Rio",
        "Samudra",
        "Samuel",
        "Sidney",
        "Syarifana",
        "Theodorus",
        "Vincent",
        "Wilson",
        "Linda",
        "Yosua"
    };

    puts("Key Yosua");
    for (int i = 0 ; i < 35 ; i++){
        printf("%15s : %lld\n", nama[i], key2(nama[i]));
    }

    // puts("Key Awal");
    // for (int i = 0 ; i < 35 ; i++){
    //     printf("%15s : %lld\n", nama[i], key(nama[i]));
    // }

    return 0;
}