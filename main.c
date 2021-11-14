#include <unistd.h>

int decoder() {
    return 0;
}

int finder() {
    return 0;
}

int placer() {
    return 0;
}

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

        } else {

        }
    } else {

    }
}