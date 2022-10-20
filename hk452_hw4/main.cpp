#include "FASTAreadset_HT.h"
#include "BLAST_DB.h"

#include<iostream>
#include<string>
#include<fstream>
#include<ctime>
#include<cstring>

#define PERFECT 100

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

void part_1A(BLAST_DB &BDB, int num_queries){

    int found = 0;

    for(int i = 0; i < num_queries; i++){

        char query[51] = {0};
        int random_start = rand() % (sizeOfdataArray - 49);

        for(int j = 0; j < 50; j++){

            query[j] = dataArray[random_start + j];

        }

        struct best_hit best = BDB.search(query);

        if(best.score == PERFECT){ //it means found

            found++;

        }

    }

    cout << "Found hits: " << found << endl;


}

void part_1B(BLAST_DB &BDB, int num_queries){

    int found = 0;
    string opt = "ACGT";

    for(int i = 0; i < num_queries; i++){

        char query[51] = {0};
        int random_start = rand() % (sizeOfdataArray -49);

        for(int j = 0; j < 50; j++){

            if(rand() % 100 > 5)
                query[j] = dataArray[random_start + j];
            else
                query[j] = opt[rand() % 4];

        }

        struct best_hit best = BDB.search(query);

        //perfect match
        if(best.score == PERFECT){ //it means found

            found++;

        }

    }

    cout << "Found hits: " << found << endl;


}

void part_1C(BLAST_DB &BDB, char* filename, int num_queries){

    fstream filehandle;
    filehandle.open(filename, ios::in);

    if(filehandle.is_open()){

    }
    else{

        cout << "File not accessible. Either the location is invalid or the file is in use!";
        exit(-1);

    }

    string line;
    int found = 0;

    while(filehandle >> line && num_queries > 0){

        //get the second line
        if(filehandle >> line){

            char query[51] = {0};

            for(int i = 0; i < 50; i++){

                query[i] = line[i]; 

            }

            struct best_hit best = BDB.search(query);

            //perfect match
            if(best.score == PERFECT){ //it means found

                found++;

            }

        }

        num_queries--;

    }    

    cout << "Perfect matches: " << found << endl;

}

int main(int argc, char** argv){

    srand(time(0));

    //arg1 is part, arg2 is file path, arg 3 is number of queries
    if(argc < 3){

        cout << "Please specify the following arguments:\n";
        cout << "1) Part number to execute\n";
        cout << "2) File path for test_genome.fasta\n";
        cout << "3) Number of queries to generate\n";
        cout << "4) HW DATASET FILE\n";
        exit(0);

    }

    char *part = argv[1];
    string filename = argv[2];
    //BDB.display();

    int num_queries = 10000;
    
    if(argv[3])
        num_queries = atoi(argv[3]);

    //initialize data array
    init_dataArray(filename);

    if(strcmp(part, "A1") == 0){

        //create the object and load seeds
        BLAST_DB BDB(10000000, argv[2], false);
        BDB.store_seeds(11);
        part_1A(BDB,num_queries);

    }

    if(strcmp(part, "A2") == 0){

        //create the object and load seeds
        BLAST_DB BDB(10000000, argv[2], false);
        BDB.store_seeds(11);
        part_1B(BDB,num_queries);

    }

    if(strcmp(part, "A3") == 0){

        if(argc < 5)
        {
            
            cout << "Genome file not specified!\n";
            return 0;

        }
        //create the object and load seeds
        BLAST_DB BDB(10000000, argv[2], false);
        BDB.store_seeds(11);
        part_1C(BDB, argv[4], num_queries);

    }

    if(strcmp(part, "B") == 0){

        if(argc < 4)
        {
            
            cout << "Genome file not specified!\n";
            return 0;

        }
        //create the object and load seeds
        BLAST_DB BDB(10000000, argv[2], true);
        BDB.store_seeds(11);
        //displaying results for first 100 queries
        part_1C(BDB, argv[3], 100);

    }

    cout << "Finished!" << endl;
    return 0;

} 