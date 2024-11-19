#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/fileprocessor.h"

#define PATH_BUF 512
int main() {
    char programIsRunning = 0;
    char IsGettingPath = 0;
    char* path = (char*)malloc(PATH_BUF);
    if (path == NULL) {
        printf("Bellek ayirma hatasi!\n");
        return 1;
    }
    
    printf("Taranacak klasor veya dosyanin yolunu girin veya dosyayi surukleyiniz:(Dikkat: Yolu girerken cift ters / kullanin)\n");
    fgets(path, PATH_BUF, stdin);
    path[strcspn(path, "\n")] = 0;
    FILE* file;
    if(file = fopen(path, "rb")) programIsRunning = !0;


    while(programIsRunning){
        printf("Program basladi\n");
        
        FILE* file;
        if(file = fopen(path, "rb")){
            char* filestr = fContentBytes(path);
            printf("Dosya: %s\n", filestr);
        }

        printf("Dosyanizi gordunuz. Bir dosya daha ekleyecek misiniz?(Y/N)\n");
        char* input = (char*)malloc(1);
        fgets(input, sizeof(input), stdin);
        if(memcmp(input, "N", 1) != 0){
            printf("Ekleyeceginiz dosyayi giriniz:\n");
        }
        else break;
    }
    
    printf("Program Sona Erdi\n");
    return 0;
}