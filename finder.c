#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void splitNumbers(char *str , char *str2){
    
    int count = 0 , j = 0 , i;
    char result[1000][10] ;
    for(i = 0 ; i < strlen(str) ; i++){
        if(str[i] == '$' || str[i] == '\0'){
            result[count][j] = '\0';
            count++;
            j = 0;
        }
        else{
            result[count][j] = str[i];
            j++;
        }
    }

    int resCounter = 0 ;
    char words[strlen(str2)];

    for(i = 0 ; i < count ; i++){
        char *split1 = strtok(result[i] , " ");
        char *split2 = strtok(NULL , " ");

        int startIdx = atoi(split1);
        int length = atoi(split2);

        int endIndex = length + startIdx , k  , l = 0;

        for(k = startIdx ; k < endIndex ; k++ ){
            words[resCounter] = str2[k];
            resCounter++;
        }
        words[resCounter] = ' ';
        resCounter++;
    }

    //send words to placer with pipe
    puts(words);
}

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

    char *string = arr1 , *string2 = arr2;

    splitNumbers(string , string2);
}