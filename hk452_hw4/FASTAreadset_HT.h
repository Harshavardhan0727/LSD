#pragma once
#include <iostream>
struct tableNode{

    char* key;
    int location;
    tableNode* next;

};

class FASTAreadset_HT{

    int size;
    tableNode* table;
    tableNode** tails;
    tableNode** heads;
    int collisions;

public:

    FASTAreadset_HT(int);
    FASTAreadset_HT(int, std::string);

    unsigned int get_hash(char*, int display = 1);
    void insert(char*, int);

    tableNode* searchKey(char*, int display = 0);

    void display();

    ~FASTAreadset_HT();

};