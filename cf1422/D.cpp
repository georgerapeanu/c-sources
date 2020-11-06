#include <bits/stdc++.h>

using namespace std;

int n,m;
vector<pair<int,int>> p;

pair<int,int> s,f;

vector<int> solve(pair<int,int> pos,vector<pair<int,int> > &warp){
    vector<int> dists(warp.size());
    
    set<pair<int,int> > xs,ys;
    priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > pq;

    for(int i = 0;i < (int)warp.size();i++){
        dists[i] = 1e9;
        xs.insert({warp[i].first,i});
        ys.insert({warp[i].second,i});
    }

    xs.insert({pos.first,-1});
    ys.insert({pos.second,-1});

    pq.push({0,-1});

    while(pq.size() > 0){
        pair<int,int> tmp = pq.top();
        pq.pop();
        pair<int,int> p = (tmp.second == -1 ? pos:warp[tmp.second]);
        if(tmp.second != -1 && dists[tmp.second] != tmp.first){
            continue;
        }

        xs.erase({p.first,tmp.second});
        ys.erase({p.second,tmp.second});

        set<pair<int,int> > :: iterator it;

        it = xs.lower_bound({p.first,tmp.second});

        if(it != xs.end()){
            if(dists[it->second] > tmp.first + it->first - p.first){
                dists[it->second] = tmp.first + it->first - p.first;
                pq.push({dists[it->second],it->second});
            }
        }
        if(it != xs.begin()){
            it--;
            if(dists[it->second] > tmp.first + p.first - it->first){
                dists[it->second] = tmp.first + p.first - it->first;
                pq.push({dists[it->second],it->second});
            }
        }
        
        it = ys.lower_bound({p.second,tmp.second});

        if(it != ys.end()){
            if(dists[it->second] > tmp.first + it->first - p.second){
                dists[it->second] = tmp.first + it->first - p.second;
                pq.push({dists[it->second],it->second});
            }
        }
        if(it != ys.begin()){
            it--;
            if(dists[it->second] > tmp.first + p.second - it->first){
                dists[it->second] = tmp.first + p.second - it->first;
                pq.push({dists[it->second],it->second});
            }
        }
    }

    return dists;
}

int main() {

    scanf("%d %d",&n,&m);

    scanf("%d %d",&s.first,&s.second);
    scanf("%d %d",&f.first,&f.second);

    for(int i = 0;i < m;i++){
        p.push_back({0,0});
        scanf("%d %d",&p[i].first,&p[i].second);
    }

    vector<int> ds = solve(s,p);

    int ans = abs(s.first - f.first) + abs(s.second - f.second);

    for(int i = 0;i < (int)ds.size();i++){
        ans = min(ans,ds[i] + abs(f.first - p[i].first) + abs(f.second - p[i].second));
    }

    printf("%d\n",ans);

    return 0;
}
