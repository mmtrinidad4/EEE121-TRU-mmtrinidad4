#ifndef TRIENODE_H
#define TRIENODE_H

#include <vector>
#include <string>
using namespace std;

#include "Trie.h"

bool prefix(node* root, string s);
bool check_prefix(string targ, string pref);
void lprefix(node* root, string &long_str, string s, int &max_len, bool &two_branch, 
int &pref_goodness, vector<string> &str_vec, int &best_count);

#endif 







