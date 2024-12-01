#include <stdlib.h>
#include "../include/fileprocessor.h"

typedef union {
    unsigned char* bytes;
    char* str;
} CharToStrConverter;


int sizeArray(char *ptr)
{
    int offset = 0; //atlanacak eleman sayısının değeri.
    int size = 0; //dizinin uzunluğu
    //ptr dizinin ilk elemanıdır.
    while (*(ptr + offset) != '\0')
    {
        ++size;
        ++offset;
    }
    return size;
}

char* combineStr(const char* str1, const char* str2){
    const size_t size1 = strlen(str1);
    const size_t size2 = strlen(str2);

    char* combinedStr = (char*)malloc(size1 + size2 + 1);//null terminator için +1 eklenir.
    if(combinedStr == NULL){
        printf("Bellek ayirmada sikinti yasandi.\n");
        return NULL;
    }

    memcpy(combinedStr, str1, size1);//(nereden itibaren kopyalamaya başlanacağı, kopyalanacak str, dizi başlıgıcından itibaren kopyalanacak str'nin kaç byte'ının kopyalanacağı)
    memcpy(combinedStr + size1, str2, size2 + 1);
    return combinedStr;
}

long fgetsize(FILE* file){
    //Dosyanın akışı kullanılarak dosyanın boyutu elde edilebilir.
    fseek(file, 0, SEEK_END);//akış dosyanın başından başlatılır, sonuna kadar devam ettirilir.
    long size = ftell(file);//akış pointer'ının konumunu söyler.
    fseek(file, 0, SEEK_SET);//tekrar okuma işlemi yapılacağı zaman bir problem yaşanmaması için akış pointer'ı başa geri getirilir.
    return size;
}

char fIsDifferent(char* path1, char* path2){
    char* buffer1 = fContentBytes(path1);
    char* buffer2 = fContentBytes(path2);

    if(buffer1 != NULL && buffer2 != NULL){
        size_t buflen1 = sizeArray(buffer1);
        size_t buflen2 = sizeArray(buffer2);
        if(buflen1 != buflen2) return TRUE;
        if(memcmp(buffer1, buffer2, buflen1) == 0) return TRUE;
        return FALSE;
    }
    return FALSE;
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
    if(copy == NULL) { printf("Alan tahsis edilemedi.\n"); return NULL; }

    memcpy(copy, fileByteContent, size);

    copy[size] = '\0';

    CharToStrConverter converter;
    converter.bytes = copy;

    free(copy);

    return converter.str;
}