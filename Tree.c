//This code is for the main grouping function

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Initialize.h"

//This is the tree node structure
typedef struct node{
    float data;
    int nStudents;
    int studentIndex[1000];
    struct node* left;
	struct node* right;
}node;

//This is the circular linked list structure 
typedef struct group{
    int group;
    int gSize;
    int sIndex[1000];
    struct group* next;
}group;

//Priority queue
int rear = -1;
float pri[1000];
int Index[1000];

//Make root of tree a global variable
node* root = NULL;
//Make tail of circular linked list a global variable
group* tail = NULL;

//Group Making Function
void CreateGroup();

//Binary Tree Functions
void CreateTree();
node* createNode(int data);
node* insertLeft(node* parent, int data);
node* insertRight(node* parent, int data);
void InsertTree();
void preorder(node* rooT);
void TraverseTree(float j);

//Priority Queue Functions
void enqueue(float score, int index);
int dequeue();
int MaxPri();

//Circular Linked List Functions
void CreateCircle(int n);
void AddCircleNode(int n);

//This function is for creating groups of students
void CreateGroup(){

    int n;

    //Get the number of groups
    printf("Please insert number of groups: ");
    scanf("%d",&n);
    printf("\n");

    //Create the binary tree and add students to each quadrant 
    CreateTree();
    InsertTree();

    CreateCircle(n);    //Create the linked list

    //Create the nodes in linked list equal to the amount of groups
    for(int i=n-1;i>0;i--){

        AddCircleNode(i);

    }

    //Create a pointer for linked list and set it to the start 
    group* ptr =  tail->next;

    //Loop to add students from each tree quadrant and enqueue them into the priority queue and dequeue them into the linked list
    for(float j=0;j<1;j+=0.25){

        //Enqueuing students from tree quadrant to to queue
        TraverseTree(j);

        //Loop while queue is not empty
        while(rear!=-1){
            ptr->sIndex[ptr->gSize]=dequeue();  //Dequeue the student index from the priority queue into the group pointer
            //printf("%lld %s %d %.2f in group %d\n",student[ptr->sIndex[ptr->gSize]].ID, 
                //student[ptr->sIndex[ptr->gSize]].name, student[ptr->sIndex[ptr->gSize]].sec, student[ptr->sIndex[ptr->gSize]].score ,ptr->group);
            ptr->gSize++;       //Increase the group size in group pointer
            ptr = ptr->next;    //Move pointer to the next linked list node

        }

        //printf("\n");

    }

    printf("List of groups: \n");

    float avrg=0, total=0;
    ptr =  tail->next;      //set pointer to the start of linked list

    //Loop through the linked lists and print out the students in each group
    for(int i=0;i<n;i++){

        for(int j=0;j<ptr->gSize;j++){

            printf("%lld %-35s %10d %7.2f in group %d\n",student[ptr->sIndex[j]].ID, student[ptr->sIndex[j]].name, 
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

//This function is for creating the tree
void CreateTree(){

    float q1,q2,q3,j=0,data;
    
    //We will sort the scores into quartiles
    //so we must first find each quartile based on max score
    q1 = MaxScore*0.25;
    q2 = MaxScore*0.5;
    q3 = MaxScore*0.75;

    //Root of the tree will split the tree by half(50%)
    root = createNode(q2);
    node* Left = insertLeft(root, q1); 
    node* Right = insertRight(root, q3);

    //loop to create the required nodes in the binary tree, Dividing scores into quartiles(25% each, 4 nodes total)
    for(int i=0;i<4;i++){

        //Finding percentage of max score(0%,25%,50%,75%)
        data = MaxScore*j;

        //Set the temporary pointer to root position
        node* temp = root;
        node* parentPtr = NULL;

        //loop to find where to insert node
        while(temp!=NULL){

            //parentPtr will point to temporary pointer
            parentPtr=temp;
            
            //Temporary pointer goes left if data is less than temp->data
            if(data < temp->data){

                temp = temp->left;

            }else{
                //Temporary pointer goes right, data is more than temp->data
                temp = temp->right;

            }
        }

        //If data is less than parentPtr->data, insert new node to left
        if(data < parentPtr->data){

            insertLeft(parentPtr, data);

        }else{
            //data is more than parentPtr->data, insert new node to right
            insertRight(parentPtr, data);
        }

        //Increment j by 0.25 to find next percentage of max score
        j+=0.25;

    }

}

//This function is for creating tree nodes
node* createNode(int data){

    //Allocate memory for new node
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;    //Data will be used to determine quartile, basically the key
    newNode->nStudents = 0;  //Number of students in new node set to 0
    newNode->left = NULL;    //Set left of new node to NULL
    newNode->right = NULL;   //Set right of new node to NULL

    return newNode;

}

//This function is for inserting new nodes to the left
node* insertLeft(node* parent, int data){

    //Creating the new node
    node* ptr = createNode(data);
    parent->left = ptr; //Inserting node to left

    return parent->left;

}

//This function is for inserting new nodes to the right
node* insertRight(node* parent, int data){

    //Creating the new node
    node* ptr = createNode(data);
    parent->right = ptr; //Inserting node to right

    return parent->right;
    
}

//This function is for sorting students into each quadrant of the tree
void InsertTree(){

    //Loop through all the students
    for(int i=0;i<TotalStudents;i++){

        //Set temp node to root position
        node* temp = root;

        //Loop while the next node isn't NULL
        while(temp->left!=NULL){

            //temp pointer goes left if student score is less than temp->data
            if(student[i].score < temp->data){

                temp = temp->left;
                //printf("student %d, score %.2f to left\n",student[i].No ,student[i].score);

            }else{
                //temp pointer goes right if student score is more than temp->data
                temp = temp->right;
                //printf("student %d, score %.2f to right\n",student[i].No ,student[i].score);

            }

        }

        temp->studentIndex[temp->nStudents]=i;  //Index of the student is added to the student array in the temp node(temp node = quadrant)
        //printf("current student %d %s\n",student[temp->studentIndex[temp->nStudents]].No ,student[temp->studentIndex[temp->nStudents]].name );
        temp->nStudents = temp->nStudents+1;    //Increment the amount of students in the quadrant
        //printf("current students in qaurtile: %d\n",temp->nStudents);
        
    }
}

//This function is for adding all the students from a quadrant into the priority queue
void TraverseTree(float j){

    //Set temp node to root position
    node* temp = root;
    int data = MaxScore*j; //Finding score percentage

    //Loop while the next node isn't NULL
    while(temp->left!=NULL){
        
        //temp pointer goes left if data is less than temp->data
        if(data < temp->data){

            temp = temp->left;

        }else{
            //temp pointer goes right, data is more than temp->data
            temp = temp->right;

        }

    }

    //printf("No. of students %d\n", temp->nStudents);
    int size = temp->nStudents; //Setting the loop to the number of students in quadrant 

    for(int i=0;i<size;i++){

        //printf("%d %lld %s %d %.2f\n",student[temp->studentIndex[i]].No ,student[temp->studentIndex[i]].ID, student[temp->studentIndex[i]].name, student[temp->studentIndex[i]].sec, student[temp->studentIndex[i]].score);
        //Adding the student score and student index to the priority queue
        enqueue(student[temp->studentIndex[i]].score, temp->studentIndex[i]);
    }

    //printf("\n");

}

//This function is to check the binary tree
void preorder(node* rooT){
    if (rooT != NULL) {
        printf("%.2f ", rooT->data);
        printf("%d \n", rooT->nStudents);
        preorder(rooT->left);
        preorder(rooT->right);

    }
}

//This Function is for adding the student to the priority queue
void enqueue(float score, int index){

    //Return if queue is full
    if(rear==999){

        return;

    }else{
        rear++;                //increment rear
        pri[rear] = score;     //Set the priority to student score
        Index[rear] = index;   //Add index of student to queue
    }
}

//This function is for getting students out of queue, highest score goes out first
int dequeue(){

    //If queue is empty, return zero
    if(rear==-1){

        return 0;
    
    }else{
        
        int index = MaxPri();           //Find the index with max priority in queue
        int student = Index[index];     //Get the student with max priority

        //Remove the student from queue
        for(int i=index;i<rear;i++){

            Index[i] = Index[i+1];
            pri[i] = pri[i+1];

        }

        rear--;     //Decrement the rear

        //Returns the student with max priority
        return student;

    }   
}

//This function is for finding the index of max priority
int MaxPri(){

    int i, index;
    float maxPri=-1; //set maxPri to -1

    //If queue is empty, return zero
    if(rear==-1){

        return 0;

    }else{

        //Loop though the queue
        for(i=0;i<=rear;i++){

            //If maxPri < priority, set maxPri to priority and update index
            if(maxPri<pri[i]){

                maxPri = pri[i];
                index = i;

            }

        }

        return index;   //returns the insex with max priority
    }
}

//This function is for creating the circular linked list
void CreateCircle(int n){

    //Allocate memory for the new node
    group* newNode = (group*)malloc(sizeof(group));

    newNode->group = n;         //Add the group number
    newNode->gSize = 0;         //Set the group size to 0
    newNode->next = newNode;    //make the new node point to itself
    tail = newNode;             //Set the tail to new node

}

//This function is for adding new nodes of groups to the circular linked list
void AddCircleNode(int n){

    //Allocate memory for the new node
    group* newNode = (group*)malloc(sizeof(group));

    newNode->group = n;         //Add the group number
    newNode->gSize = 0;         //Set the group size to 0
    newNode->next = tail->next; //Make the new node point to the head of linked list
    tail->next = newNode;       //Make the tail point to new node

}

int main(){

    studentInformation();
    /*printf("q1 %d\n",root->left->left->nStudents);
    printf("q2 %d\n",root->left->right->nStudents);
    printf("q3 %d\n",root->right->left->nStudents);
    printf("q4 %d\n",root->right->right->nStudents);
    printf("q1 %.2f\n",root->left->left->data);
    printf("q2 %.2f\n",root->left->right->data);
    printf("q3 %.2f\n",root->right->left->data);
    printf("q4 %.2f\n",root->right->right->data);*/

    CreateGroup();

    /*for(int i=0;i<TotalStudents;i++){

        printf("%d %lld %s %d %.2f\n",student[i].No ,student[i].ID, student[i].name, student[i].sec, student[i].score);

    }

    printf("%.2f",MaxScore);*/

}
