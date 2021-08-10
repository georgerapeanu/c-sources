#include "tcolor.h"

using namespace std;

const int NMAX = 1e5;
int n;
int v;
int e;
vector<int> tree[NMAX + 5];
vector<int> graph[NMAX + 5];

vector<int> solve(int N, int V, int E, vector<int> A, vector<int> B, vector<int> X, vector<int> Y){
    n = N;
    v = V;
    e = E;
    
    2SATSOLVER solver(n * v);
    for(int i = 0;i < n;i++){
        for(int j = 0;j < v;j++){
            i * n + j
        }
    }
}
