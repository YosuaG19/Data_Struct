#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct siswa{
    int nilai;
    char nama[30];
    // siswa* next;
};



int main(){
    // struct biasa
    siswa data1;
    
    //akses anggota
    strcpy(data1.nama, "Adriel");
    data1.nilai = 90;
    printf("%d %s\n", data1.nilai, data1.nama);

    // alokasi memori dynamic
    siswa *data2 = (siswa*)malloc(sizeof(siswa));
    
    // akses anggota dari struct pointer
    strcpy(data2->nama, "Yosua");
    data2->nilai = 90;
    printf("%d %s\n", data2->nilai, data2->nama);

    // melepaskan alokasi memori
    free(data2);




    
    return 0;
}