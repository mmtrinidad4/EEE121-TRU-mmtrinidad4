#include <iostream>
#include <vector>
#include <string>
using namespace std;

void genStateCombi(vector<string> &stateList, int numStates, string stateTrans) {
    if (numStates == 0) {
        cout << stateTrans << endl;
        return;
    }

    for (const string &state : stateList) {
        genStateCombi(stateList, numStates - 1, stateTrans + " " + state);
    }
}

void printAllStates(vector<string> &stateList) {
    genStateCombi(stateList, stateList.size(), "");
}

int main() {
    vector<string> stateList = {"RESET", "IDLE", "ACTIVE", "DONE"};
    printAllStates(stateList);
    return 0;
}
