#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node *left,*right;
};

struct Node* newNode(int data){
    struct Node *n = (struct Node*)malloc(sizeof(struct Node));
    n->data=data;
    n->left = n->right = NULL;
    return n;
} 

struct Node* createTree(){
    struct Node *root=NULL,*temp,*quene[7];
    int n,i,data,front=0,rear=0;

    printf("Enter number of nodes: ");
    scanf("%d",&n);

    if(n==0){
        return NULL;
    }

    printf("Enter elemets: ");
    scanf("%d",&data);

    root=newNode(data);
    quene[rear++]=root;

    for(i=1;i<n;i++){
        scanf("%d",&data);
        temp=newNode(data);
        while(quene[front]->left!=NULL && quene[front]->right!=NULL){
            front++;
        }

        if(quene[front]->left==NULL){
            quene[front]->left=temp;
        }
        else{
            quene[front]->right=temp;
        }

        quene[rear++]=temp;
    }
    return root;
}

void preorder(struct Node *root){
    if(root!=NULL){
        printf("%d ",root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(struct Node *root){
    if(root!=NULL){
        inorder(root->left);
        printf("%d ",root->data);
        inorder(root->right);
    }
}

void postorder(struct Node *root){
    if(root!=NULL){
        postorder(root->left);
        postorder(root->right);
        printf("%d ",root->data);
    }
}

int main(){
    struct Node *root=NULL;
    int choice;

    while(1){
        printf("\n\n---BINARY TREE MENU---\n");
        printf("1.Create Binary Tree \n");
        printf("2.Preorder Traversal \n");
        printf("3.Inorder Traversal \n");
        printf("4.Postorder Traversal \n");
        printf("5.Exit \n");
        printf("Enter choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
              root=createTree();
              printf("Binary Tree created \n");
              break;

            case 2:
              printf("Preorder: ");
              preorder(root);
              break;

            case 3:
              printf("Inorder");
              inorder(root);
              break;

            case 4:
              printf("Postorder: ");
              postorder(root);
              break;

            case 5:
              exit(0);

            default:
              printf("Invalid choice!");
        }
    }
}