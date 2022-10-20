#include "FASTAreadset_HT.h"
#include<iostream>
#include<string>
#include<fstream>
#include<ctime>
#define ONEMILLION 1000000

using namespace std;

char* dataArray = NULL;
int sizeOfdataArray = 0;

void init_dataArray(string filename){
    
    if(dataArray == NULL){

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

        dataArray = new char[initsize];
        sizeOfdataArray = initsize;

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

    }
}

void get_random_16mer_from_array(char dataArray[], int size, char arr[]){

    int index = rand() % (size - 15);

    for(int i = 0; i < 16; i++){

        arr[i] = dataArray[index + i];

    }

}

void get_completely_random_16mers(char arr[]){

    char ACGT[] = {'A', 'C', 'G', 'T'};

    for(int i = 0; i < 16; i++){

        arr[i] = ACGT[rand()%4];
    
    }

}

void get_iterative_16mer(int startIndex, char arr[]){

    for(int i = 0; i < 16; i++){

        arr[i] = dataArray[startIndex + i];

    }    

}

void get_16mers_with_error(int startIndex, char arr[]){

    char ACGT[] = {'A', 'C', 'G', 'T'};

    for(int i = 0; i < 16; i++){

        arr[i] = dataArray[startIndex + i];
        
        if(rand() % 101 == 1) //1%
            arr[i] = ACGT[rand()%4];

    }

}

int main(int argc, char** argv){

    if(argc < 3){

        cout << "Please specify the following arguments:\n";
        cout << "1) Part number to execute\n";
        cout << "2) File path for test_genome.fasta\n";
        cout << "3) Size of hashtable to use\n";
        exit(0);

    }

    char part = argv[1][0];

    if(part == 'A' && argc < 4){

        cout << "Please specify Size of hashtable to use\n";
        return 0; //need to pass hash table size

    }

    string filename = argv[2];
    int hashTableSize;
// executing the part A for collisions with respective hash tabel size

    if (part == 'A'){

        hashTableSize = atoi(argv[3]);

        //customized constructor that takes the size of hashtable and filename to populate the hash table with all possible 16-mers
        FASTAreadset_HT *HT = new FASTAreadset_HT(hashTableSize, filename);

        //to display the whole table
        //HT->display();

        //call the destructor
        delete HT;
    
    }
// executing the part B for searching with random and completly ramdom.

    if(part == 'B'){

        srand(time(0));

        //customized constructor that takes the size of hashtable and filename to populate the hash table with all possible 16-mers
        FASTAreadset_HT *HT = new FASTAreadset_HT(ONEMILLION, filename);
        char query[17] = {0};
        int found = 0;

        init_dataArray(filename);

        cout << "\nSearching with random 16-mers from the given genome file..\n";

        for(int i = 0; i < ONEMILLION; i++){

            get_random_16mer_from_array(dataArray, sizeOfdataArray, query);
            found += HT->searchKey(query);

        }

        cout << "\nSearches matched = " << found << endl;

        cout << "\nNow searching with completely random 16-mers..\n\n";

        found = 0;

        for(int i = 0; i < ONEMILLION; i++){

            get_completely_random_16mers(query);
            found += HT->searchKey(query);

        }

        cout << "\nSearches matched = " << found << endl;

        delete HT;

    }

// executing the part C for search function with 1% error rate 

    if(part == 'C'){

        srand(time(0));

        FASTAreadset_HT *HT = new FASTAreadset_HT(ONEMILLION * 10, filename);
        char query[17] = {0};
        int found = 0;

        init_dataArray(filename);

        cout << "\nSearching with 16-mers from the given genome file..\n";

        for(int i = 0; i < sizeOfdataArray - 15; i++){

            get_iterative_16mer(i, query);
            found += HT->searchKey(query);

        }

        cout << "\nSearches matched = " << found << endl;

        cout << "\nNow searching 16-mers with 1\% error rate..\n\n";

        found = 0;

        for(int i = 0; i < sizeOfdataArray - 15; i++){

            get_16mers_with_error(i, query);
            found += HT->searchKey(query);

        }

        cout << "\nSearches matched = " << found << endl;

        delete HT;

    }

    cout << "\nProgram executed correctly!" << endl;
    return 0;

} 