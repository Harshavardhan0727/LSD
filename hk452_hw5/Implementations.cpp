#include "Implementations.h"
using namespace std;

//read in the genome file
char* read_genome_file(char* filename){

    fstream file;
    file.open(filename, ios::in);

    if(!file.is_open()){

        cout << "Could not open \"" << filename << "\"\n";
        exit(0);  
    }

    string buffer;

    int size = 0;
    int c = 0;

    //loop to read lines from file into buffer
    while(getline(file, buffer)){

        //skip if the line is a header
        if(buffer[0] == '>')
            continue;

        for(int i = 0; buffer[i] != '\0'; i++)
           size++;

    }

    file.close();
    file.open(filename, ios::in);

    cout << "Characters in genome: " << size << endl;

    char *genome = new char[size + 1];
    genome[size] = '\0';

    while(getline(file, buffer)){

        //skip if the line is a header
        if(buffer[0] == '>')
            continue;

        for(int i = 0; buffer[i] != '\0'; i++)
            genome[c++] = buffer[i];

    }

   //cout << "Genome: " << genome << endl;

    return genome;

}

//search for all the possible 36mers in the trie
int search(prefix_trie& trie, char* genome){

    int counter = 0;

    int max = 29903-35;
    char query[37];
    query[36] = '\0'; 

    for(int i = 0; i < max; i++){

        for(int j = 0; j < 36; j++){

            query[j] = genome[i+j];

        }

        if(trie.fuzzy_search(query, 0, trie.root) == true)
            counter++;

    }

    return counter;

}