#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int n;

pair<int,int> d[NMAX + 5];

int v[2 * NMAX + 5],len;

pair<int,int> edge[2 * NMAX + 5];

bool cmp(pair<int,int> a,pair<int,int> b){
    if(a.first != b.first){
        return a.first > b.first;
    }
    return a.second < b.second;
}

int main() {

    scanf("%d",&n);
    
    for(int i = 1;i <= n;i++){
        scanf("%d",&d[i].first);
        d[i].second = i;
    }

    sort(d + 1,d + 1 + n,cmp);

    len = n;
    for(int i = 1;i <= n;i++){
        v[i] = 2 * d[i].second - 1;
        if(i > 1){
            edge[i - 1] = {v[i - 1],v[i]};
        }
    }

    for(int i = 1;i <= n;i++){
        edge[n + i - 1] = {v[i + d[i].first - 1],v[i] + 1};
        if(i + d[i].first - 1 == len){
            v[++len] = v[i] + 1;
        }
    }

    for(int i = 1;i < 2 * n;i++){
        printf("%d %d\n",edge[i].first,edge[i].second);
    }

    return 0;
}
