#include <bits/stdc++.h>

using namespace std;


int n,m;

int dsu[200005];

int fi_root(int nod){
    if(dsu[nod] == 0){
        return nod;
    }
    return dsu[nod] = fi_root(dsu[nod]);
}

bool unite(int x,int y){
    x = fi_root(x);
    y = fi_root(y);

    if(x == y){
        return false;
    }

    dsu[x] = y;
    
    return true;
}

int main() {

    scanf("%d %d",&n,&m);

    vector<int> a(n + 1,0);
    vector<int> b(m + 1,0);
    
    vector<int> ord_a(n + 1,0);
    vector<int> ord_b(m + 1,0);
    vector<int> inv_a(n + 1,0);
    vector<int> inv_b(m + 1,0);

    for(int i = 1;i <= n;i++){
        scanf("%d",&a[i]); 
        ord_a[i] = i;
    }

    for(int i = 1;i <= m;i++){
        scanf("%d",&b[i]); 
        ord_b[i] = i;
    }

    sort(ord_a.begin(),ord_a.end(),[&](int i,int j){
                return a[i] < a[j];
            });
    sort(ord_b.begin(),ord_b.end(),[&](int i,int j){
                return b[i] < b[j];
            });

    sort(a.begin(),a.end());
    sort(b.begin(),b.end());

    for(int i = 0;i <= n;i++){
        inv_a[ord_a[i]] = i;
    }
    
    for(int i = 0;i <= m;i++){
        inv_b[ord_b[i]] = i;
    }

    vector<vector<int> > sets = vector<vector<int> >(n + 1,vector<int>());

    for(int i = 1;i <= n;i++){
        int len;
        scanf("%d",&len);
        vector<int> stuff;
        for(int j = 1;j <= len;j++){
            int val;
            scanf("%d",&val);
            stuff.push_back(inv_b[val]);
        }
        sets[inv_a[i]] = stuff;
    }

    long long ans = 0;


    vector<pair<int,pair<int,int> > > edges;

    for(int i = 1;i <= n;i++){
        for(auto it:sets[i]){
            edges.push_back({a[i] + b[it],{i,it + n}});
        }
    }

    sort(edges.begin(),edges.end());
    reverse(edges.begin(),edges.end());

    for(auto it:edges){
        if(unite(it.second.first,it.second.second) == false){
            ans += it.first;
        }
    }

    printf("%lld\n",ans);

    return 0;
}
