//trie class header file
#pragma once

//uses trie node
#include "trie_node.h"

//class prefix_trie
class prefix_trie{

public:

    //has the root, height, and count of nodes
    node* root;
    int height;
    int nodes_count;

    //default constructor
    prefix_trie();
    
    //custom constructor
    prefix_trie(char* query_set, int queries_count, char* error);
    
    //insertion function
    void insert_node(char* query);
    
    //fuzzy search tolerating upto 1 mismatchh
    bool fuzzy_search(char* query, int index = 0, node* root_node = NULL, bool found=false, int mismatches = 0);
    
    //destructor helper function that works recursively
    void destructor_helper(node* root);
    
    //destructor
    ~prefix_trie();

    //copy constructor
    prefix_trie(const prefix_trie &copy);

    //copy constructor helper function that works recursively
    void copy_helper(node* copy, node* curr_root);


};