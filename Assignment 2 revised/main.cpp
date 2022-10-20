#include "FASTAreadset_LL.h"
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main(int argc, char** argv){

    //check for cmd arguments
    if(argc < 4){

        cout << "Expected at least 4 arguments!\n\n";
        cout << "./run partA hw_dataset.fa test_genome.fasta 1000\n\n";
    
        //arg1 is part num
        //arg2 is filename1
        //arg3 is filename 2
        //arg4 is optional number of queries        
        exit(0);

    }

    FASTAreadset_LL obj(argv[2]);

    if(strstr(argv[1], "A")){

    //    FASTAreadset_LL obj2 = obj;
    //    FASTAreadset_LL obj3 = obj2;
        
        cout << "NODE FOUND AT: " << obj.searchFragment("CTAGGTACATCCACACACAGCAGCGCATTATGTATTTATTGGATTTATTT") << endl;
        cout << "NODE FOUND AT: " << obj.searchFragment("GCGCGATCAGCTTCGCGCGCACCGCGAGCGCCGATTGCACGAAATGGCGC") << endl;
        cout << "NODE FOUND AT: " << obj.searchFragment("CGATGATCAGGGGCGTTGCGTAATAGAAACTGCGAAGCCGCTCTATCGCC") << endl;
        cout << "NODE FOUND AT: " << obj.searchFragment("CGTTGGGAGTGCTTGGTTTAGCGCAAATGAGTTTTCGAGGCTATCAAAAA") << endl;
        cout << "NODE FOUND AT: " << obj.searchFragment("ACTGTAGAAGAAAAAAGTGAGGCTGCTCTTTTACAAGAAAAAGTNNNNNN") << endl;
        
    }

    if(strstr(argv[1], "B")){

        fstream fileReader;
        fileReader.open(argv[3], ios::in);

        if(!fileReader.is_open())
        {

            cout << "error opening file!";
            exit(-1);

        }

        string l;
        int exactLength = 0;

        getline(fileReader, l); //discard the tag line

        while(fileReader >> l)
            exactLength += l.length();

        cout << "EXACT LENGTH IS: " << exactLength << endl;

        char * charArray = new char[exactLength];

        fileReader.clear();
        fileReader.seekg(0, ios::beg);

        getline(fileReader, l); //discard the tag line

        int index = 0;

        while(fileReader >> l){
        
            for(int i = 0; i < l.length(); i++){

                if(l[i] == '\0')
                    cout << "NULL FOUND" << endl;

                charArray[index + i] = l[i];

            }
    
            index += l.length();
    
        }
    
        //now creating 50 char long fragments by shifting start position and checking

        int sp;
        int overlap = 0;

        int queries = exactLength - 49;

        if(argc > 4){

            if(atoi(argv[4]) <= queries)
                queries = atoi(argv[4]);

        }

        auto timerstart = high_resolution_clock::now();

        for(sp = 0; sp < queries; sp++){

            char searchFor[51] = {0};

            for(int i = 0; i < 50; i++)
                searchFor[i] = charArray[i+sp];

            if(obj.searchFragment(searchFor) != NULL){

                overlap++;

            }

        }

        auto timerstop = high_resolution_clock::now();

        cout << "\nSubfragments made = " << sp << endl;
        cout << "Overlap = " << overlap << endl;
        cout << "Time taken: " << duration_cast<seconds>(timerstop - timerstart).count() << " seconds" << endl;

    }

}