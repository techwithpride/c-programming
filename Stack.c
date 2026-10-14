/* Stack Implementation */

#include<stdio.h>
#include<stdlib.h>
#define MAX 4
int stack[MAX];
int top=-1;
void push();
void pop();
void display();

int main()
{
    int choice;
    while(1)
    {
        printf("\n*** STACK OPERATIONS MENU ***\n");
        printf("1.Push an element(Demonstrate overflow)\n");
        printf("2.Pop an element(Demonstrate underflow)\n");
        printf("3.Display the stack states\n");
        printf("4.Exit\n");
        printf("Enter your choice(1-4): ");
        if(scanf("%d",&choice)!=1)
        {
            printf("Invalid input. Please enter a number between 1 and 4.\n");
            while(getchar() != '\n'); // Clear the input buffer
            continue;
        }
        switch(choice)
        {
            case 1: push();
                    break;
            case 2: pop();
                    break;
            case 3: display();
                    break;
            case 4: printf("\nExiting  program.Goodbye!\n");
                    exit(0);
            default: printf("Invalid input! Please choose an option between 1 and 4.\n");
        }
    }
    return 0;
}

void push()
{
    int item;
    if(top>=MAX-1)
    {
        printf("\n[OVERFLOW DETECTED] Cannot push! Stack is completely full(Max size= %d).\n");
        return;
    }
    printf("Enter integer element to push: ");
    scanf("%d",&item);
    stack[++top]=item;
    printf("Successfully pushed %d onto the stack.\n",item);
}

void pop()
{
    if(top==-1)
    {
        printf("\n[UNDERFLOW DETECTED] Cannot pop! Stack is empty.\n");
        return;
    }
    printf("Popped element: %d\n",stack[top--]);
}

void display()
{
    if(top==-1)
    {
        printf("\nStack status: Empty\n");
        return;
    }
    printf("\n--- Stack Status ---\n");
    printf("Total capacity: %d\n",MAX);
    printf("Current number of elements: %d\n",top+1);
    printf("Elements (from top to bottom):\n");
    for(int i=top;i>0;i--)
    {
       if(i==top)
       {
           printf("[%d]<- Top.\n",stack[i]);
       }
       else
       {
           printf("[%d]\n",stack[i]);
       }
       printf("----------\n");
    }
}