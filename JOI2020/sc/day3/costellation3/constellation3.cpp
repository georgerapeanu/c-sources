#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

struct point_t{
    int x,y,c,id;
    bool operator < (const point_t &other)const{
        if(y != other.y){
            return y < other.y;
        }
        return id < other.id;
    }
};

class SegmentTree{
private:

    int n;
    vector<long long> aint;
    vector<long long> lazy;

    void propag(int nod,int st,int dr){
        if(st == dr || lazy[nod] == 0){
            return ;
        }

        int mid = (st + dr) / 2;

        aint[nod * 2] += 1LL * (mid - st + 1) * lazy[nod];
        aint[nod * 2 + 1] += 1LL * (dr - mid) * lazy[nod];
        lazy[nod * 2] += lazy[nod];
        lazy[nod * 2 + 1] += lazy[nod];
        lazy[nod] = 0;
    }

    void update(int nod,int st,int dr,int l,int r,long long val){
        propag(nod,st,dr);
        if(dr < l || st > r){
            return ;
        }
        if(l <= st && dr <= r){
            aint[nod] += 1LL * (dr - st + 1) * val;
            lazy[nod] += val;
            return ;
        }
        int mid = (st + dr) / 2;
        
        update(nod * 2,st,mid,l,r,val);
        update(nod * 2 + 1,mid + 1,dr,l,r,val);
        
        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];

    }

    long long query(int nod,int st,int dr,int l,int r){
        propag(nod,st,dr);
        if(dr < l || st > r){
            return 0;
        }
        if(l <= st && dr <= r){
            return aint[nod];
        }
        int mid = (st + dr) / 2;
        return query(nod * 2,st,mid,l,r) + query(nod * 2 + 1,mid + 1,dr,l,r);
    }

public:

    SegmentTree(int n){
        this->n = n;
        aint = vector<long long>(4 * n + 5,0);
        lazy = vector<long long>(4 * n + 5,0);
    }

    void update(int l,int r,long long val){
        update(1,1,n,l,r,val);
    }

    long long query(int pos){
        long long ans = query(1,1,n,pos,pos);
        return ans;
    }
}aint(0);

int n,m;
int a[NMAX + 5];

vector<int> tree[NMAX + 5];
int jump_node[NMAX + 5];

long long dp[NMAX + 5];
int cost[NMAX + 5];

int lst = 0;
int l[NMAX + 5];
int r[NMAX + 5];


void dfs(int nod){
    l[nod] = ++lst;
    dp[nod] = 0;
    for(auto it:tree[nod]){
        dfs(it);
        dp[nod] += dp[it];
    }
    r[nod] = lst;

    for(auto it:tree[nod]){
        aint.update(l[it],r[it],dp[nod] - dp[it]);
    }
   
    aint.update(l[nod],l[nod],dp[nod]);

    dp[nod] += cost[nod];
    dp[nod] = min(dp[nod],aint.query(l[jump_node[nod]]));

    aint.update(l[nod],r[nod],cost[nod]);
}

int main(){

    scanf("%d",&n);

    vector<pair<int,int> > tmp;

    set<int> s;

    for(int i = 1;i <= n;i++){
        scanf("%d",&a[i]);
        tmp.push_back({a[i],i});
        s.insert(i);
    }

    vector<point_t> points;

    scanf("%d",&m);

    for(int i = 1;i <= m;i++){
        points.push_back({0,0,0,0});
        scanf("%d %d %d\n",&points.back().x,&points.back().y,&points.back().c);
        points.back().id = i;
        cost[i] = points.back().c;
    }

    sort(points.begin(),points.end());

    sort(tmp.begin(),tmp.end());
    reverse(tmp.begin(),tmp.end());

    s.insert(0);
    s.insert(n + 1);

    set<pair<pair<int,int>,int> > active_segments;

    set<int> untaken;

    for(int i = 0; i <= n + 1;i++){
        untaken.insert(i);
    }

    vector<int> tag(n + 1,0);

    for(auto it:points){
        while((int)tmp.size() > 0 && tmp.back().first < it.y){
            s.erase(tmp.back().second);
            tmp.pop_back();
        }
        pair<int,int> segm;
        segm.second = (*s.lower_bound(it.x)) - 1;
        segm.first = (*prev(s.lower_bound(it.x))) + 1;

        while(active_segments.empty() == false && active_segments.lower_bound({{segm.first,0},0}) != active_segments.end() && active_segments.lower_bound({{segm.first,0},0})->first.first <= segm.second){
            set<pair<pair<int,int>,int> > :: iterator it2 = active_segments.lower_bound({{segm.first,0},0});
            tree[it.id].push_back(it2->second);
            active_segments.erase(it2);
        }

        while(*untaken.lower_bound(segm.first) <= segm.second){
            tag[*untaken.lower_bound(segm.first)] = it.id;
            untaken.erase(untaken.lower_bound(segm.first));
        }

        jump_node[it.id] = tag[it.x];
        active_segments.insert({segm,it.id});
    }

    aint = SegmentTree(m);

    long long ans = 0;
    
    for(auto it:active_segments){
        dfs(it.second);
        ans += dp[it.second];
    }

    if(false){
        for(int i = 1;i <= m;i++){
            printf("nod %d %d %d %lld\n",i,jump_node[i],cost[i],dp[i]);
            for(auto it:tree[i])printf("%d ",it);
            printf("\n");
        }
    }

    printf("%lld\n",ans);

    return 0;
}
