#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
using namespace std;

struct FASTA_node{

    char read[50];
    FASTA_node * next;

};

class FASTAreadset_LL{

private:

    FASTA_node* head;
    long num_nodes;

public:

    //default constructor
    FASTAreadset_LL();

    //custom constructor
    FASTAreadset_LL(string hw_dataset);

    //read genome file
    void read_genome_file(string filename);

    //copy constructor
    FASTAreadset_LL(const FASTAreadset_LL& copy);

    //function to display linked list
    void display();

    //destructor
    ~FASTAreadset_LL();

    //search function
    FASTA_node* searchFragment(char frag[50]);

};