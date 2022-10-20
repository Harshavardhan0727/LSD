#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

class FASTA_readset{

    int dataset_number;
    char ** dataset;
    int total_reads_for_dataset;
    int current_read_index;
    int total_segments_with_copies;

public:

    FASTA_readset(){

        this->dataset_number = 0;
        this->dataset = NULL;
        this->total_reads_for_dataset = 0;
        this->current_read_index = 0;
        this->total_segments_with_copies = 0;

    }


    FASTA_readset(string filename, int dataset_num){

        this->dataset_number = dataset_num;
        this->total_reads_for_dataset = 0;
        this->current_read_index = 0;
        this->total_segments_with_copies = 0;

        /* reusing code from the given start code*/

        ifstream input;  		//create filestream to read the file
        input.open(filename);		//initialize the filestream by pointing it to the right file
        
        char * temp_header = new char[1000];	//temporary buffer for header... 1000 characters will do
        char * temp_read   = new char[1000];	//temporary buffer for genomic data... 1000 characters will do
        char * temp_buffer = new char[1000];	//another temp buffer
        int a, b, i, j, k; 				//temporary counters to be used later
        int header_length;
        
        //read in 15 read tuples (header + genomic sequence)
        while(input >> temp_header){
             	//read in the header line

            count_dataset_instances(temp_header);

            input >> temp_read;		//read in the read line

            // Lets figure out how long the header is
                header_length = 0;
                while(temp_header[header_length] != '\0'){	// '\0' is a special end-of-string character
                    header_length++;
                }
            
            // pull out the read number... may want to make this into a function... you'll be doing this 
            // a lot for the parsing out the read count numbers from the header string

                a = 2; //third letter in header... we are assuming the first two are ">R"... may be good to double check
                b = a;	

                while(temp_header[b] != '_' && b < header_length){	
                    b++;
                }
                // by this point we either found the delimiter "_" or we ran off the end of the header
                if(b == header_length){   // something went wrong
                    cout << "Error: exhausted header string looking for read number... exiting" << endl;
                    exit(-1);
                }else{
                    for(j = a; j < b; j++){//copy of the read number to a new string
                        temp_buffer[j - a] = temp_header[j];
                    }
                    temp_buffer[j] = '\0'; // top of the read number with the end-of-string special character
                }

                // convert your character string temp_buffer into an integer so you can do math with it when needed
                k = atoi(temp_buffer);		//this will convert the temp_buffer string into an integer

               // cout << "The read ID is R" << k << endl;
               // cout << "The read sequence is: " << temp_read << endl;

    	}

        //after getting the total number of sequences, create a character array of respective size

        this->dataset = new char*[this->total_reads_for_dataset];

        initialize_arrays(filename);

    }
    
    //function to create character arrays and store fasta reads
    void initialize_arrays(string filename){

        /* reusing code from the given start code*/

        ifstream input;  		//create filestream to read the file
        input.open(filename);		//initialize the filestream by pointing it to the right file
        
        char * temp_header = new char[1000];	//temporary buffer for header... 1000 characters will do
        char * temp_read   = new char[1000];	//temporary buffer for genomic data... 1000 characters will do
        char * temp_buffer = new char[1000];	//another temp buffer
        
        int a, b, i, j, k; 				//temporary counters to be used later
        int header_length;
        
        //read in 15 read tuples (header + genomic sequence)
        while(input >> temp_header){
            
            input >> temp_read;		//read in the read line

            if(is_relevant(temp_header) > 0){

                //counting instances with copies
                this->total_segments_with_copies += is_relevant(temp_header);
                
                this->dataset[this->current_read_index++] = new char[(50 * is_relevant(temp_header))+1];

                for(int j = 0; j < (50 * is_relevant(temp_header)); j++){

                    this->dataset[this->current_read_index-1][j] = temp_read[j % 50];

                }

                this->dataset[this->current_read_index-1][(50 * is_relevant(temp_header))] = '\0';    


            }

            //storing reads specific to the dataset


    	}


    }

    int is_relevant(string header){

        int pos = 1;
        

        int i = 0;

        for(i = 0; header[i] != '\0' && header[i] != '_'; i++){

            continue;

        }

        i++;

        for(i = i; header[i] != '\0'; i++){

                if(header[i] == '_'){

                    continue;

                }

                if(header[i] != '0' && pos == (this->dataset_number)){
                    
                    return atoi(&header[i]);
                    pos++;

                }
                else{

                    pos++;

                }


        }

        return -1;
    }

    char* get_fragment(int index){

        return dataset[index];

    }

    int get_unique_segments_count(){

        return this->total_reads_for_dataset;
        
    }

    int get_total_segments_count(){

        return this->total_segments_with_copies;

    }

    void count_dataset_instances(string header){
        
        int pos = 1;
        

        int i = 0;

        for(i = 0; header[i] != '\0' && header[i] != '_'; i++){

            continue;

        }

        i++;

        for(i = i; header[i] != '\0'; i++){

                if(header[i] == '_'){

                    continue;

                }

                if(header[i] != '0' && pos == (this->dataset_number)){
                    
                    this->total_reads_for_dataset++;
                    pos++;

                }
                else{

                    pos++;

                }


        }

    }

    void print_arrays(){

        for(int i = 0; i < total_reads_for_dataset; i++){

            for(int j = 0; dataset[i][j] != '\0'; j++){

                cout << dataset[i][j];

            }

            cout << endl;

        }

    }

    void sort_alphabetically(){

        char * temp;

        //sorting - ASCENDING ORDER
        for(int i=0; i < this->get_unique_segments_count(); i++)
        {		
            for(int j = i+1; j < this->get_unique_segments_count(); j++)
            {
                if(strcmp(dataset[i],dataset[j]) > 0)
                {
   
                    temp  = dataset[i];
                    dataset[i] = dataset[j];
                    dataset[j] = temp;
   
                }
            }
        }

    }

    int binary_search(char* query, int l = 0, int r = -1)
    {

        if(r == -1){

            r = this->get_unique_segments_count() - 1;

        }

        if (r >= l) {
            int mid = l + (r - l) / 2;
    
            // If the element is present at the middle
            // itself
            if (strcmp(dataset[mid], query) == 0){

                return true;

            }
                
    
            // If element is smaller than mid, then
            // it can only be present in left subarray
            if (strcmp(dataset[mid], query) > 0)
                return binary_search(query, l, mid - 1);
    
            // Else the element can only be present
            // in right subarray
            return binary_search(query, mid + 1, r);
        }
    
        // We reach here when element is not
        // present in array
        
        return false;
    }

    // a function to search a given sequence fragment in the dataset in unsorted form
    bool linear_search(char * query){
        
        for(int i = 0; i < this->get_unique_segments_count(); i++){

            bool not_found = false;
            int j;

            for(j = 0; query[j] != '\0' && dataset[i][j] != '\0'; j++){

                if(query[j] != dataset[i][j]){

                    not_found = true;
                    break;

                }

            }


            if(not_found == false && query[j] == '\0' && dataset[i][j] == '\0'){
      
                return true;
            }

        }

        return false;
    }

    ~FASTA_readset(){

        if(this->dataset != NULL){

            for(int i = 0; i < this->total_reads_for_dataset; i++){

                delete [] dataset[i];

            }

            delete [] dataset;

        }

    }

};