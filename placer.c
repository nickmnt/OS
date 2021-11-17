#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    char * motherPlacer = "/tmp/fifo3";
    mkfifo(motherPlacer, 0666);

    char * finderPlacer = "/tmp/fifo5";
    mkfifo(finderPlacer, 0666);

    char arr1[10000], arr2[10000];
    int fd = open(motherPlacer, O_RDONLY);
    read(fd, arr1, sizeof(arr1));
    close(fd);

    printf("\nPlacer finished reading from mother: %s\n", arr1);

    fd = open(finderPlacer, O_RDONLY);
    read(fd, arr2, sizeof(arr2));
    close(fd);

    printf("\nPlacer finished reading from finder: %s\n", arr2);
}