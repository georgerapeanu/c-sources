#include <vector>

#include <algorithm>
#include <cstdio>

using namespace std;

const int NMAX = 2e5;

vector<int> graph[NMAX + 5];
int brut_dp[NMAX + 5][2];

void brut(int nod,int tata,int k){
    brut_dp[nod][0] = brut_dp[nod][1] = 1;
    vector<int> sons;
    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        brut(it,nod,k);
        sons.push_back(brut_dp[it][1]);
    }
    sort(sons.begin(),sons.end());
    reverse(sons.begin(),sons.end());

    for(int i = 0;i < k - 1 && i < (int)sons.size();i++){
        brut_dp[nod][0] += sons[i];
        brut_dp[nod][1] += sons[i];
    }
    if(k - 1 < (int)sons.size()){
        brut_dp[nod][0] += sons[k - 1];
    }
}

vector<int> solve(int n, vector<int> a, vector<int> b) {
    std::vector<int> ret(n);

    for(int i = 0;i < (int)a.size();i++){
        graph[a[i]].push_back(b[i]);
        graph[b[i]].push_back(a[i]);
    }

    for(int i = 1;i <= 100;i++){
        brut(1,0,i);
        int ma = 0;
        for(int j = 1;j <= n;j++){
            ma = max(ma,brut_dp[j][0]);
        }
        ret[i - 1] = ma;
    }

    return ret;
}
