#include <bits/stdc++.h>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;

int i32(){
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }
    
    while(!(buff[ind] < '0' || buff[ind] > '9')){
        ans = ans * 10 + buff[ind] - '0';
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }

    return ans;
}

const int NMAX = 1e6 + 5;

int n;
int nxt[NMAX];
vector <pair<int,int>> G[NMAX];
vector<int> active;
int dist[NMAX];

inline int my_abs(int x){
    return (x < 0 ? -x:x);
}

void dijkstra() {
    priority_queue <pair<int,int>> Q;

    for (int i = 1; i <= n; i++) {
        active.push_back(i);
        dist[i] = i - 1;
        Q.push({-dist[i], i});
    }

    while (!Q.empty()) {
        if (-Q.top().first != dist[Q.top().second]) {
            Q.pop();
            continue;
        }
        int nod = Q.top().second;
        Q.pop();

        int v = nxt[nod];
        if (dist[nod] < dist[v]) {
            dist[v] = dist[nod];
            Q.push({-dist[v], v});
        }

        for(int i = 0;i < (int)active.size();i++){
            if(active[i] == nod){
                swap(active.back(),active[i]);
                active.pop_back();
                break;
            }
        }

        for (auto i:active)
            if (dist[nod] + my_abs(i - nod) < dist[i]) {
                dist[i] = dist[nod] + my_abs(i - nod);
                Q.push({-dist[i], i});
            }
    }
}

int main() {
    n = i32();
    for (int i = 1; i <= n; i++) {
        nxt[i] = i32();
        nxt[i]++;
    }

    dijkstra();
    printf("%d", dist[n]);

    return 0;
}
