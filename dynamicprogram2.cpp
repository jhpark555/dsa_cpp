#include <stdio.h>
#include <stdlib.h>


typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
}Node;

void addChildSum(Node *root)
{

    if( root==NULL) return;

    addChildSum(root->left);
    addChildSum(root->right);

    int finalSum=root->data;

    if(root->left!=NULL)
        finalSum +=root->left->data;
    if(root->right !=NULL)
        finalSum +=root->right->data;

    root->data = finalSum;
    printf("sum=%d \n", root->data);
}

Node *insertNode(int data)
{
    Node *newNode= (Node *)malloc(sizeof(Node));
    newNode->data= data;
    newNode->left=NULL;
    newNode->right=NULL;

    return newNode;
}

void postorder(Node *root)
{
    Node *curr=root;
    if (curr !=NULL) {
        postorder(curr->left);
        postorder(curr->right);
        printf("%d ",curr->data);
    }
}
int main(int argc, char *argv[])
{
    Node *root = insertNode(2);
    root->left= insertNode(4);
    root->right= insertNode(1);
    root->left->left=insertNode(6);
    root->left->right=insertNode(9);
    root->left->right->left= insertNode(3);
    root->right->right=insertNode(2);   
  
    postorder(root);

    addChildSum(root);

    return 0;
}