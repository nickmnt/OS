#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
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
                printf("Parent doing nothing... (Replace with wait?)");
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