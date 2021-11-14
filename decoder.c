#include <stdio.h>
#include <string.h>

void main(){

    //dummy input
    char *string = "afklakgKHSFLgasfaf"; 
    printf("\nDecoder run .");

    decodeAndWrite(string);
}

void decodeAndWrite(char *str){
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
    printf("\n\n%s" , result);
}