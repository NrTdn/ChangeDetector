#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/fileprocessor.h"

#define PATH_BUF 512
int main() {
    char programIsRunning = 0;
    char IsGettingPath = 0;
    char* path1 = (char*)malloc(PATH_BUF);
    if (path1 == NULL) {
        printf("Bellek ayirma hatasi!\n");
        return 1;
    }
    char* path2 = (char*)malloc(PATH_BUF);
    if (path2 == NULL) {
        printf("Bellek ayirma hatasi!\n");
        return 1;
    }

    printf("Taranacak klasor veya dosyanin yolunu girin veya dosyayi surukleyiniz:(Dikkat: Yolu girerken cift ters / kullanin)\n");
    fgets(path1, PATH_BUF, stdin);
    path1[strcspn(path1, "\n")] = 0;
    FILE* file;
    if(file = fopen(path1, "rb")) { programIsRunning = !0; fclose(file);}


    while(programIsRunning){
        printf("Program basladi\n");
        
        FILE* file;
        if(file = fopen(path1, "rb")){
            char* filestr = fContentBytes(path1);
            printf("Dosya: %s\n", filestr);
            fclose(file);
        }

        printf("Dosyanizi gordunuz. Bir dosya daha ekleyecek misiniz?(Y/N)\n");
        char* input = (char*)malloc(1);
        fgets(input, sizeof(input), stdin);
        if(memcmp(input, "N", 1) != 0){
            printf("Ekleyeceginiz dosyayi giriniz:\n");
            fgets(path2, PATH_BUF, stdin);
        }
        else break;
        free(input);
    }
    free(path1);
    free(path2);
    printf("Program Sona Erdi\n");
    return 0;
}