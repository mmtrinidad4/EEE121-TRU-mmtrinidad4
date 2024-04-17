#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include "Trie.h"
#include "TrieNode.h" 
using namespace std;

int main() {
    int t, g;
    cin >> t;
    g = t;
    while(t--) {
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
