//This code is for the main grouping function

#include "Grouper.h"

//This is the circular linked list structure 
typedef struct group{
    int group;
    int gSize;
    int sIndex[1000];
    struct group* next;
    struct group* prev;
}group;

//Priority queue
int rear = -1;
float pri[1000];
int Index[1000];

//Make tail of circular linked list a global variable
group* head = NULL;

//Group Making Function
void GroupFile(int n);

//Binary Tree Functions
void CreateTree();
node* createNode(int data);
node* insertLeft(node* parent, int data);
node* insertRight(node* parent, int data);
void InsertTree();
void TraverseTree(float j);

//Priority Queue Functions
void enqueue(float score, int index);
int dequeue();
int MaxPri();

//Circular Linked List Functions
void CreateList(int n);
void AddListNode(int n);
void DeleteList(group* ptr);

//This function is for creating groups of students
void CreateGroup(){

    int n, loop=0, choice, valid=1;

    //Let user select how to make groups
    while(valid){
        printf("\n<-------How would you like to create your groups?------->\n");
        printf("     -Enter total number of groups      : Enter 1\n     -Enter number of students per group: Enter 2\n");
        printf(">>Please select your option: ");
        scanf("%d",&choice);

        if(choice==1 || choice==2){
            break;
        }else{
            printf("\n<<-------------Please enter a valid option!------------>>\n");
        }
    }

    valid=1;
    //Get the number of groups, loop if invalid
    while(valid){

        if(choice==1){
            printf(">>Please insert number of groups: ");
            scanf("%d",&n);

            //loop if invalid
            if(n > TotalStudents || n < 1){
                printf("\n<<---------Please enter a valid number!--------->>\n");
            }else{
                break;
            }

        }else if(choice==2){
            printf(">>Please insert number of students per group: ");
            scanf("%d",&n);

            n = TotalStudents/n; //find number of groups

            //loop if invalid
            if(n > TotalStudents || n < 1){
                printf("\n<<---------Please enter a valid number!--------->>\n");
            }else{
                break;
            }

        }else{
            printf("\n<<---------Please enter valid option!--------->>\n");
        }
    }

    //Create the binary tree and add students to each quadrant 
    if(root==NULL){
        CreateTree();
        InsertTree();
    }

    CreateList(n);    //Create the linked list

    //Create the nodes in linked list equal to the amount of groups
    for(int i=n-1;i>0;i--){

        AddListNode(i);

    }

    //Create a pointer for linked list and set it to the start 
    group* ptr =  head;

    //Loop to add students from each tree quadrant and enqueue them into the priority queue and dequeue them into the linked list
    for(float j=0.75;j>-0.25;j-=0.25){

        //Enqueuing students from tree quadrant to to queue
        TraverseTree(j);
        
        //Loop while queue is not empty
        while(rear!=-1){
            ptr->sIndex[ptr->gSize]=dequeue();  //Dequeue the student index from the priority queue into the group pointer
            ptr->gSize++;       //Increase the group size in group pointer

            //Loop back and forth in the doubly linked-list
            if(loop<n){
                if(ptr->next==NULL){
                    loop++;
                    continue;
                }
                ptr = ptr->next;
                loop++;
            }else{
                if(ptr->prev==NULL){
                    loop=0;
                    continue;
                }
                ptr = ptr->prev;
                loop++;
            }

        }

    }

    printf("\n<--------------GROUPS CREATED SUCCESSFULLY--------------->\n");

    ptr =  head;      //set pointer to the start of linked list

    //Loop through the linked lists and print out the students in each group
    for(int i=0;i<n;i++){
        
        printf(" ________________________________________________________ \n");
        printf("|                       GROUP %3d                        |\n",ptr->group);
        printf("|________________________________________________________|\n");
        printf("| STUDENT ID |      STUDENT NAME       | SECTION | SCORE |\n");
        printf("|____________|_________________________|_________|_______|\n");


        for(int j=0;j<ptr->gSize;j++){

            printf("| %lld  %-22s %7d %10.2f |\n",student[ptr->sIndex[j]].ID, student[ptr->sIndex[j]].name, 
                    student[ptr->sIndex[j]].sec, student[ptr->sIndex[j]].score);

        }

        printf("|________________________________________________________|\n");
        printf("| Total students in group:                        %3d    |\n",ptr->gSize);
        printf("|________________________________________________________|\n");

        ptr=ptr->next;

    }

    valid=1;
    //Let user select to create group file, if invalid, loop
    while(valid){

        //Get selction
        printf("\n<------Would you like to save groups as excel file?------>\n");
        printf("     -Yes: Enter 1\n     -No : Enter 2\n");
        printf(">>Please select your option: ");
        scanf("%d",&choice);
        getchar();

        if(choice==1){
            GroupFile(n);   //Create the group file
            break;
        }else if(choice==2){
            printf("\n<<---------------------No file made--------------------->>\n\n");
            break;
        }else{
            printf("\n<<--------------Please enter valid option!-------------->>\n");
        }
    }

    //empty the doubly linked-list
    DeleteList(head);

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
                //printf("student %d, score %.2f to left\n",student[i].No ,student[i].score); //test to see which brabch it's going to

            }else{
                //temp pointer goes right if student score is more than temp->data
                temp = temp->right;
                //printf("student %d, score %.2f to right\n",student[i].No ,student[i].score); //test to see which brabch it's going to

            }

        }

        temp->studentIndex[temp->nStudents]=i;  //Index of the student is added to the student array in the temp node(temp node = quadrant)
        temp->nStudents = temp->nStudents+1;    //Increment the amount of students in the quadrant
        
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

    int size = temp->nStudents; //Setting the loop to the number of students in quadrant 

    for(int i=0;i<size;i++){

        //Adding the student score and student index to the priority queue
        enqueue(student[temp->studentIndex[i]].score, temp->studentIndex[i]);
    }

}

