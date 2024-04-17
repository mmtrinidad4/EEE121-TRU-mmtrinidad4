#include "Trie.h"

node* create() {
    node* new_node = new node();
    new_node->end = false;
    return new_node;
}

int node_count(node* root) {
    int count = 1; 
    
    for (std::unordered_map<char, node*>::iterator it = root->children.begin(); it != root->children.end(); it++) {
        node* child_node = it->second;
        count += node_count(child_node);
    }
    return count;
}

void add(node* root, string s) {
    node* curr_node = root;
    int n = s.length();
    for (int i = 0; i < n; i++) {
        if (curr_node->children.find(s[i]) == curr_node->children.end()) {
            curr_node->children[s[i]] = create();
        }
        curr_node = curr_node->children[s[i]];
    }
    curr_node->end = true;
}

bool search(node* root, string s) {
    node* curr_node = root;
    int n = s.length();
    for (int i = 0; i < n; i++) {
        if (curr_node->children.find(s[i]) == curr_node->children.end()) {
            return false;
        }
        curr_node = curr_node->children[s[i]];
    }
    return curr_node->end;
}
