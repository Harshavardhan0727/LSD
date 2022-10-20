//root class
#pragma once
class node{

public:

    //contains the base value, leaf flag, and the pointer to the children
    char base;
    bool leaf;
  
    node* A_child;
    node* C_child;
    node* G_child;
    node* T_child;

    //creates a default and a custom constructor
    node();
    node(char b, bool l);

};