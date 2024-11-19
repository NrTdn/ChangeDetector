#include <stdio.h>
#include <string.h>

char IsDifferentFile(FILE* file1, FILE* file2);
long fgetsize(FILE* file);
char* fContentBytes(const char* filePath); 
char* fContentChar(const char* fileByteContent, size_t size);