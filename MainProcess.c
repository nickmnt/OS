#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    char * motherDecoder = "/tmp/fifo1";
    char * motherFinder = "/tmp/fifo2";
    char * motherPlacer = "/tmp/fifo3";

    mkfifo(motherDecoder, 0666);
    mkfifo(motherFinder, 0666);
    mkfifo(motherPlacer, 0666);

    char arr1[10000];

    pid_t x = fork();
    if(x < 0) {
        printf("Error creating child.");
    } else if(x > 0) {
        //Parent
        pid_t y = fork();

        if(y < 0) {
            printf("Error creating second child.");
        } else if(y > 0) {
            //Parent
            pid_t z = fork();

            if(z < 0) {
                printf("Error creating third child");
            } else if(z > 0) {
                //Parent
                printf("OS Project 1\n");
                // printf("Enter your input:\n");
                // fgets(arr1, 10000, stdin);

                char buffer[10000];
                char res[1000000] = "" ;
                FILE *f;
                f = fopen("../test.txt" , "r");
                
                while (fgets(buffer , sizeof buffer , f))
                {
                    strcat(res , buffer);
                }

                char *decoder , *finder  , *placer ;


                char *split = strtok(res , "###");
                int k = 0 ;

                while(split != NULL){
                    if(k == 0){
                        decoder = split ;
                        k++;
                    }
                    else if(k == 1){
                        finder = split ;
                        k++;
                    }
                    else if(k == 2){
                        placer = split ;
                    }


                    split = strtok(NULL , "###");
                }

                int len = strlen(decoder);
                int i , j;
                for(i = 0; i < len; i++)
                {
                    if(decoder[i] == '\n')
                    {
                        for(j = i; j < len; j++)
                        {
                            decoder[j] = decoder[j + 1];
                        }
                        len--;
                        i--;	
                    } 
                }

                int fd1 = open(motherDecoder, O_WRONLY);
                write(fd1, decoder, strlen(decoder)+1);
                close(fd1);

                int fd2 = open(motherFinder, O_WRONLY);
                write(fd2, finder, strlen(finder)+1);
                close(fd2);
                
                int fd3 = open(motherPlacer, O_WRONLY);
                write(fd3, placer, strlen(placer)+1);
                close(fd3);

                printf("\nParent finished writing to pipes, should add option to get information from placer later on?");
            } else {
                //Placer
                char *args[] = {"placer", "C", "Programming", NULL};
                execv("./placer", args);
            }
        } else {
            //Finder
            char *args[] = {"finder", "C", "Programming", NULL};
            execv("./finder", args);
            return 0;
        }
    } else {
        //Decoder
        char *args[] = {"decoder", "C", "Programming", NULL};
        execv("./decoder", args);
    }
}