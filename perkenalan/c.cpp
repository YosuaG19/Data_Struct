#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

//struct
// typedef struct player{
//     int hp, magic, gold;
//     char nama[30], rank[7];    
// }ply;

struct ply{
    int hp, magic, gold;
    char nama[30], rank[7];
}; 
 
//dynamic
ply* data = (ply*) malloc (sizeof(ply));

//funcitonal
int scan(){
    int input;
    scanf("%d", &input);getchar();
    return input;
}

void press(){
    puts("press anything to continue");getchar();
}

//global var
int ttl_ply = 0;



//menu
void main_menu(), menu1(), menu2(), menu3(), menu4();

int main(){
    int input;
    do {
        system("cls");
        main_menu();
        do {
            printf(">> ");
            input = scan();
        } while(!(1 <= input && input <= 5));

        switch (input){
            case 1: menu1();press();break;
            case 2: menu2();press();break;
            case 3: menu3();press();break;
            case 4: menu4();press();break;
            case 5: return 0;
        }

    } while(1);
}

void main_menu(){
    puts("1. Insert");
    puts("2. View");
    puts("3. Delete");
    puts("4. Upgrade");
    puts("5. Exit");
}
void menu1(){
    printf("Name\t: ");
    scanf("%[^\n]", data[ttl_ply].nama);getchar();

    do {
        printf("Rank\t: ");
        scanf("%[^\n]", data[ttl_ply].rank);getchar();
    }while (!(strcmp(data[ttl_ply].rank, "bronze") == 0 ||
              strcmp(data[ttl_ply].rank, "silver") == 0 ||
              strcmp(data[ttl_ply].rank, "gold") == 0));

    srand(time(NULL));

    int pointh, pointm, pgold;
    if (strcmp(data[ttl_ply].rank, "gold") == 0) pointh = 150, pointm = 20, pgold = 500;
    else if (strcmp(data[ttl_ply].rank, "silver") == 0) pointh = 100, pointm = 15, pgold = 250;
    else pointh = 50, pointm = 10, pgold = 0;
    data[ttl_ply].hp = rand() % 50 + pointh;
    data[ttl_ply].gold = rand() % 100 + pgold;
    data[ttl_ply].magic = rand() % 75 + pointm;

    puts("==========================================");
    printf("Name\t: %s\n", data[ttl_ply].nama);
    printf("Rank\t: %s\n", data[ttl_ply].rank);
    printf("Health\t: %d\n", data[ttl_ply].hp);
    printf("Magic\t: %d\n", data[ttl_ply].magic);
    printf("Gold\t: %d\n", data[ttl_ply].gold);
    puts("==========================================");

    ttl_ply++;
}
void menu2(){
    if (ttl_ply == 0) {
        puts("no character created");
        return;
    }
    for (int i = 0 ; i < ttl_ply ; i++){
        puts("==========================================");
        printf("Character %d\n", i+1);
        printf("Name\t: %s\n", data[i].nama);
        printf("Rank\t: %s\n", data[i].rank);
        printf("Health\t: %d\n", data[i].hp);
        printf("Magic\t: %d\n", data[i].magic);
        printf("Gold\t: %d\n", data[i].gold);
        puts("==========================================");
    }
}
void menu3(){
    menu2();
    int index;
    puts("Player index to Delete");
    do {
        if (ttl_ply == 1) printf("[1] : ");
        else printf("[%d - %d] : ", 1, ttl_ply);
        index = scan() - 1;
    } while (!(0<= index && index <= ttl_ply-1));

    for (int i = index ; i < ttl_ply ; i++){
        strcpy(data[i].nama, data[i+1].nama);
        strcpy(data[i].rank, data[i+1].rank);
        data[i].magic = data[i+1].magic;
        data[i].hp = data[i+1].hp;
        data[i].gold = data[i+1].gold;
    }
    ttl_ply--;
}
void menu4(){
    menu2();
    int index;
    puts("Player index to Upgrade");
    do {
        if (ttl_ply == 1) printf("[1] : ");
        else printf("[%d - %d] : ", 1, ttl_ply);
        index = scan() - 1;
    } while (!(0<= index && index <= ttl_ply-1));

    int spend;
    if ((data[index].gold / 50) < 1) {
        puts("not enough gold");
        return;
    }
    puts("Gold Spend");
    do {
        printf("[%d - %d] : ", 1, data[index].gold / 50);
        spend = scan();
    } while (!(1<= spend && spend <= data[index].gold / 50));

    data[index].magic += (150 * spend);
    data[index].hp += (150 * spend);
    data[index].gold -= (spend * 50);

    puts("==========================================");
    printf("Name\t: %s\n", data[index].nama);
    printf("Rank\t: %s\n", data[index].rank);
    printf("Health\t: %d\n", data[index].hp);
    printf("Magic\t: %d\n", data[index].magic);
    printf("Gold\t: %d\n", data[index].gold);
    puts("==========================================");
}