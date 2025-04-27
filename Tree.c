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
}node;

//This is the circular linked list structure 
typedef struct group{
    int group;
    int gSize;
    int sIndex[100];
    struct group* next;
}group;

void CreateTree();
node* createNode(int data);
node* insertLeft(node* parent, int data);
node* insertRight(node* parent, int data);
void InsertTree();
void preorder(node* rooT);
void TraverseTree(float j);
void enqueue(float score, int index);
int MaxPri();
void CreateGroup();
void CreateCircle(int n);
int dequeue();
void AddCircleNode(int n);



//Priority queue
int rear = -1;
float pri[100];
int Index[100];

//Make root of tree a global variable
node* root = NULL;

group* tail = NULL;

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

    node* newNode = (node*)malloc(sizeof(node));
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

        while(temp->left!=NULL){

            if(student[i].score < temp->data){

                temp = temp->left;
                //printf("student %d, score %.2f to left\n",student[i].No ,student[i].score);

            }else{

                temp = temp->right;
                //printf("student %d, score %.2f to right\n",student[i].No ,student[i].score);

            }

        }

        temp->studentIndex[temp->nStudents]=i;
        //printf("current student %d %s\n",student[temp->studentIndex[temp->nStudents]].No ,student[temp->studentIndex[temp->nStudents]].name );
        temp->nStudents = temp->nStudents+1;
        //printf("current students in qaurtile: %d\n",temp->nStudents);
        
    }
}

void TraverseTree(float j){

    node* temp = root;
    int data = MaxScore*j;

    while(temp->left!=NULL){
            
        if(data < temp->data){

            temp = temp->left;

        }else{

            temp = temp->right;

        }

    }

    //printf("No. of students %d\n", temp->nStudents);
    int size = temp->nStudents;

    for(int i=0;i<size;i++){

        //printf("%d %lld %s %d %.2f\n",student[temp->studentIndex[i]].No ,student[temp->studentIndex[i]].ID, student[temp->studentIndex[i]].name, student[temp->studentIndex[i]].sec, student[temp->studentIndex[i]].score);
            
        enqueue(student[temp->studentIndex[i]].score, temp->studentIndex[i]);
    }

    //printf("\n");

}

void enqueue(float score, int index){

    if(rear==99){

        return;

    }else{
        rear++;

        pri[rear] = score;
        Index[rear] = index;

    }
}

int dequeue(){

    if(rear==-1){

        return 0;
    
    }else{
    
        int index = MaxPri();
        int student = Index[index];

        for(int i=index;i<rear;i++){

            Index[i] = Index[i+1];
            pri[i] = pri[i+1];

        }

        rear--;

        return student;

    }   
}

int MaxPri(){

    int i, index;
    float maxPri=-1;

    if(rear==-1){

        return 0;

    }else{

        for(i=0;i<=rear;i++){

            if(maxPri<pri[i]){

                maxPri = pri[i];
                index = i;

            }

        }

        return index;
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

void CreateGroup(){

    int n;

    printf("Please insert number of groups: ");
    scanf("%d",&n);
    printf("\n");

    CreateCircle(n);

    for(int i=n-1;i>0;i--){

        AddCircleNode(i);

    }

    group* check =  tail->next;

    for(int i=0;i<4;i++){

    }
    
    group* ptr =  tail->next;
    for(float j=0;j<1;j+=0.25){

        TraverseTree(j);

        while(rear!=-1){
            ptr->sIndex[ptr->gSize]=dequeue();

            //printf("%lld %s %d %.2f in group %d\n",student[ptr->sIndex[ptr->gSize]].ID, 
                //student[ptr->sIndex[ptr->gSize]].name, student[ptr->sIndex[ptr->gSize]].sec, student[ptr->sIndex[ptr->gSize]].score ,ptr->group);
            ptr->gSize++;
            ptr = ptr->next;

        }

        //printf("\n");

    }

    printf("List of groups: \n");


    float avrg=0, total=0;
    ptr =  tail->next;
    for(int i=0;i<n;i++){

        for(int j=0;j<ptr->gSize;j++){

            printf("%lld %s %d %.2f in group %d\n",student[ptr->sIndex[j]].ID, student[ptr->sIndex[j]].name, 
                    student[ptr->sIndex[j]].sec, student[ptr->sIndex[j]].score ,ptr->group);
                    total++;
                    avrg=avrg+student[ptr->sIndex[j]].score;

        }

        avrg=avrg/total;
        printf("Average = %.2f\n",avrg);
        ptr=ptr->next;

        printf("\n");

    }

}

void CreateCircle(int n){

    group* newNode = (group*)malloc(sizeof(group));

    newNode->group = n;
    newNode->gSize = 0;
    newNode->next = newNode;
    tail = newNode;

}

void AddCircleNode(int n){

    group* newNode = (group*)malloc(sizeof(group));

    newNode->group = n;
    newNode->gSize = 0;
    newNode->next = tail->next;
    tail->next = newNode;

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

    CreateGroup();

    
    /*for(int i=0;i<TotalStudents;i++){

        printf("%d %lld %s %d %.2f\n",student[i].No ,student[i].ID, student[i].name, student[i].sec, student[i].score);

    }

    printf("%.2f",MaxScore);*/

}
