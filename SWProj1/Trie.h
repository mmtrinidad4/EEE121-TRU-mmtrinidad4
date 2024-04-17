#ifndef TRIE_H
#define TRIE_H

#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

struct node {
    unordered_map<char, node*> children;
    bool end;
};

node* create();
int node_count(node* root);
void add(node* root, string s);
bool search(node* root, string s);

#endif 

// TRIE_H
