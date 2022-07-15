#include <iostream>
#include <fstream>
#include <cstring>
#include <utility>

#include "vote.h"

using namespace std;

int main() {
    ifstream cin("vote.in");
    ofstream cout("vote.out");

    int N, M, MOD; cin >> N >> M >> MOD;
    vector< vector<int> > A(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        string S; cin >> S;
        for (int j = 0; j < M; ++j)
            A[i][j] = (S[j] == '1');
    }

    for (auto &x : waysToWin(N, M, MOD, A))
        cout << x << " ";
    cout << "\n";
}
