#include <bits/stdc++.h>

using namespace std;

int n,q;
vector<vector<pair<int,int> > > graph;
vector<pair<int,int> > edges;

class SegmentTree{
    struct node_t{
        int best[2];
        int lazy;
    
        node_t(){
            best[0] = 0;
            best[1] = 0;
            lazy = 0;
        }
    
        node_t operator + (const node_t &other)const{
            node_t ans;
            for(int i = 0;i < 2;i++){
                ans.best[i] = max(this->best[i],other.best[i]);
            }
            ans.lazy = 0;
            return ans;
        }
    
        void propag(int lazy){
            if(lazy){
                swap(best[0],best[1]);
                this->lazy ^= lazy;
            }
        }
    };

    int n;
    vector<node_t> aint;

    void propag(int nod,int st,int dr){
        if(st == dr || aint[nod].lazy == 0){
            return ;
        }

        aint[nod * 2].propag(aint[nod].lazy);
        aint[nod * 2 + 1].propag(aint[nod].lazy);

        aint[nod].lazy = 0;
    }

    void build(int nod,int st,int dr,const vector<int> &lvl,const vector<int> &tp){
        if(st == dr){
            aint[nod].best[tp[st]] = lvl[st];
            aint[nod].best[tp[st] ^ 1] = 0;
            return ;
        }

        int mid = (st + dr) / 2;

        build(nod * 2,st,mid,lvl,tp);
        build(nod * 2 + 1,mid + 1,dr,lvl,tp);
        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

    void flip(int nod,int st,int dr,int l,int r){
        propag(nod,st,dr);

        if(dr < l || st > r){
            return ;
        }

        if(l <= st && dr <= r){
            aint[nod].propag(1);
            return ;
        }

        int mid = (st + dr) / 2;

        flip(nod * 2,st,mid,l,r);
        flip(nod * 2 + 1,mid + 1,dr,l,r);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

public:
    SegmentTree(int n,const vector<int> &lvl,const vector<int> &tp){
        this->n = n;
        aint = vector<node_t>(4 * n + 5,node_t());
        build(1,1,n,lvl,tp);
    }

    SegmentTree(){
        ;
    }

    void flip(int l,int r){
        flip(1,1,n,l,r);
    }

    int query(){
        return aint[1].best[0];
    }

};

class TreeWrapper{
    SegmentTree aint;
    vector<int> lvl;
    vector<int> tp;
    vector<int> l;
    vector<int> r;
    int lst = 0;

    void dfs(int nod,pair<int,int> tata,const vector<vector<pair<int,int> > > &graph){
        l[nod] = ++lst;
        lvl[l[nod]] = 1 + lvl[l[tata.first]];
        tp[l[nod]] = tp[l[tata.first]] ^ tata.second;
        for(auto it:graph[nod]){
            if(it.first == tata.first){
                continue;
            }
            dfs(it.first,{nod,it.second},graph);
        }
        r[nod] = lst;
    }

public:

    TreeWrapper(int root,const vector<vector<pair<int,int> > > &graph){
        lst = 0;
        l = vector<int>(graph.size(),0);
        r = vector<int>(graph.size(),0);
        lvl = vector<int>(graph.size(),0);
        tp = vector<int>(graph.size(),0);
        dfs(root,{0,0},graph);
        aint = SegmentTree((int)graph.size() - 1,lvl,tp);
    }

    void flip(pair<int,int> a){
        if(lvl[l[a.first]] > lvl[l[a.second]]){
            swap(a.first,a.second);
        }
        aint.flip(l[a.second],r[a.second]);
    }

    int query(){
        return aint.query();
    }
};

pair<int,int> dfs(int nod,int tata){
    pair<int,int> ans = {0,nod};
    for(auto it:graph[nod]){
        if(it.first == tata){
            continue;
        }
        pair<int,int> tmp = dfs(it.first,nod);
        tmp.first++;
        ans = max(ans,tmp);
    }
    return ans;
}

int main(){

    scanf("%d",&n);

    graph = vector<vector<pair<int,int> > > (n + 1,vector<pair<int,int> >());
    edges = vector<pair<int,int> >(n,{0,0});

    for(int i = 1;i < n;i++){
        int x,y,t;
        scanf("%d %d %d",&x,&y,&t);
        graph[x].push_back({y,t});
        graph[y].push_back({x,t});
        edges[i] = {x,y};
    }

    int a = dfs(1,0).second;
    int b = dfs(a,0).second;

    TreeWrapper fst(a,graph),snd(b,graph);
   
    scanf("%d",&q);

    while(q--){
        int id;
        scanf("%d",&id);
        fst.flip(edges[id]);
        snd.flip(edges[id]);
        printf("%d\n",max(fst.query(),snd.query()) - 1);
    }
    

    return 0;
}
