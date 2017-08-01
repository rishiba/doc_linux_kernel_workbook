#include <stdio.h>

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "myproc.h"

#define LEN 1024

int main () {

    int fd = open (PROC_FULL_PATH, O_RDONLY);
    char buf[LEN];
    int retval;

    if (fd < 0) {
        perror("myproc_test: ");
        fprintf(stderr, "Make sure that the myproc module is loaded");
        exit(0);
    }

    retval = read(fd, buf, LEN);

    printf("\nData Read is %s", buf);
    printf("\nBytes Read is %d", retval);

    close(fd);

    printf("\nThis open should fail because of the permissons we set in the code");
    fd = open (PROC_FULL_PATH, O_RDWR);
    if (fd < 0) {
        perror("myproc_test: ");
    }

    return 0;
}
