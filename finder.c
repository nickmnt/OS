#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    char * motherFinder = "/tmp/fifo2";
    mkfifo(motherFinder, 0666);

    char * decoderFinder = "/tmp/fifo4";
    mkfifo(decoderFinder, 0666);

    char arr1[10000], arr2[10000];
    int fd = open(motherFinder, O_RDONLY);
    read(fd, arr1, sizeof(arr1));
    close(fd);

    printf("\nFinder finished reading from mother.\n");
    printf("%s\n", arr1);

    fd = open(decoderFinder, O_RDONLY);
    read(fd, arr2, sizeof(arr2));
    close(fd);

    printf("\nFinder finished reading from decoder\n");
    printf("%s\n",arr2);
}