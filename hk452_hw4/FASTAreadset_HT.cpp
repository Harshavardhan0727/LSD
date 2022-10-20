#include "FASTAreadset_HT.h"
#include<iostream>
#include<string>
#include<fstream>
#include<math.h>
#include<cstring>

#define RADIX 7 //13 bit radix

using namespace std;


FASTAreadset_HT::FASTAreadset_HT(int m){

    size = m;
    table = new tableNode[m];
    tails = new tableNode*[m];
    heads = new tableNode*[m];
    collisions = 0;

    for(int i = 0; i < m; i++){

        table[i].key = NULL;
        table[i].location = -1;
        table[i].next = NULL;
    }

}

FASTAreadset_HT::FASTAreadset_HT(int m, string filename){

    size = m;
    table = new tableNode[m];
    tails = new tableNode*[m];
    heads = new tableNode*[m];

    collisions = 0;

    for(int i = 0; i < m; i++){

        table[i].key = NULL;
        table[i].next = NULL;

    }

    fstream filereader;
    filereader.open(filename, ios::in);

    if(!filereader.is_open()){

        cout << "Unable to open " << filename << endl;
        cout << "Exiting.." << endl;
        exit(0);

    }

    string line;
    int initsize = 0;

    getline(filereader, line);

    while(filereader >> line){

        initsize += line.length();

    }

    char* dataArray = new char[initsize];

    filereader.close();

    filereader.open(filename, ios::in);

    if(!filereader.is_open()){

        cout << "Unable to open " << filename << endl;
        cout << "Exiting.." << endl;
        exit(0);

    }

    getline(filereader, line);

    int iterator = 0;

    while(filereader >> line){

        for(int i = 0; i < line.length(); i++){

            dataArray[iterator] = line[i];
            iterator++;

        }

    }

    cout << "Finished reading the file.." << endl;
    cout << "Now inserting to hashtable..." << endl;

    //now generating dataArray of size 11

    int totalPossible = initsize - 10;
    cout << "TOTAL POSSIBLE: " << initsize - 10 << endl;

    for(int i = 0; i < totalPossible; i++){

        char insertKey[11];

        for(int j = 0; j < 11; j++){

            insertKey[j] = dataArray[i+j];

        }

        insert(insertKey, i);
    
    }
    cout << "Collisions = " << collisions << endl;

}

unsigned int FASTAreadset_HT::get_hash(char* key, int display){

    //

    int radix_power = 0;
    unsigned int sum = 0;

    for(int i = 0; i < 11; i++){

        sum += int(key[i]) * pow(RADIX, radix_power);
        radix_power++;

    }

    if(display == 1)
    {
        cout << "Hash value = " << sum << endl;
        cout << "Hash value mod m = " << sum % size << endl;
    }

    return sum;

}

void FASTAreadset_HT::insert(char* key, int loc){

    unsigned int hash;

    hash = get_hash(key, 0);
    int index = hash % size;

    if(table[index].key == NULL){

        table[index].key = new char[11]; //length of a subfragment
        table[index].location = loc;
        strncpy(table[index].key, key, 11);
        tails[index] = &table[index];
        heads[index] = &table[index];
        table[index].next = NULL;

    }
    else{

        tails[index]->next = new tableNode;
        tails[index]->next->key = new char[11]; //length of a subfragment
        strncpy(tails[index]->next->key, key, 11);
        tails[index]->next->location = loc;
        tails[index] = tails[index]->next;
        tails[index]->next = NULL;
        collisions++;

    }

}

tableNode* FASTAreadset_HT::searchKey(char* key, int display){

    unsigned int hash;

    hash = get_hash(key, 0);
    int index = hash % size;

    if(table[index].key == NULL)
        return NULL;

    tableNode* temp = heads[index];
    tableNode* temphead = heads[index];
 
    while(temp){

        if(strncmp(temp->key, key, 11) == 0){

            if(display == 1)    
                cout << "found at index: " << index << endl;
    
            heads[index] = temphead;
            return temp;

        }

        temp = temp->next;
    }

    heads[index] = temphead;
    
    return NULL;

}


void FASTAreadset_HT::display(){

    for(int i = 0; i < size; i++){

        tableNode* temp = &table[i];

        if(temp->key)
            cout << "HT Index : " << i << endl;

        while(temp){

            if(temp->key)
                cout << "     " << temp->key << "   " << temp->location << endl;
            temp = temp->next;
        }

    }

    cout << "\nCollisions = " << collisions << endl;

}

FASTAreadset_HT::~FASTAreadset_HT(){

    for(int i = 0; i < size; i++){

        if(table[i].key == NULL)
            continue;

        tableNode* temp = heads[i]->next;

        while(temp){

            tableNode* temp0 = temp;
            temp = temp->next;
            delete temp0;

        }

    }

    delete [] heads;
    delete [] tails;
    delete [] table;

}
