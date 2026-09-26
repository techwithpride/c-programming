/* Library Management System */


#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define AVAILABLE "Available"
#define ISSUED "Issued"

struct Book {
    int book_id;
    char title[100];
    char author[100];
    char status[10];
};

struct Book *books=NULL;
int N=0;

void create();
void display();
void search();
void issueBook();
void returnBook();

int readInt (){
    char input[100];
    int value;
    while(1){
        fgets(input, sizeof(input), stdin);
        if(sscanf(input, "%d", &value) == 1){
            return value;
        } else {
            printf("Invalid input. Please enter an integer: ");
        }
    }
}

float readFloat (){
    char input[100];
    float value;
    while(1){
        fgets(input, sizeof(input), stdin);
        if(sscanf(input, "%f", &value) == 1){
            return value;
        } else {
            printf("Invalid input. Please enter a float: ");
        }
    }
}

void removeNewline(char str[]) {
    str[strcspn(str, "\n")] = 0;
}

void create(){
    int i;
    if (books!=NULL) {
        free(books);
        books=NULL;
    }
    printf("Enter the number of books: ");
    N=readInt();
    if(N <= 0) {
        printf("Number of books must be greater than 0.\n");
        N=0;
        return;
    }
    books = (struct Book*)malloc(N * sizeof(struct Book));
    for(i=0;i<N;i++){
        printf("\n=========== Book %d ============\n", i+1);
        printf("Enter Book ID: ");
        books[i].book_id = readInt();
        printf("Enter Book Title: ");
        fgets(books[i].title, sizeof(books[i].title), stdin);
        removeNewline(books[i].title);
        printf("Enter Book Author: ");
        fgets(books[i].author, sizeof(books[i].author), stdin);
        removeNewline(books[i].author);
        printf("Enter price: ");
        float price = readFloat();
        strcpy(books[i].status, AVAILABLE);
    }
    printf("\n=================================\n");
    printf("Books records created successfully!\n");
    printf("===================================\n");
}

void display(){
    books = (struct Book*)realloc(books, N * sizeof(struct Book));
    int i,found=0;
    if(books==NULL || N==0){
        printf("\n No books available.\n");
        return;
    }
    for(i=0;i<N;i++){
        if(strcmp(books[i].status, AVAILABLE) == 0){
         printf("\n=========== Book %d ============\n", i+1);
         printf("Book ID: %d\n", books[i].book_id);
         printf("Title: %s\n", books[i].title);
         printf("Author: %s\n", books[i].author);
         printf("Status: %s\n", books[i].status);
         printf("=================================\n");
         found=1;
        }
    }
    if(found==0){
          printf("\n No  books are currently available.\n");
    }
 }

void search(){
    books = (struct Book*)realloc(books, N * sizeof(struct Book));
    int id, i, found=0;
    if(books==NULL || N==0){
      printf("\n No books available.\n");
      return;
    } 
    printf("Enter Book ID to search: ");
    id = readInt(); 
    for(i=0;i<N;i++){
        if(books[i].book_id == id){
            printf("\n=========== Book Found ============\n");
            printf("Book ID: %d\n", books[i].book_id);
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("Status: %s\n", books[i].status);
            printf("=================================\n");
            found=1;
            break;
        }
    }
    if(found==0){
            printf("\n Book with ID %d not found.\n", id);
    }
}

void issueBook(){
    books = (struct Book*)realloc(books, N * sizeof(struct Book));
    int id, i, found=0;
    if(books==NULL || N==0){
      printf("\n No books records available.\n");
      return;
   } 
     printf("Enter Book ID to issue: ");
     id = readInt(); 
     for(i=0;i<N;i++){
        if(books[i].book_id == id){
            if(strcmp(books[i].status, AVAILABLE) == 0){
                strcpy(books[i].status, ISSUED);
                printf("\n Book with ID %d has been issued successfully.\n", id);
            } else {
                printf("\n Book with ID %d is already issued.\n", id);
            }
            found=1;
            break;
        }
    }
    if(found==0){
            printf("\n Book with ID %d not found.\n", id);
    }
}

void returnBook(){
    books = (struct Book*)realloc(books, N * sizeof(struct Book));
    int id, i, found=0;
    if(books==NULL || N==0){
      printf("\n No books records available.\n");
      return;
   } 
     printf("Enter Book ID to return: ");
     id = readInt(); 
     for(i=0;i<N;i++){
        if(books[i].book_id == id){
            if(strcmp(books[i].status, ISSUED) == 0){
                strcpy(books[i].status, AVAILABLE);
                printf("\n Book with ID %d has been returned successfully.\n", id);
            } else {
                printf("\n Book with ID %d was not issued.\n", id);
            }
            found=1;
            break;
        }
    }
    if(found==0){
            printf("\n Book with ID %d not found.\n", id);
    }
}

int main(){
    int choice;
    while(1){
        printf("\n==================================================\n");
        printf("\n============ Library Management System ============\n");
        printf("\n===================================================\n");
        printf("1. Create Book Records\n");
        printf("2. Display Available Books\n");
        printf("3. Search for a Book\n");
        printf("4. Issue a Book\n");
        printf("5. Return a Book\n");
        printf("6. Exit\n");
        printf("\n===================================================\n");
        printf("Enter your choice: ");
        choice = readInt();
        switch(choice){
            case 1:
                create();
                break;
            case 2:
                display();
                break;
            case 3:
                search();
                break;
            case 4:
                issueBook();
                break;
            case 5:
                returnBook();
                break;
            case 6:
                if (books != NULL) {
                    free(books);
                    books = NULL;
                }
                return 0;
            default:
                printf("Invalid choice! Enter a number from 1 to 6.\n");
        }
    }
    return 0;
}