#include <bits/stdc++.h>
#include "divine.h"

using namespace std;

namespace {
    static int N, M, Q;
    static vector<vector<int>> edg;
    static vector<int> col, done;
    static vector<pair<int, int>> edges;
}

int DFS(int nod) {
    if (done[nod] || !col[nod])  return 0;
    done[nod] = 1;
    int ans = 1;
    for(const int nxt : edg[nod])
        ans += DFS(nxt);
    return ans;
}

int query(const vector<int>& nodes) {
    for (const int node : nodes)
        col[node] = 1;
    int ans = 0;
    for(auto x: nodes) {
        int cnt = DFS(x);
        ans = max(ans, cnt);
    }
    for (const int node : nodes)
        done[node] = col[node] = 0;
    return ans;
}

void answer(const vector< pair<int, int> >& ans_) {
    vector<pair<int, int>> ans(ans_);
    for (auto& p : ans)
        if (p.first > p.second)
            swap(p.first, p.second);
    sort(ans.begin(), ans.end());
    if (ans == edges)
        cout << "OK" << endl;
    else
        cout << "Wrong answer!" << endl;
    cout << "Queries: " << Q << endl;
    exit(0);
}

void readTest() {
    Q = 0;
    cin >> N >> M;
    edg.resize(N); col.resize(N); done.resize(N);
    for(int i = 0; i < N; i++)
        col[i] = done[i] = 0;
    for(int i = 0; i < M; i++) {
        int x, y;
        cin >> x >> y;
        if(x > y)
            swap(x, y);
        edg[x].push_back(y);
        edg[y].push_back(x);
        edges.emplace_back(x, y);
    }
    sort(edges.begin(), edges.end());
}

int main() {
    readTest();
    solve(N, 1);  // You can change the subtask number :)
    cout << "Answer not called!" << endl;
	return 0;
}