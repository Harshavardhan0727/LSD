#include "Implementations.h"
#include "prefix_trie.h"
using namespace std;

int main(int argc, char** argv){

    //check for the command line arguments
    if(argc < 3){

        cout << "Usage: ./main 1 sars_genome.fasta 5000" << endl;
        exit(0);

    }

    //seed the random number generator
    srand(time(0));

    //extract the command line arguments
    int part = atoi(argv[1]); //part number to execute, 1/2
    char* file_name = argv[2]; //file containing the sars genome
    int n = atoi(argv[3]); //n, size of the set of queries used to populate the trie 

    //read and store the sars genome
    char* sars_genome = read_genome_file(file_name);
    
    //part A
    if(part == 1){

        //set the error type to no error and create the trie
        char type[] = "without_error";

        //create the trie with the genome, set_size, and type (error/no error)
        prefix_trie trie(sars_genome, n, type);

        //call the copy constructor
        prefix_trie trie2 = trie;

        //now search
        cout << "Matched = " << search(trie, sars_genome) << " queries!" << endl;

    }

    if(part == 2){

        //set the type to error
        char type[] = "error";
        
        //create the trie with the genome, set_size, and type (error/no error)
        prefix_trie trie(sars_genome, n, type);
        
        //call the copy constructor
        prefix_trie trie2 = trie;
        
        //now search
        cout << "Matched = " << search(trie, sars_genome) << " queries!" << endl;
        
    }
    return 0;

}