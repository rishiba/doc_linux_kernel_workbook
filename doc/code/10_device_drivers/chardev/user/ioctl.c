#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>

#define DEV_NAME_LENGTH 20

struct param {
    int number;
    char **ptr;
};

int main(int argc, char *argv[])
{
    int i;
    char dev_name[DEV_NAME_LENGTH];
    struct param ioctl_params;
    int fd, retval;
    printf("\n\nNumber of arguements passed %d", argc);

    for (i = 0; i < argc; i++) {
        printf("\nARG %d is %s", i, argv[i]);
    }

    if (argc < 4) {
        printf("\n\n Number of arguements is very less");
        printf("\n\n argc 1 should be device name");
        printf("\n\n argc 2 should be the ioctl number");
        printf("\n\n argc 3 onwards should be all the arguements");
        goto exit;
    } else {
        printf("\n\n Number of arguements is fine .... proceeding");
    }
    /* argc 1 should be device name */
    /* argc 2 should be the ioctl number */
    /* argc 3 onwards should be all the arguements */
    /* Asumming that the parameters are correct */
    ioctl_params.number = argc - 3;
    ioctl_params.ptr = argv[3];

    printf("\nXXXX ARG %d is %s", i, ioctl_params.ptr);
    /* Substract from a single digit number to get the correct digit */
    int ioctl_number = argv[2][0] - 48;

    printf("\n\nioctl number is %d", ioctl_number);

    strcpy(dev_name, argv[1]);
    fd = open(dev_name, O_RDWR);

    /* complain if the open failed */
    if (fd == -1) {
        printf("Error in opening the device %s", dev_name);
        return 1;
    } else {
        printf("\n\nOpened the device file .... proceeding");
    }

    /* Call the ioctl */
    printf("\n\nCalling the ioctl, lets see what happens");
    retval = ioctl(fd, ioctl_number, &ioctl_params);
    if (retval == -1) {
        perror("ioctl : ");
        printf("\n\nIOCTL Failed boss");
    } else {
        printf("\n\nWorks fine");
    }

 exit:
    return 0;
}
