#include<string.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct mahsiswa{
    char nim[10];
    char nama[30];
}mhs;

int main (){
    // mhs* nama = (return memory) malloc (memory size);
    mhs* siswa = (mhs*) malloc (sizeof(mhs));
    
}