#pragma once
#include "FASTAreadset_HT.h"

struct best_hit{

    int location;
    int score;

};

struct align{
		
	char seq1[100] = {0};
	char seq2[100] = {0};
	char rel[100] = {0};
	
};

class BLAST_DB{

    FASTAreadset_HT *HT;
    char *genome;
    int genome_size;
    int HT_Size;
    int ** matrix;
    bool disp;

public:

    BLAST_DB(int ht_size, char* filename, bool disp);
    ~BLAST_DB();

    char* load_genome(char* filename);
    void store_seeds(int size);
    int NeedleManWunsch(char* s1, char* s2, int wordsize = 11 );
    struct best_hit search(char* query);
    void display();
    struct align  get_optimal_alignment(char gen1[], char gen2[]);

};
