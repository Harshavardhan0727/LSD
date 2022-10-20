#include <iostream>
#include <fstream>
#include <cstring>
#include "prefix_trie.h"
using namespace std;
#define MAX 29903

prefix_trie::prefix_trie(){

    //set all values to NULL
    root = new node();
    height = 0;
    nodes_count = 0;

}

prefix_trie::prefix_trie(char* query_set, int queries_count, char* error){

    //check if insertion is with error
    bool error_flag = false;
    //check for passed flag
    if(strcmp(error, "error") == 0){

        cout << "Mutation/Error is ON!" << endl;
        error_flag = true;

    }

    //set the initial values of the attributes
    root = new node();
    height = 0;
    nodes_count = 0;

    //stores the query
    char query[37];
    query[36] = '\0';

    //count bases in genome
    int max = 0;
    for(int i = 0; query_set[i] != '\0'; i++){
        
        max++;

    }

    max = MAX - 35;

    int rand_start;

    //create the number of queries passed for inserting
    for(int i = 0; i < queries_count; i++){

        rand_start = rand() % max;

        //generate a query to insert
        for(int j = 0; j < 36; j++){

            query[j] = query_set[rand_start+j];

        }

        //if error flag is on
        if(error_flag == true){

            char opts[] = "ACGT";

            //add five percent error
            for(int j = 0; j < 36; j++){

                if(rand() % 100 > 95)
                    query[j] = opts[rand() % 4];

            }

        }

        this->insert_node(query);
    
    }

    cout << "Trie created with max height = " << height << endl;
    cout << "Nodes count = " << nodes_count << endl;

}

void prefix_trie::insert_node(char* query){

    //create the root node
    node* temp = root;

    //root is not leaf, set to false
    bool leaf = false;

    //loop for the sequence and insert the nodes
    for(int i = 0; i < 36; i++){

        //if all the 36mer bases are inserted, it should be leaf at the end
        if(i == 35){
            
            leaf = true;
        
        }
        
        //insert the A node
        if(query[i] == 'A'){
            
            if(temp->A_child == NULL){

                temp->A_child = new node('A', leaf);
                
                if(height < 36)
                    height++;
                
                nodes_count++;

            }

            temp = temp->A_child;

        }
        //insert the C node
        else if(query[i] == 'C'){

            if(temp->C_child == NULL){

                temp->C_child = new node('C', leaf);
                
                if(height < 36)
                    height++;

                nodes_count++;

            }

            temp = temp->C_child;

        }
        
        //insert the G node
        else if(query[i] == 'G'){

            if(temp->G_child == NULL){

                temp->G_child = new node('G', leaf);

                if(height < 36)
                    height++;

                nodes_count++;

            }

            temp = temp->G_child;

        }
        //insert the T node
        else if(query[i] == 'T'){


            if(temp->T_child == NULL){

                temp->T_child = new node('T', leaf);
                
                if(height < 36)
                    height++;

                nodes_count++;

            }

            temp = temp->T_child;

        }
        else{

            cout << "Udef\n";

        }

    }

}

bool prefix_trie::fuzzy_search(char* query, int index, node* root_node, bool found, int mismatches){

    //base case
    //if found, no need to go further
    if(found == true){

        return true;

    }

    //if root is NULL, return false
    if(root_node == NULL){

        return false;

    }

    //if mismatch occured, increment the counter
    if(root_node->base != query[index] && root_node != this->root)
    {
     
        mismatches++;
    
    }
    
    //if leaf node reached without mismatches greated than 1, return true with status found equal to true
    if(root_node->leaf == true && mismatches <= 1){

        found = true;
        return true;

    }

    //if leaf node is reached but mismatches greater than 1, return false
    if(root_node->leaf == true)
        return false;

    //if mismatches exceed the limit, return false
    if(mismatches > 1){

        return false;

    }

    //if the root node is equal to actual root, index shall not be incremented for the genome sequence
    if(root_node == this->root)
        index--;

    //recursively search each child, and store the status of search results in found variable
    found = fuzzy_search(query, index+1, root_node->A_child, found, mismatches);
    found = fuzzy_search(query, index+1, root_node->C_child, found, mismatches);
    found = fuzzy_search(query, index+1, root_node->G_child, found, mismatches);
    found = fuzzy_search(query, index+1, root_node->T_child, found, mismatches);

    //return the value of found to the calling function
    return found;

}

//helper function to deallocate the memory recursively
void prefix_trie::destructor_helper(node* curr_root)
{
    if (curr_root != NULL)
    {
        //recursively delete each child
        destructor_helper(curr_root->A_child);
        destructor_helper(curr_root->C_child);
        destructor_helper(curr_root->G_child);
        destructor_helper(curr_root->T_child);
        
        delete curr_root; //finally start deleting the node from the lowest level

    }
}


prefix_trie::~prefix_trie(){
    
    //call the recursive destructor helper function 
    //send the root of the trie
    destructor_helper(root);

}

//a function that helps the copy constructor by creating a trie recursively
//takes the root node of copy object and the current root of the object to be created
void prefix_trie::copy_helper(node* copy, node* curr_root) {
    
    //if the current root is NULL, simply return
    if (curr_root == NULL){

        copy = NULL;
        return;
    
    }

    //copy the value of current node
    copy->base = curr_root->base;
    copy->leaf = curr_root->leaf;

    if (curr_root->A_child) {

        //create new child node, set values
        copy->A_child = new node(curr_root->A_child->base, curr_root->A_child->leaf);
        
        //recursively call the lower level with updated nodes
        copy_helper(copy->A_child, curr_root->A_child);

    }

    if (curr_root->C_child) {

        //create new child node, set values
        copy->C_child = new node(curr_root->C_child->base, curr_root->C_child->leaf);
        
        //recursively call the lower level with updated nodes
        copy_helper(copy->C_child, curr_root->C_child);

    }

    if (curr_root->G_child) {

        //create new child node, set values
        copy->G_child = new node(curr_root->G_child->base, curr_root->G_child->leaf);
        
        //recursively call the lower level with updated nodes
        copy_helper(copy->G_child, curr_root->G_child);

    }

    if (curr_root->T_child) {

        //create new child node, set values
        copy->T_child = new node(curr_root->T_child->base, curr_root->T_child->leaf);
        
        //recursively call the lower level with updated nodes
        copy_helper(copy->T_child, curr_root->T_child);

    }
}

prefix_trie::prefix_trie(const prefix_trie &copy){

    //create the root node first
    root = new node();

    //call the helper function to recursively copy the nodes of the trie
    copy_helper(root, copy.root);

    //copy the height as well as the number of nodes 
    height = copy.height;
    nodes_count = copy.nodes_count;

}