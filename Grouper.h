#ifndef Grouper_H
#define Grouper_H

#include "Initialize.h"

//This is the tree node structure
typedef struct node{
    float data;
    int nStudents;
    int studentIndex[1000];
    struct node* left;
	struct node* right;
}node;

node* root = NULL;

void CreateGroup();
void DeleteTree(node* root);

#endif