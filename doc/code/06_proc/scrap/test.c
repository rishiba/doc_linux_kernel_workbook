#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "myproc.h"

#define LEN 1024

int main () {

    int fd = open (PROC_FULL_PATH, O_RDWR);
    char buf[LEN] = "Hey People";
    int retval;

    if (fd < 0) {
        perror("myproc_test: ");
        fprintf(stderr, "Make sure that the myproc module is loaded");
    }

    retval = write(fd, buf, 11);

    close(fd);


    return 0;
}