//This function is for deleting the tree
void DeleteTree(node* root){
       if(root->left){
             DeleteTree(root->left);
             free(root->left);
       }
       if(root->right){
             DeleteTree(root->right);
             free(root->right);
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
void CreateList(int n){

    //Allocate memory for the new node
    group* newNode = (group*)malloc(sizeof(group));

    newNode->group = n;         //Add the group number
    newNode->gSize = 0;         //Set the group size to 0
    newNode->next = NULL;       //make the next node point to NULL
    newNode->prev = NULL;       //make the prevoius node point to NULL
    head = newNode;             //Set the head to new node

}

//This function is for adding new nodes of groups to the circular linked list
void AddListNode(int n){

    //Allocate memory for the new node
    group* newNode = (group*)malloc(sizeof(group));

    newNode->group = n;         //Add the group number
    newNode->gSize = 0;         //Set the group size to 0
    newNode->next = head;       //Make the new node point to the head of linked list
    head->prev = newNode;       //Make the head point to new node
    newNode->prev = NULL;       //make the prevoius node point to NULL
    head = newNode;             //Set the head to new node

}

//function to delete linked-list
void DeleteList(group* ptr){

    //retrun when empty
    if(ptr==NULL){
        return;
    }

    DeleteList(ptr->next);
    free(ptr);
}

void GroupFile(int n){

    //update the products file
    FILE *file = fopen("GroupSheet.csv","w");

    //check if file exists
    if (file == NULL){
        printf("Error: Unable to open GroupSheet file.\n");
        return;
    }

    //Set pointer to start of linked list
    group* ptr = head;
    //print out the new information
    fprintf(file,"Group No.,Students ID,Student Name,Section,Score\n");
    for (int i=0;i<n;i++){
        for(int j=0;j<ptr->gSize;j++){
            fprintf(file,"%d,%lld,%s,%d,%.2f\n",ptr->group ,student[ptr->sIndex[j]].ID, 
                    student[ptr->sIndex[j]].name ,student[ptr->sIndex[j]].sec ,
                    student[ptr->sIndex[j]].score);
        }

        ptr = ptr->next;
    }

    fclose(file);

    printf("\n<<-----Group Sheet successully created!----->>\n\n");
}

//For testing
int main(){

    studentInformation();
    CreateGroup();

}
