//This code is for the main grouping function

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Initialize.h"

//This is the tree node structure

typedef struct node{
    float data;
    int nStudents;
    int studentIndex[100];
    struct node* left;
	struct node* right;
} node;

void CreateTree();
node* createNode(int data);
node* insertLeft(node* parent, int data);
node* insertRight(node* parent, int data);
void InsertTree();
void preorder(node* rooT);

//Make root of tree a global variable
node* root = NULL;
//This function is for creating the tree
void CreateTree(){

    float q1,q2,q3,j=0,data;
    
    //We will sort the scores into quartiles
    //,so we must first find each quartile based on max score
    q1 = MaxScore*0.25;
    q2 = MaxScore*0.5;
    q3 = MaxScore*0.75;

    //Root of the tree will split the tree by half(50%)
    root = createNode(q2);
    node* Left = insertLeft(root, q1);
    node* Right = insertRight(root, q3);

    for(int i=0;i<4;i++){

        data = MaxScore*j;

        node* temp = root;
        node* parentPtr = NULL;

        while(temp!=NULL){

            parentPtr=temp;
            
            if(data < temp->data){

                temp = temp->left;

            }else{

                temp = temp->right;

            }
        }

        if(data < parentPtr->data){

            insertLeft(parentPtr, data);

        }else{

            insertRight(parentPtr, data);
        }

        j+=0.25;

    }

}

//This function is for creating tree nodes
node* createNode(int data){

    node* newNode = (node*)malloc(sizeof(node*));
    newNode->data = data;
    newNode->nStudents = 0;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;

}

node* insertLeft(node* parent, int data){

    node* ptr = createNode(data);
    parent->left = ptr;

    return parent->left;

}

node* insertRight(node* parent, int data){

    node* ptr = createNode(data);
    parent->right = ptr;

    return parent->right;
    
}

void InsertTree(){

    for(int i=0;i<TotalStudents;i++){

        node* temp = root;
        int loop=0;

        while(loop<2){

            if(student[i].score < temp->data){

                temp = temp->left;
                printf("student %d, score %.2f to left\n",student[i].No ,student[i].score);

            }else{

                temp = temp->right;
                printf("student %d, score %.2f to right\n",student[i].No ,student[i].score);

            }

            loop++;

        }

        temp->nStudents = temp->nStudents+1;
        printf("current students in qaurtile: %d\n",temp->nStudents);

    }
}

void preorder(node* rooT){
    if (rooT != NULL) {
        printf("%.2f ", rooT->data);
        printf("%d \n", rooT->nStudents);
        preorder(rooT->left);
        preorder(rooT->right);

    }
}

int main(){

    studentInformation();

    CreateTree();

    /*printf("q1 %d\n",root->left->left->nStudents);
    printf("q2 %d\n",root->left->right->nStudents);
    printf("q3 %d\n",root->right->left->nStudents);
    printf("q4 %d\n",root->right->right->nStudents);
    printf("q1 %.2f\n",root->left->left->data);
    printf("q2 %.2f\n",root->left->right->data);
    printf("q3 %.2f\n",root->right->left->data);
    printf("q4 %.2f\n",root->right->right->data);*/

    InsertTree();
    preorder(root);
    /*for(int i=0;i<TotalStudents;i++){

        printf("%d %lld %s %d %.2f\n",student[i].No ,student[i].ID, student[i].name, student[i].sec, student[i].score);

    }

    printf("%.2f",MaxScore);*/

}
