#include "FASTAreadset_LL.h"

//default constructor
FASTAreadset_LL::FASTAreadset_LL(){

    head = NULL;
    num_nodes = 0;

} 

//custom constructor
FASTAreadset_LL::FASTAreadset_LL(string hw_dataset){

    head = NULL;
    num_nodes = 0;

    fstream fileReader;
    fileReader.open(hw_dataset, ios::in);

    if(!fileReader.is_open()){

        cout << "Error opening High Throughput Sequence File! \n";
        exit(0);

    }

    string read;
    FASTA_node* temp;

    while(getline(fileReader, read)){

        if(read[0] != '>' && read[0] != '='){

            if(head == NULL){

                head = new FASTA_node;
                strcpy(head->read, read.c_str());
                head->next = NULL;
                temp = head;
                num_nodes++;

            }
            else{

                temp->next = new FASTA_node;
                temp = temp->next;
                strcpy(temp->read, read.c_str());
                temp->next = NULL;
                num_nodes++;

            }

        } 

    }
}


void FASTAreadset_LL::display(){

    FASTA_node* temp = head;

    while(temp)
    {

        cout << temp->read << endl;
        temp = temp->next;
        //sleep(1);

    }

}

void FASTAreadset_LL::read_genome_file(string filename){

    fstream fileReader;
    fileReader.open(filename, ios::in);

    if(!fileReader.is_open()){

        cout << "ERROR READING!" << endl;
        exit(-1);

    }

    string l;

    while(getline(fileReader, l))
        cout << l << endl;


}

//destructor
FASTAreadset_LL::~FASTAreadset_LL(){

    //destroy dynamically allocated memory
    FASTA_node* temp = NULL;
    
    if(head != NULL)
        temp = head;
    
    while( temp != NULL ) {
    
        FASTA_node* next = temp->next;
        delete temp;
        temp = next;
    
    }
    head = NULL;
}

//copy constructor
FASTAreadset_LL::FASTAreadset_LL(const FASTAreadset_LL& copy){

    if(copy.head == NULL)
    {
        head = NULL;
        num_nodes = 0;
        return;

    }

    head = new FASTA_node;
    strcpy(head->read, copy.head->read);
    num_nodes = copy.num_nodes;

    FASTA_node * copyTemp, *temp;
    copyTemp = copy.head;
    temp = head;

    while(copyTemp->next != NULL){

        temp->next = new FASTA_node;
        strcpy(temp->next->read, copyTemp->next->read); 
 
        temp = temp->next;
        copyTemp = copyTemp->next;

    }

    temp->next = NULL;

}

//search function
FASTA_node* FASTAreadset_LL::searchFragment(char frag[50]){

    FASTA_node* temp = NULL;

    if(head!=NULL)  
        temp = head;

    while(temp){

        if(strncmp(temp->read, frag, 50) == 0)
            return temp;

        temp = temp->next;
    }

    return NULL;

}
