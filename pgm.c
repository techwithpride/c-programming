/* program to processing sparse matrices */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_TERMS 100

typedef struct {
    int row;
    int col;
    int value;
} term;

typedef struct {
    int rows;
    int cols;
    int terms;
    term data[MAX_TERMS];
} SparseMatrix;

void readSparseMatrix(SparseMatrix *matrix) {       /*Read a sparse matrix*/
    int i;  
    printf("Enter number of rows and columns : ");
    scanf("%d %d", &matrix->rows, &matrix->cols);
    printf("Enter the number of non-zero terms: ");
    scanf("%d", &matrix->terms);
    if(matrix->terms > MAX_TERMS) {
        printf("there are too many non zero elements:\n");
        exit(1);
    }
    printf("Enter the each non zero terms as rows and column values:\n");
    printf("(Use 0-based indexing)\n");
    for (int i = 0; i < matrix->terms; i++) {
        scanf("%d %d %d",
             &matrix->data[i].row, 
             &matrix->data[i].col,
             &matrix->data[i].value);
    }
}

void displaySparse(const SparseMatrix *matrix) {      /*Display triple representation*/
    int i;
    printf("\n Rows: %d, Columns: %d, Non-zero elements: %d\n", matrix->rows, matrix->cols, matrix->terms);
    printf("Rows\tColumns\tValues\n");
    for(i=0;i<matrix->terms;i++) {
        printf("%d\t%d\t%d\n",
            matrix->data[i].row,
            matrix->data[i].col, 
            matrix->data[i].value);
    }
} 

void displayFullMatrix(const SparseMatrix  *matrix) {    /*Display sparse matrix from  normal matrix form*/
    int i, j, k = 0;

    printf("\n Matrix:\n");

    for(i=0;i<matrix->rows;i++) {
        for(j=0;j<matrix->cols;j++) {
            if(k < matrix->terms && 
                matrix->data[k].row == i && 
                matrix->data[k].col == j) {
                printf("%4d ", matrix->data[k].value);
                k++;
            } else {
                printf("%4d ",0);
            }
        }
        printf("\n");
    }
}

int addSparseMatrices(const SparseMatrix *a,       /*Addition of 2 sparse matrices*/
                      const SparseMatrix *b,
                      SparseMatrix *c){
                       
                        int i=0,j=0,k=0;
                        if(a->rows != b->rows || a->cols != b->cols) {
                            return 0; // matrices are not compatible for addition
                        }

                        c->rows = a->rows;
                        c->cols = a->cols;
                        c->terms = 0;

                        while(i < a->terms && j < b->terms) {
                            if(a->data[i].row < b->data[j].row || 
                               (a->data[i].row == b->data[j].row && 
                                a->data[i].col < b->data[j].col)) {
                               
                                c->data[k++] = a->data[i++];

                            } else if(b->data[j].row < a->data[i].row || 
                                      (b->data[j].row == a->data[i].row &&
                                       b->data[j].col < a->data[i].col)) {
                               
                                c->data[k++] = b->data[j++];

                            } else {
                                // same position, add values
                                int sum = a->data[i].value + b->data[j].value;
                                if(sum != 0) {
                                    c->data[k].row = a->data[i].row;
                                    c->data[k].col = a->data[i].col;
                                    c->data[k].value = sum;
                                    k++;
                                }

                                i++;
                                j++;
                            }
                        }
                       while(i < a->terms) {
                            c->data[k++] = a->data[i++];
                        }
                        while(j < b->terms) {
                            c->data[k++] = b->data[j++];
                        }

                        c->terms = k;
                        return 1; // addition successful
                    
                    }


void TransposeSparse(const SparseMatrix *a, SparseMatrix *t) {   /*Transpose of sparse matrix*/
    int i, j, k = 0;

    t->rows = a->cols;
    t->cols = a->rows;
    t->terms = a->terms;
                                         /* *scan columns form left to right.
                                            *For each column,copy all elements belonging.
                                            *To that column with row and column exchanged. */
    for(j=0;j<a->cols;j++) {
        for(i=0;i<a->terms;i++) {
            if(a->data[i].col == j) {
                t->data[k].row = a->data[i].col;
                t->data[k].col = a->data[i].row;
                t->data[k].value = a->data[i].value;
                k++;
            }
        }
    }
}

int main() {                               /* Main function */
    SparseMatrix A,B,Sum,Transpose;
    
    printf("\n===== SPARSE MATRIX A =====\n");
    readSparseMatrix(&A);
    
    printf("\n===== SPARSE MATRIX B =====\n");
    readSparseMatrix(&B);

    printf("\n===== MATRIX A =====\n");
    displaySparse(&A);
    displayFullMatrix(&A);

    printf("\n===== MATRIX B =====\n");
    displaySparse(&B);
    displayFullMatrix(&B);

    /*Addition*/
    printf("\n===== A+B =====\n");
    if(addSparseMatrices(&A, &B, &Sum)) {
        displaySparse(&Sum);
        displayFullMatrix(&Sum);
    } else {
        printf("Addition is not possible : dimensions are different.\n");
    }

    /*Transpose of A*/

    printf("\n===== TRANSPOSE OF A =====\n");
    TransposeSparse(&A, &Transpose);
    displaySparse(&Transpose);
    displayFullMatrix(&Transpose);

    /*Transpose of B*/

    printf("\n===== TRANSPOSE OF B =====\n");
    TransposeSparse(&B, &Transpose);
    displaySparse(&Transpose);
    displayFullMatrix(&Transpose);

    return 0;
}   