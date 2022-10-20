#include <iostream>
#include <fstream>
#include "prefix_trie.h"

using namespace std;

char* read_genome_file(char* filename);

int search(prefix_trie& trie, char* genome);