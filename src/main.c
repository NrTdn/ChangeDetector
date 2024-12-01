#include <stdio.h>
#include <stdlib.h>
#include "../include/fileprocessor.h"

#define PATH_BUF 512
#define IMPLEMENTATION_ERROR 1
int main(int argc, char** argv) {

    if(argc != 3){
        printf("Yanlis implementasyon, Dogru Kullanim:\n    ./detector dosya1.uzanti dosya2.uzanti\n");
        return IMPLEMENTATION_ERROR;
    }

    char* mainPath = "C:\\Users\\HelyakX\\Desktop\\Visual Studio Code\\C\\Change Commiter\\";

    //printf("Birinci arguman: %s\n",argv[1]);
    //printf("İkinci arguman: %s\n",argv[2]);

    
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

    path1 = argv[1];
    path2 = argv[2];

    char* combinedPath1 = combineStr(mainPath, path1);
    char* combinedPath2 = combineStr(mainPath, path2);
    
    //char result = fIsDifferent(path1, path2); => Bu şekilde de kullanılabilir.
    //Bu şekilde kullanılmazsa mainPath değişkeninin içindeki değeri değiştirmeniz gerekir.
    //Manuel olarak değiştirmek yerine ./detector çağrısında parametre olarak alınabilir.

    char result = fIsDifferent(combinedPath1, combinedPath2);
    switch (result)
    {
    case TRUE:
        printf("Farkli Dosyalar\n");
        break;
    case FALSE:
        printf("Ayni Dosyalar\n");
        break;
    default:
        break;
    }

    free(path1);
    free(path2);
    free(combinedPath1);
    free(combinedPath2);
    return 0;
}