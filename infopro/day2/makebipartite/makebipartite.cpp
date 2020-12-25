#include "makebipartite.h"
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int DEB = 0;
const int NMAX = 1e6;

struct dsu_t{
    int n;
    vector<int> father;
    vector<vector<int> > comp;
    vector<int> col;
    vector<pair<int,int> > history;

    dsu_t(int n){
        this->n = n;
        father = vector<int>(n + 1,0);
        comp = vector<vector<int> >(n + 1);
        col = vector<int> (n + 1,0);
        for(int i = 1;i <= n;i++){
            comp[i].push_back(i);
        }
    }

    int find_root(int nod){
        while(father[nod]){
            nod = father[nod];
        }
        return nod;
    }

    bool unite(int x,int y){
        if(DEB)printf("unite %d %d\n",x,y);
        int tmp_x = x;
        int tmp_y = y;
        x = find_root(x);
        y = find_root(y);
        
        if(comp[x].size() > comp[y].size()){
            swap(x,y);
            swap(tmp_x,tmp_y);
        }

        history.push_back({x,y});

        if(x == y){
            if(DEB)printf("answer1 %d\n",col[tmp_x] != col[tmp_y]);
            return col[tmp_x] != col[tmp_y];
        }

        father[x] = y;
        for(auto it:comp[x]){
            comp[y].push_back(it);
        }
        
        if(col[tmp_x] == col[tmp_y]){
            for(auto it:comp[x]){
                col[it] ^= 1;
            }
        }

        if(DEB)printf("answer2 true\n");
        return true;
    }

    void undo(){
        pair<int,int> tmp = history.back();
        if(DEB)printf("undo %d %d\n",tmp.first,tmp.second);
        history.pop_back();
        if(tmp.first == tmp.second){
            return ;
        }
        father[tmp.first] = 0;
        for(int i = 0;i < (int)comp[tmp.first].size();i++){
            comp[tmp.second].pop_back();
        }
    }

    void afis(){
        printf("col ");
        for(int i = 1;i <= n;i++){
            printf("%d ",col[i]);
        }
        printf("\n");
    }
};

class SegmentTree{
    int n;
    vector<vector<pair<int,int> > > aint;

    void update(int nod,int st,int dr,int l,int r,pair<int,int> val){
        if(r < st || l > dr){
            return ;
        }
        
        if(l <= st && dr <= r){
            aint[nod].push_back(val);
            return ;
        }

        int mid = (st + dr) / 2;

        update(nod * 2,st,mid,l,r,val);
        update(nod * 2 + 1,mid + 1,dr,l,r,val);
    }

    void dfs(int nod,int st,int dr,dsu_t &solver,char *S,bool ok){
        int cnt = 0;
        for(int i = 0;i < (int)aint[nod].size() && ok;i++){
            ok &= solver.unite(aint[nod][i].first,aint[nod][i].second);
            if(DEB)solver.afis();
            cnt++;
        }

        if(st == dr){
            S[st - 1] = ok + '0';
            for(int i = 0;i < cnt;i++){
                solver.undo();
            }
            return ;
        }

        int mid = (st + dr) / 2;

        dfs(nod * 2,st,mid,solver,S,ok);
        dfs(nod * 2 + 1,mid + 1,dr,solver,S,ok);

        for(int i = 0;i < cnt;i++){
            solver.undo();
        }
    }

public:
    
    SegmentTree(int n){
        this->n = n;
        aint = vector<vector<pair<int,int> > >(4 * n + 5);
    }

    void push(int l,int r,pair<int,int> edge){
        update(1,1,n,l,r,edge);
    }

    void solve(dsu_t &solver,char *S){
        dfs(1,1,n,solver,S,true);
    }
};

int n,m;

void solve(int N,int M,int *X,int *Y,char *S){

    n = N;
    m = M;

    dsu_t solver(n);
    SegmentTree aint(n);

    for(int i = 0;i < m;i++){
        if(1 <= min(X[i],Y[i]) - 1){
            aint.push(1,min(X[i],Y[i]) - 1,{X[i],Y[i]});
        }
        if(min(X[i],Y[i]) + 1 <= max(X[i],Y[i]) - 1){
            aint.push(min(X[i],Y[i]) + 1,max(X[i],Y[i]) - 1,{X[i],Y[i]});
        }
        if(max(X[i],Y[i]) + 1 <= n){
            aint.push(max(X[i],Y[i]) + 1,n,{X[i],Y[i]});
        }

    }

    aint.solve(solver,S);
}
