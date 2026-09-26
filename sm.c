
/* Simple Guessing Game */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(void) {
    int guess,rand();
    srand(time(NULL));
    int secretNumber=rand()%100 + 1;
    do{
        printf("Enter your guess number(1-100):\n");
        scanf("%d",&guess);
        if(guess < secretNumber){
            printf("guess is too low.\n");
        }
        else if (guess > secretNumber){
            printf("guess is too high.\n");
        }
        else{
            printf("right guess.\n");
        }
    } while(guess<=100);
    return 0;
}