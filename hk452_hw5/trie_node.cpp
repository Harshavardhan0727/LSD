#include <iostream>
#include "trie_node.h"
using namespace std;

//custom constructor for node, sets all values to null
node::node(){

    base = ' ';
    leaf = false;
    A_child = NULL;
    C_child = NULL;
    G_child = NULL;
    T_child = NULL;

}
//custom constructor for node, sets all to passed values, and the pointers to NULL (initially)
node::node(char b, bool l){

    base = b;
    leaf = l;
    A_child = NULL;
    C_child = NULL;
    G_child = NULL;
    T_child = NULL;
    
}