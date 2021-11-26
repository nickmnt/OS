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
    char * placerMother = "/tmp/fifo6";

    mkfifo(motherDecoder, 0666);
    mkfifo(motherFinder, 0666);
    mkfifo(motherPlacer, 0666);
    mkfifo(placerMother, 0666);

    char arr1[10000], arr2[10000];

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
                int i , j = 0;
                char refinedDecoder[10000];
                for(i = 0; i < len; i++)
                {
                    if((decoder[i] >= 'a' && decoder[i] <= 'z') || (decoder[i] >= 'A' && decoder[i] <= 'Z'))
                    {
                        refinedDecoder[j++] = decoder[i];
                    } 
                }
                refinedDecoder[j] = '\0';

                int fd1 = open(motherDecoder, O_WRONLY);
                write(fd1, refinedDecoder, strlen(refinedDecoder)+1);
                close(fd1);

                int fd2 = open(motherFinder, O_WRONLY);
                write(fd2, finder, strlen(finder)+1);
                close(fd2);
                
                int fd3 = open(motherPlacer, O_WRONLY);
                write(fd3, placer, strlen(placer)+1);
                close(fd3);

                printf("\nParent finished writing to pipes.\n");
                int fd4 = open(placerMother, O_RDONLY);
                read(fd4, arr2, sizeof(arr2));
                close(fd4);
                printf("\nParent received result from placer: %s\n", arr2);
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