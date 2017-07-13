#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
int main()
{
    int ch;
    FILE *f = fopen("/proc/my_proc_entry", "r");
    while((ch = fgetc(f)) != EOF) {
        putchar(toupper(ch));
        getchar();
    }
    exit(0);
}
