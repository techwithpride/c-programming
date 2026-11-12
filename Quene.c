#include<stdio.h>
#include<stdlib.h>
# define MAX 5

int quene[MAX],front=-1,rear=-1;

int isFull(){
    return(rear==MAX-1);
}

int isEmpty(){
    return(front==-1 || front>rear);
}

void addJobs(){
    if(isFull()){
        printf("\n[OVERFLOW DETECTED] ! Queue is full \n");
        return;
    }
    int id;
    printf("Enter job ID: ");
    scanf("%d", &id);
    if(front==-1){
        front=0;
    }
    quene[++rear]=id;
    printf("Job %d is added \n",id);
}

void processJobs(){
    if(isEmpty()){
        printf("\n[UNDERFLOW DETECTED] ! Queue is empty \n");
        front=rear=-1;
        return;
    }
    printf("Job %d is processed \n",quene[front++]);
    if(front>rear){
        front=rear=-1;
    }
}

void displayWaitingJobs(){
    if(isEmpty()){
        printf("\nWaiting Jobs:0 \n");
        return;
    }
    printf("Waiting Jobs:%d\n",(rear-front+1));
}

void demonstrateOverflowUnderflow(){
    if(isFull()){
        printf("\n->Overflow Detected!\n");
    }
    if(isEmpty()){
        printf("\n->Underflow Detected!\n");
    }
}

int main(){
    int ch;
    while(1){
        printf("1.Add  2.Process  3.Count  4.Demo  5.Exit  choice: \n");
        if(scanf("%d",&ch)!=1){
            while(getchar()!='\n');
            continue;
        }
        if(ch==1){
            addJobs();
        }else if(ch==2){
            processJobs();
        }else if(ch==3){
            displayWaitingJobs();
        }else if(ch==4){
            demonstrateOverflowUnderflow();
        }else if(ch==5){
            exit(0);
        }
    }
    return 1;
}