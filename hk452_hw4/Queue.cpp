#pragma once
#include <iostream>
using namespace std;

struct Qnode{

    int location;
    char seed[11];
    Qnode* next;

};

class Queue{

    Qnode *head;

public:

    Queue(){

        head = NULL;

    }

    void insert(int location, char* seed = NULL){

        if(head == NULL){

            head = new Qnode;
            head->location = location;
            head->next = NULL;
            //strncpy(head->seed, seed, 11);
            return;

        }

        Qnode* temp = head;
        while(temp->next){

            temp = temp->next;

        }

        temp->next = new Qnode;
        temp = temp->next;
        temp->location = location;
        temp->next = NULL;
        //strncpy(temp->seed, seed, 11);

    }

    Qnode pop(){

        if(head == NULL)
            return Qnode();

        Qnode* hptr = head;
        Qnode temp;
        temp.location = head->location;
        strncpy(temp.seed, head->seed, 11);
        head = head->next;
        delete hptr;
        return temp;

    }

    bool isEmpty(){

        return head == NULL;

    }

};