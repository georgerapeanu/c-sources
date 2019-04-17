#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int NMAX = 1e3;

int n;
vector<pair<int,int> > v[2];

void solve(int root,int st,int dr,set<pair<int,int> > &edges,vector<pair<int,int> > &ans,bool reversed) {
    if(st == dr - 1) {
        return ;
    }

    int other = -1;

    for(int i = st; i <= dr; i++) {
        if(edges.count({st,i}) && edges.count({dr,i})) {
            other = i;
            break;
        }
    }

    if(reversed == false) {
        ans.push_back({st,dr});
    }
    else {
        ans.push_back({root,other});
    }

    edges.erase({st,dr});
    edges.erase({dr,st});
    edges.insert({root,other});
    edges.insert({other,root});

    solve(root,st,other,edges,ans,reversed);
    solve(root,other,dr,edges,ans,reversed);
}

vector<pair<int,int> > transform(vector<pair<int,int> > &v,bool reversed) {

    set<pair<int,int> > s;

    for(auto it:v) {
        s.insert({it.first,it.second});
        s.insert({it.second,it.first});
    }

    for(int i = 1; i <= n; i++) {
        s.insert({i,i % n + 1});
        s.insert({i % n + 1,i});
    }

    vector<int> tmp;

    for(auto it:s) {
        if(it.first > 1) {
            break;
        }
        tmp.push_back(it.second);
    }

    vector<pair<int,int> > ans;

    for(int i = 0; i < (int)tmp.size() - 1; i++) {
        solve(1,tmp[i],tmp[i + 1],s,ans,reversed);
    }

    if(reversed) {
        reverse(ans.begin(),ans.end());
    }

    return ans;
}



int main() {
    scanf("%d",&n);
    for(int t = 0; t < 2; t++) {
        for(int i = 1; i <= n - 3; i++) {
            int x,y;
            scanf("%d %d",&x,&y);
            v[t].push_back({x,y});
        }
    }

    vector<pair<int,int> > v1 = transform(v[0],false);
    vector<pair<int,int> > v2 = transform(v[1],true);

    printf("%d\n",(int)v1.size() + (int)v2.size());

    for(auto it:v1) {
        printf("%d %d\n",it.first,it.second);
    }

    for(auto it:v2) {
        printf("%d %d\n",it.first,it.second);
    }

    return 0;
}
