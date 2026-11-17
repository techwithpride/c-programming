/* Polynomial Operations */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct Node{
    int coeff,exp;
    struct Node* next;
};

typedef struct Node* Polynomial;

Polynomial createNode(int coeff,int exp);
Polynomial initializeList();
Polynomial insertTerm(Polynomial head,int coeff,int exp);
Polynomial readPolynomial(int PolyNumber);
int getDegree(Polynomial head);
void displayPolynomial(Polynomial head);
Polynomial addPolynomials(Polynomial poly1, Polynomial poly2);

int main(){
    Polynomial poly1=NULL,poly2=NULL,polySum=NULL;
    poly1=readPolynomial(1);
    poly2=readPolynomial(2);

    printf("\n===================================\n");
    printf("POLYNOMIAL REPRESENTATION BASED ON DEGREE\n");
    printf("===================================\n");

    printf("POLY1(Degree %d): ",getDegree(poly1));
    displayPolynomial(poly1);

    printf("POLY2(Degree %d): ",getDegree(poly2));
    displayPolynomial(poly2);

    polySum=addPolynomials(poly1,poly2);

    printf("\n===================================\n");
    printf("RESULT OF ADDITION(POLYSUM)\n");
    printf("===================================\n");
    printf("POLYSUM(Degree %d): ",getDegree(polySum));
    displayPolynomial(polySum);
    printf("\n===================================\n");

    return 0;
}

Polynomial createNode(int coeff,int exp){
    Polynomial newNode=(Polynomial)malloc(sizeof(struct Node));
    if(newNode==NULL){
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->coeff=coeff;
    newNode->exp=exp;
    newNode->next=NULL;
    return newNode;
}

Polynomial initializeList(){
    Polynomial head=createNode(-1,-1);
    head->next=head; 
    return head;
} 

Polynomial insertTerm(Polynomial head,int coeff,int exp){
    Polynomial newNode,prev,curr;
    if(coeff==0){
       return head;
    }

    newNode=createNode(coeff,exp);
    prev=head;
    curr=head->next;

    while(curr!=head && curr->exp>exp){
        prev=curr;
        curr=curr->next;
    }
    if(curr!=head && curr->exp==exp){
        curr->coeff+=coeff;
        free(newNode);
        if(curr->coeff==0){
            prev->next=curr->next;
            free(curr);
        }
    }
    else{
        prev->next=newNode;
        newNode->next=curr;
    }
    return head;
}

Polynomial readPolynomial(int PolyNumber){
    Polynomial head=initializeList();
    int numTerms,coeff,exp;
    printf("\n---Reading POLY %d---\n",PolyNumber);
    printf("Enter the number of terms : ");
    scanf("%d",&numTerms);
    for(int i=0;i<numTerms;i++){
        printf("Enter term %d(coefficient and exponent/power): ",i+1);
        scanf("%d %d",&coeff,&exp);
        insertTerm(head,coeff,exp);
    }
    return head;
}

int getDegree(Polynomial head){
    if(head->next==head){
        return 0; 
    }
    return head->next->exp;
}


void displayPolynomial(Polynomial head){
    int maxDegree,isFirst,currentExp,absCoeff;
    Polynomial temp;
    if(head->next==head){
        printf("0\n");
        return;
    }

    maxDegree=getDegree(head);
    temp=head->next;
    isFirst=1;

    for(currentExp=maxDegree;currentExp>=0;currentExp--){
        int coeff=0;
        if(temp!=head && temp->exp==currentExp){
            coeff=temp->coeff;
            temp=temp->next;
        }
        if(coeff==0){
            continue;
        }    
        if(coeff>0&&!isFirst){
            printf("+");
        }
        else if(coeff<0){
            if(isFirst){
                printf("-");
            }
            else{
                printf(" - ");
            }
        }
        absCoeff=abs(coeff);
        if(currentExp==0){
            printf("%d",absCoeff);
        }
        else if(currentExp==1){
            if(absCoeff==1){
                printf("x");
            }
            else{
                printf("%dx",absCoeff);
            }
        }
        else{
            if(absCoeff==1){
                printf("x^%d",currentExp);
            }
            else{
                printf("%dx^%d",absCoeff,currentExp);
            }
        }
        isFirst=0;
    }
    printf("\n");
}


Polynomial addPolynomials(Polynomial poly1, Polynomial poly2){
    Polynomial polySum=initializeList();
    Polynomial p1=poly1->next;
    Polynomial p2=poly2->next;

    while(p1!=poly1 && p2!=poly2){
        if(p1->exp==p2->exp){
            int sumCoeff=p1->coeff+p2->coeff;
            insertTerm(polySum,sumCoeff,p1->exp);
            p1=p1->next;
            p2=p2->next;
        }
        else if(p1->exp>p2->exp){
            insertTerm(polySum,p1->coeff,p1->exp);
            p1=p1->next;
        }
        else{
            insertTerm(polySum,p2->coeff,p2->exp);
            p2=p2->next;
        }
    }

    while(p1!=poly1){
        insertTerm(polySum,p1->coeff,p1->exp);
        p1=p1->next;
    }

    while(p2!=poly2){
        insertTerm(polySum,p2->coeff,p2->exp);
        p2=p2->next;
    }

    return polySum;
}