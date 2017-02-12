#include <stdio.h>
#include <stdlib.h>

extern char* StrSHA256(const char* str, long long length, char* sha256);

int main(void){
    char text[] = "abc";
    char sha256[100];
    StrSHA256(text,sizeof(text)-1,sha256);  // sizeof()计算的结果包含了末尾的'\0'应减1
    puts(sha256);
    return 0;
}