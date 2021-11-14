#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void decodeAndWrite(char *str, char * decoderFinder){
    int counter ;
    char result[strlen(str)];

    for(counter = 0 ; counter < strlen(str) ; counter++){
        if(str[counter] >= 'a' && str[counter] <= 'z'){
            result[counter] = (str[counter]-'a'-3+26)%26+'a';
        }
        else if(str[counter] >= 'A' && result[counter] <= 'Z'){
            result[counter] = (str[counter]-'A'-3+26)%26+'A';
        }
    }

    //output
    int fd = open(decoderFinder, O_WRONLY);
    write(fd, result, strlen(result)+1);

    //printf("\n\n%s" , result);
}

void main(){
    char * motherDecoder = "/tmp/fifo1";
    mkfifo(motherDecoder, 0666);

    char * decoderFinder = "/tmp/fifo4";
    mkfifo(decoderFinder, 0666);

    char arr1[10000];
    int fd = open(motherDecoder, O_RDONLY);
    read(fd, arr1, sizeof(arr1));

    //dummy input
    //char *string = "afklakgKHSFLgasfaf"; 
    char *string = arr1; 
    printf("\nDecoder run .");

    decodeAndWrite(string, decoderFinder);
}