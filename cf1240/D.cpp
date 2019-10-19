#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e5;

int t;
int n;
int a[NMAX + 5];

map<pair<int,int>,int> edge;
int w1[NMAX + 5];
int w2[NMAX + 5];
int fa[NMAX + 5];
int lst_node;
int curr_node;
vector<int> stuff;

long long solve(int st,int dr){

    if(st == dr){
        return 0;
    }

    int mid = (st + dr) / 2;
    long long ans = solve(st,mid) + solve(mid + 1,dr);

    stuff.clear();
    curr_node = 0;
    for(int i = mid + 1;i <= dr;i++){
        if(stuff.empty() || stuff.back() != a[i]){
            stuff.push_back(a[i]);
            if(edge.count({curr_node,a[i]}) == 0){
                edge[{curr_node,a[i]}] = ++lst_node;
                fa[lst_node] = curr_node;
            }
            curr_node = edge[{curr_node,a[i]}];
        }
        else{
            stuff.pop_back();
            curr_node = fa[curr_node];
        }
        w1[curr_node]++;
    }
    
    stuff.clear();
    curr_node = 0;
    for(int i = mid;i >= st;i--){
        if(stuff.empty() || stuff.back() != a[i]){
            stuff.push_back(a[i]);
            if(edge.count({curr_node,a[i]}) == 0){
                edge[{curr_node,a[i]}] = ++lst_node;
                fa[lst_node] = curr_node;
            }
            curr_node = edge[{curr_node,a[i]}];
        }
        else{
            stuff.pop_back();
            curr_node = fa[curr_node];
        }
        w2[curr_node]++;
    }

    edge.clear();
    for(int i = 0;i <= lst_node;i++){
        ans += 1LL * w1[i] * w2[i];
        fa[i] = 0;
        w1[i] = 0;
        w2[i] = 0;
    }
    lst_node = 0;

    return ans;
}

int main() {

    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);

        for(int i = 1;i <= n;i++){
            scanf("%d",&a[i]);
        }

        printf("%lld\n",solve(1,n));
    }

    return 0;
}
