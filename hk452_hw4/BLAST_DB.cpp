#include <iostream>
#include <fstream>
#include <cstring>
#include <stack>

#include "BLAST_DB.h"
#include "Queue.cpp"

using namespace std;

void store(stack<char> &st, char A){
	
	st.push(A);
	
}

char retrieve(stack<char> &st){
	
	char ret = st.top();
	st.pop();
	return ret;
	
}

BLAST_DB::BLAST_DB(int ht_size, char* filename, bool disp){

    this->disp = disp;
    HT_Size = ht_size;
    HT = new FASTAreadset_HT(HT_Size);
    genome = NULL;
    genome = load_genome(filename);

    matrix = new int*[2500];
    
    for(int i = 0; i < 2500; i++)
        matrix[i] = new int[2500];

}

char* BLAST_DB::load_genome(char *filename){

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

    genome = new char[initsize];

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

            genome[iterator] = line[i];
            iterator++;

        }

    }

    genome_size = initsize;
    return genome;

}

void BLAST_DB::store_seeds(int size = 11){

    for(int i = 0; i < genome_size - 50; i++){

        char ins[12] = {0};

        for(int j = 0; j < 11; j++){

            ins[j] = genome[i+j];

        }

        HT->insert(ins, i); //store seed and its location

    }

}

BLAST_DB::~BLAST_DB(){

    if(genome)      
        delete [] genome;

    if (HT)
        delete HT; //calls specific destrcutor for HT


}

void BLAST_DB::display(){

    if(HT)  
        HT->display();

}

int BLAST_DB::NeedleManWunsch(char* gen1, char* gen2, int wordsize){

	int genome_length = 50;

	int match_score = 2;
	int mismatch_penalty = -1;
	int gap_penalty = -1;
	int score = 0;

    for (int i=0;i<=genome_length;i++){
	
		matrix[i][0] = matrix[0][i] = i * gap_penalty;
    
	}

	for (int i=1;i<=genome_length;i++)
    {
        for (int j=1;j<=genome_length;j++)
        {
        	
            if(gen1[i-1] == gen2[j-1])
			{
			
				score = match_score;	
				
			}
			else{
				
				score = mismatch_penalty;
				
			}
			
            matrix[i][j] = max(matrix[i-1][j-1] + score, max(matrix[i-1][j] + gap_penalty, matrix[i][j-1] + gap_penalty));
        
		}
    }
    
    return matrix[genome_length][genome_length];


}

struct align BLAST_DB::get_optimal_alignment(char gen1[], char gen2[])
{    

	int genome_length = 50;
	char dash = '_';

	int match_score = 2;
	int mismatch_penalty = -1;
	int gap_penalty = -1;
	
	struct align ret;
    
	stack<char> seq1, seq2;
    
	int i = genome_length; 
	int j = genome_length;
    
    while (!(i == 0 && j == 0))
    {
        if (i == 0)
        {
            store(seq1, dash);//seq1.push(dash);
            store(seq2, gen2[j--]);//seq2.push(B[j--]);
            
        }
        
        else if (j == 0)
        {
            store(seq1, gen1[i--]);//seq1.push(A[i--]);
            store(seq2, dash);//seq2.push(dash);
        }
        else
        {
            int score;
			if (gen1[i-1] == gen2[j-1]){
				
				score = match_score;
				
			}
			else{
				
				score = mismatch_penalty;
			} 
			
            if (matrix[i][j] == matrix[i-1][j-1] + score)
            {
                store(seq1, gen1[i-1]);//seq1.push(A[i-1]);
                store(seq2, gen2[j-1]);//seq2.push(B[j-1]);
                i--; j--;
            }
            else if (matrix[i-1][j] > matrix[i][j-1])
            {
                store(seq1, gen1[i--]);//seq1.push(A[i--]);
                store(seq2, dash);//seq2.push(dash);
            }
            else
            {
                store(seq1, dash);//seq1.push(dash);
                store(seq2, gen2[j--]);//seq2.push(B[j--]);
            }
        }
    }
    
    int s1I = 0, s2I = 0;
    
    for (;!seq1.empty();)
    {
        ret.seq1[s1I] = retrieve(seq1);
        
        ret.seq2[s2I] = retrieve(seq2);

		if(ret.seq1[s1I] == ret.seq2[s2I]){
			
			ret.rel[s1I] = '|';
			
		}
		else if(ret.seq1[s1I] != dash && ret.seq2[s2I] != dash){
			
			ret.rel[s1I] = 'X';
			
		}
		else{
			
			ret.rel[s1I] = ' ';
			
		}

		s1I++;
		s2I++;

    }	

    cout << endl;
	cout << ret.seq1 << endl;
	cout << ret.rel << endl;
	cout << ret.seq2 << endl;
    cout << endl;

	return ret;

}


struct best_hit BLAST_DB::search(char *query){ //searches a given query and returns match score

    struct best_hit bestHit;
    bestHit.score = 0;

    int possible_seeds = 50-10;
    Queue Q;

    //disassemble into all possible 11-mers and search each

    for(int i = 0; i < possible_seeds; i++){

        char seed[12] = {0};

        for(int j = 0; j < 11; j++){

            seed[j] = query[i+j];

        }

        //search the seed in the hashtable //if found, add to Queue
        tableNode* found = HT->searchKey(seed); //the search function of hashtable returns the location..
        //the location of the starting index of matching seed
        //-1 if not found

        if(found != NULL){
            
            while(found){
            
                Q.insert(found->location); //insert seed and its starting location in the original genome   
                found = found->next;

            }
        }

    }

    //now get each seed from the queue, expand it to 50mer, and apply Needleman
    while(!Q.isEmpty()){

        int location = (Q.pop()).location;
        char expanded[51] = {0};

        //fetch 50 characters from the location, and match with out query
        for(int i = 0; i < 50; i++){

            expanded[i] = genome[location + i];

        }

        int score = NeedleManWunsch(query, expanded);

        if(score == 100){ //no need to check the rest

            bestHit.score = score;
            bestHit.location = location;
    
            if(disp == true)
                get_optimal_alignment(query, expanded);

            return bestHit;

        }

        //update best hit
        if(score > bestHit.score){

            bestHit.score = score;
            bestHit.location = location;
    
            if(disp == true)
                get_optimal_alignment(query, expanded);

        }

    }    

    return bestHit;

}