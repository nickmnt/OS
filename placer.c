#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void writeInFile(char *str){
    FILE *file ;
    file = fopen("../placerResult.txt" , "w");

    if(file != NULL){
        fputs(str , file);
    }

    fclose(file);
}

int main() {
    char * motherPlacer = "/tmp/fifo3";
    mkfifo(motherPlacer, 0666);

    char * placerMother = "/tmp/fifo6";
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

    char result[10000];
    int len = 0;

    int pointer = 0;

    int count = 0;

    for(int i = 0; i < strlen(arr1); ++i) {
        if(arr1[i] == '$') {
            while(arr2[pointer] != ' ' && arr2[pointer] != '\0') {
                result[count++] = arr2[pointer++];
            }
            pointer++;
        } else {
            result[count++] = arr1[i];
        }
    }
    result[count] = '\0';
    
    writeInFile(result);
    
    fd = open(placerMother, O_WRONLY);
    write(fd, result, strlen(result)+1);
    close(fd);

    
}