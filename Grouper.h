#ifndef GROUPER_H
#define GROUPER_H

#include "Initialize.h"


typedef struct node{
    float data;
    int nStudents;
    int studentIndex[1000];
    struct node* left;
	struct node* right;
}node;

extern node* root;

void CreateGroup();
void DeleteTree(node* root);

#endif