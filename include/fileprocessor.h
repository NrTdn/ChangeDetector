#include <stdio.h>
#include <string.h>

#define TRUE !0
#define FALSE 0

int sizeArray(char *ptr);
char* combineStr(const char* str1, const char* str2);
char fIsDifferent(char* path1, char* path2);
long fgetsize(FILE* file);
char* fContentBytes(const char* filePath); 
char* fContentChar(const char* fileByteContent, size_t size);