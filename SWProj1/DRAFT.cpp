#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
using namespace std;



struct node {
    unordered_map<char, node*> children;
    bool end;
};

//Need a function that creates a node
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

//Need a function that adds nodes given a string
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

//Need a function that searches for a particular word
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

//Need a function that searches if a prefix is present
//NOTE: Completely irrelevant to the problem.
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
            //Why do I need to do this? 
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
            //Why do I need to do this? 
            new_count = max_count;
        }
        
        if (new_count*g_len > pref_goodness) {
            best_count = new_count;
            pref_goodness = new_count*g_len;
            max_len = g_len;
        }
       
    }
}

/*
For tree approach:
1. Get the node of the one corresponding to the longest prefix tree (the deepest node that is either a two branch (if it exists) or a 
or a one branch (if two branches do not exist)).

2. Starting from that node, traverse down. 

3. Count the number of words formed.

        o
      /  \
    o     o
   /
  o
 /  \
o    o

Make the code below more efficient! Implement the algorithm!
*/

//Add algorithm to count the number of nodes. It's a simple graph traversal!
int main() {
    int t, g;
    cin >> t;
    g = t;
    while(t--) {
        //Clean this up! So many variables!
        node* root = create();
        bool two_branch = false;
        map<string, int> count;
        int max_len = 0;
        int max_count = 0;
        string longpref = "";
        string s = "";
        int long_string = 0;
        int digit_num = 0;
        int n;
        int pref_goodness = -1;
        cin >> n;
        vector<string> str_vec(n);
        
        for (int i = 0; i < n; i++) {
            //Clean this up!
            string input_string;
            cin >> input_string;
            str_vec[i] = input_string;
            add(root, input_string);
            int str_len = input_string.length();
            
            digit_num += str_len;
            long_string = max(str_len, long_string);
        }
        int new_count;
        string ans;
        string long_str = "";
        int best_count = 0;
        lprefix(root, s, s, max_len, two_branch, pref_goodness, str_vec, best_count);

        //FIX: No need for this condition! It will continue to traverse anyway!
        
        //Organize this into a function! This looks messy.
        int node_num = node_count(root);
        cout << "Test Case #" << g - t << ":\n";       
        cout << "Number of digits in all binary strings: " << digit_num << "\n";
        cout << "Number of nodes in Trie: " << node_num << "\n"; 
        cout << "Max prefix length: " << max_len << "\n";
        cout << "Total substrings: " << best_count << "\n";
        cout << "Prefix goodness: " << best_count*max_len << "\n";
        cout << "\n";
    }
    return 0;
}