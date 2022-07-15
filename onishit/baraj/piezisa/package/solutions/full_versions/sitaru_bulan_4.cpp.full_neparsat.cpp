//sitaru_bulan_4.cpp
#include <bits/stdc++.h>

using namespace std;

const int BLN = 30;
const int BLN2 = 15;

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

class BinaryIndexedTree {
public:
    int N;
    vector<int> aib;

    BinaryIndexedTree(int _N) {
        N = _N;
        aib = vector<int>(N + 5, 1 << 30);
    }

    void update(int p, int v) {
        p += 2;
        for(; p <= N; p += p & (-p))
            aib[p] = min(aib[p], v);
    }

    int query(int p) {
        p += 2;
        int ans = 1 << 30;
        for(; p > 0; p -= p & (-p))
            ans = min(ans, aib[p]);
        return ans;
    }


};

void solve_one_side(vector<int> &v, vector<int> &lft, vector<int> &rgt, int solutions[]) {
    int N = v.size(), Q = lft.size();

    for(int i = 1; i < N; i++)  v[i] ^= v[i - 1];

    int K;
    unordered_map<int, int> nrm;
    K = 1;
    nrm[0] = 0;
    for(int i = 0; i < N; i++) {
        if (!nrm.count(v[i])) {
            nrm[v[i]] = K++;
        }
        v[i] = nrm[ v[i] ];
    }

    vector<int> pos[K];

    pos[0].push_back(-1);
    for(int i = 0; i < N; i++)
        pos[ v[i] ].push_back(i);

    for(int q = 0; q < Q; q++) {
        int l = lft[q], r = rgt[q];

        int ans = N + 1;
        for(int j = l - 1; j >= -1 && j >= l - BLN; j--) {
            int val = j == -1 ? 0 : v[j];
            auto it = lower_bound(pos[val].begin(), pos[val].end(), r);
            if(it != pos[val].end()) {
                ans = min(ans, (*it) - j);
            }
        }

        solutions[q] = min(ans, solutions[q]);
    }

    vector<int> capr[N];
    for(int q = 0; q < Q; q++) {
        capr[ rgt[q] ].push_back(q);
    }

    BinaryIndexedTree aib(N);
    vector<int> wh(K, 0);
    for(int i = 0; i < K; i++)
        wh[i] = pos[i].size();
    for(int r = N - 1; r >= 0; r--) {
        int val = v[r];
        wh[val]--;

        for(int i = wh[val] - 1; i >= 0 && i >= wh[val] - BLN2; i--)
            aib.update(pos[val][i], (r - pos[val][i]));

        for(int i = 0; i < wh[val] && i < BLN2; i++)
            aib.update(pos[val][i], (r - pos[val][i]));

        if(wh[val] > 0) {
            for (int k = 0; k < BLN2 * 2; k++) {
                int i = rng() % wh[val];
                aib.update(pos[val][i], (r - pos[val][i]));
            }
        }

        for(auto id: capr[r]) {
            int l = lft[id];
            int ans = aib.query(l - 1);
            solutions[id] = min(solutions[id], ans);
        }
    }
}

void solve(int N, int v[], int Q, int lft[], int rgt[], int solutions[]) {
    for(int q = 0; q < Q; q++)  solutions[q] = N + 1;

    vector<int> _v, _lft, _rgt;
    _v = vector<int>(N, 0);
    _lft = _rgt = vector<int>(Q, 0);
    for(int i = 0; i < N; i++)  _v[i] = v[i];
    for(int i = 0; i < Q; i++) {
        _lft[i] = lft[i];
        _rgt[i] = rgt[i];
    }

    solve_one_side(_v, _lft, _rgt, solutions);

    _v = vector<int>(N, 0);
    _lft = _rgt = vector<int>(Q, 0);
    for(int i = 0; i < N; i++)  _v[i] = v[N - i - 1];
    for(int i = 0; i < Q; i++) {
        _lft[i] = N - rgt[i] - 1;
        _rgt[i] = N - lft[i] - 1;
    }

    solve_one_side(_v, _lft, _rgt, solutions);

    for(int q = 0; q < Q; q++)
        if(solutions[q] == N + 1)   solutions[q] = -1;
}
#include <stdio.h>
#include <stdlib.h>

int main(){
  
  int n, q;
  scanf("%d", &n);
  int* v = (int*)malloc(sizeof(int) * n);

  for(int i = 0;i < n;i++){
    scanf("%d", &v[i]);
  }

  scanf("%d", &q);

  int* l = (int*)malloc(sizeof(int) * q);
  int* r = (int*)malloc(sizeof(int) * q);
  for(int i = 0;i < q;i++){
    scanf("%d %d", &l[i], &r[i]);
  }

  int* answers = (int*)malloc(sizeof(int) * q);

  solve(n, v, q, l, r, answers);

  for(int i = 0;i < q;i++){
    printf("%d\n", answers[i]);
  }

  free(answers);
  free(l);
  free(r);
  free(v);

  return 0;
}
