#include <stdlib.h>
#include "../include/fileprocessor.h"

typedef union {
    unsigned char* bytes;
    char* str;
} CharToStrConverter;

long fgetsize(FILE* file){
    //Dosyanın akışı kullanılarak dosyanın boyutu elde edilebilir.
    fseek(file, 0, SEEK_END);//akış dosyanın başından başlatılır, sonuna kadar devam ettirilir.
    long size = ftell(file);//akış pointer'ının konumunu söyler.
    fseek(file, 0, SEEK_SET);//tekrar okuma işlemi yapılacağı zaman bir problem yaşanmaması için akış pointer'ı başa geri getirilir.
    return size;
}

char fIsDifferent(FILE* file1, FILE* file2){
    long size1 = fgetsize(file1);
    long size2 = fgetsize(file2);

    if(size1 != size2) return !0; //boyutları farklı

    unsigned char* buffer1 = (unsigned char*)malloc(size1);
    unsigned char* buffer2 = (unsigned char*)malloc(size2);

    size_t byteRead1 = fread(buffer1, 1, size1, file1);
    if(byteRead1 != size1) { printf("Okuma sirasinda hata meydana geldi.\n"); return 0; }
    size_t byteRead2 = fread(buffer2, 1, size2, file2);

    if(memcmp(buffer1, buffer2, size1) != 0) {
        free(buffer1);
        free(buffer2);
        return !0;
    }

    free(buffer1);
    free(buffer2);
    return 0;
}

char* fContentBytes(const char* filePath){
    FILE* file = fopen(filePath, "rb");

    if(file != NULL){
        long size = fgetsize(file);
        
        char* buffer = (char*)malloc(size);
        if(buffer == NULL) { printf("Bellek tahsis edilemedi.\n"); return NULL; }
        //char ch;
        //for (int i = 0; (ch = fgetc(file)) != EOF; i++){
        //    buffer[i] = ch;
        //}
        size_t bytesRead = fread(buffer, 1, size, file);
        if(bytesRead != size){
            printf("Dosya okunurken hata meydana geldi\n");
            free(buffer);
            fclose(file);
            return NULL;
        }
        fclose(file);
        return buffer;
    }
    printf("Dosya acilamadi.\n");
    return NULL;
}

char* fContentChar(const char* fileByteContent, size_t size){
    char* copy = (char*)malloc(size);
    if(copy == NULL) { printf("Alan tahsis edilemedi.\n"); return 0; }

    memcpy(copy, fileByteContent, size);

    copy[size] = '\0';

    CharToStrConverter converter;
    converter.bytes = copy;

    free(copy);

    return converter.str;
}