#include "TrieNode.h"

bool prefix(node* root, string s) {
    node* curr_node = root;
    int n = s.length();
    for (int i = 0; i < n; i++) {
        if (curr_node->children.find(s[i]) == curr_node->children.end()) {
            return false;
        }
        curr_node = curr_node->children[s[i]];
    }
    return true;
}

bool check_prefix(string targ, string pref) {
    int n = pref.length();
    for (int i = 0; i < (n); i++) {
        if (targ[i] != pref[i]) {
            return false;
        }
    }
    return true;
}

void lprefix(node* root, string &long_str, string s, int &max_len, bool &two_branch, 
int &pref_goodness, vector<string> &str_vec, int &best_count) {
    node* curr_node = root;
    string bnry = "01";
    string bnry_char = "";

    int branch_count = 0;
    for (int i = 0; i < 2; i++) {
        if (curr_node->children.find(bnry[i]) != curr_node->children.end()) {
            branch_count++;
            bnry_char += bnry[i];
        }
    }
    
    if ((branch_count == 1) && (curr_node->end == false)) {
        curr_node = curr_node->children[bnry_char[0]];
        s = s + bnry_char[0];

        lprefix(curr_node, long_str, s, max_len, two_branch, pref_goodness, str_vec, best_count);

    } else if (branch_count == 2){
        two_branch = true;
        int n = s.length();
        int g_len = n;
        long_str = s;
        
        int new_count = 0;
        //FIX: No need for this condition! It will continue to traverse anyway!
        if (s.length() == 0) {
            new_count = 1;
        } else {
            int max_count = 0;
            //Remove this function once you implement the tree-based algorithm!
            for (int i = 0; i < str_vec.size(); i++) {
                if (check_prefix(str_vec[i], s) == true) {
                    max_count++;
                }
            }
            new_count = max_count;
        }
        
        if (new_count*g_len > pref_goodness) {
            best_count = new_count;
            
            max_len = g_len;
            pref_goodness = new_count*g_len;
        } else if (new_count*g_len == pref_goodness) {
            if (g_len > max_len) {
                best_count = new_count;
                max_len = g_len;
            }
        }
        lprefix(curr_node->children[bnry_char[0]], 
            long_str, s + bnry_char[0], max_len, two_branch, pref_goodness, str_vec, best_count);

        lprefix(curr_node->children[bnry_char[1]],
            long_str, s + bnry_char[1], max_len, two_branch, pref_goodness, str_vec, best_count);
        
    } else if ((branch_count == 0) && (curr_node->end == true)) {
        int n = s.length();
        int g_len = n;
        long_str = s;
        
        int new_count = 1;
        //FIX: No need for this condition! It will continue to traverse anyway!
        if (s.length() == 0) {
            new_count = 1;
        } else {
            int max_count = 0;
            //Remove this function once you implement the tree-based algorithm!
            for (int i = 0; i < str_vec.size(); i++) {
                if (check_prefix(str_vec[i], s) == true) {
                    max_count++;
                }
            } 
            new_count = max_count;
        }
        
        if (new_count*g_len > pref_goodness) {
            best_count = new_count;
            pref_goodness = new_count*g_len;
            max_len = g_len;
        }
       
    }
}
