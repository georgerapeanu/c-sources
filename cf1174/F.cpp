#include <bits/stdc++.h>

using namespace std;

int dist_to_searched(int u) {
    int ans;
    cout << "d " << u << endl;
    cin >> ans;
    return ans;
}

int ancestor_to(int u) {
    int ans;
    cout << "s " << u << endl;
    cin >> ans;
    return ans;
}

void answer(int u) {
    cout << "! " << u << endl;
    exit(0);
}

const int NMAX = 2e5;
int n;
vector<int> graph[NMAX + 5];
int heavy_child[NMAX + 5];
int lvl[NMAX + 5];
int weight[NMAX + 5];

void dfs(int nod,int tata) {
    lvl[nod] = 1 + lvl[tata];
    weight[nod] = 1;
    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        dfs(it,nod);
        weight[nod] += weight[it];
    }
    heavy_child[nod] = -1;

    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        if(2 * weight[it] > weight[nod]) {
            heavy_child[nod] = it;
        }
    }
}

vector<int> lant;
void solve(int nod,int target_lvl) {
    if(lvl[nod] == target_lvl) {
        answer(nod);
    }

    if(heavy_child[nod] == -1) {
        solve(ancestor_to(nod),target_lvl);
        return ;
    }

    lant.clear();

    for(int i = nod; i > 0; i = heavy_child[i]) {
        lant.push_back(i);
    }

    int a = lvl[lant.back()] - lvl[lant[0]];
    int b = target_lvl - lvl[nod];
    int c = dist_to_searched(lant.back());
    int x = (a + b + c) / 2 - c;

    heavy_child[lant[x]] = -1;
    solve(lant[x],target_lvl);
}

int main() {

    cin >> n;

    for(int i = 1; i < n; i++) {
        int u,v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int a = -1;

    dfs(1,0);
    solve(1,dist_to_searched(1) + 1);

    return 0;
}
