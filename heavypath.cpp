#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("heavypath.in","r");
FILE *g = fopen("heavypath.out","w");

const int NMAX = 1e5;

class SegmentTree{
private:
    int n;
    vector<int> aint;
   
    void build(int nod,int st,int dr,const vector<int> &vals){
        if(st == dr){
            aint[nod] = vals[st];
            return ;
        }

        int mid = (st + dr) / 2;

        build(nod * 2,st,mid,vals);
        build(nod * 2 + 1,mid + 1,dr,vals);

        aint[nod] = max(aint[nod * 2],aint[nod * 2 + 1]);
    }

    void update(int nod,int st,int dr,int pos,int val){
        if(dr < pos || st > pos){
            return ;
        }
        
        if(st == dr){
            aint[nod] = val;
            return ;
        }

        int mid = (st + dr) / 2;

        update(nod * 2,st,mid,pos,val);
        update(nod * 2 + 1,mid + 1,dr,pos,val);

        aint[nod] = max(aint[2 * nod],aint[2 * nod + 1]);
    }

    int query(int nod,int st,int dr,int S,int D){
        if(dr < S || st > D){
            return 0;
        }
        
        if(S <= st && dr <= D){
            return aint[nod];
        }

        int mid = (st + dr) / 2;

        return max(query(nod * 2,st,mid,S,D),query(nod * 2 + 1,mid + 1,dr,S,D));
    }
public:
 
    SegmentTree(int n){
        this->n = n;
        this->aint = vector<int>(4 * n + 5,0);
    }

    SegmentTree(const vector<int> &vals){
        this->n = (int)vals.size() - 1;
        this->aint = vector<int>(4 * n + 5,0);
        this->build(1,1,n,vals);
    }

    void update(int pos,int val){
        this->update(1,1,n,pos,val);
    }

    int query(int l,int r){
        return this->query(1,1,n,l,r);
    }
};


int n,q;
int v[NMAX + 5];

int hpd[NMAX + 5];
int sz[NMAX + 5];
int ind[NMAX + 5];
int lvl[NMAX + 5];
int weight[NMAX + 5];
int root[NMAX + 5];
int father[NMAX + 5];
vector<SegmentTree> lant;
int last_comp;

vector<int> graph[NMAX + 5];

void dfs(int nod,int tata){
    lvl[nod] = lvl[tata] + 1;
    hpd[nod] = -1;
    weight[nod] = 1;
    father[nod] = tata;

    int bigChild = -1;

    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        dfs(it,nod);
        weight[nod] += weight[it];

        if(bigChild == -1 || weight[it] > weight[bigChild]){
            bigChild = it;
        }
    }

    if(bigChild == -1){
        last_comp++;
        hpd[nod] = last_comp;
        sz[last_comp]++;
        ind[nod] = sz[last_comp];
        root[last_comp] = nod;
    }
    else{
        hpd[nod] = hpd[bigChild];
        sz[hpd[nod]]++;
        ind[nod] = sz[hpd[nod]];
        root[hpd[nod]] = nod;
    }
}

int solve(int x,int y){
    if(lvl[root[hpd[x]]] > lvl[root[hpd[y]]]){
        swap(x,y);
    }
    
    if(hpd[x] == hpd[y]){
        if(lvl[x] > lvl[y]){
            swap(x,y);
        }
        return lant[hpd[x]].query(ind[y],ind[x]);
    }
    else{
        return max(lant[hpd[y]].query(ind[y],sz[hpd[y]]),solve(x,father[root[hpd[y]]]));
    }
}

int main(){

    fscanf(f,"%d %d",&n,&q);

    for(int i = 1;i <= n;i++){
        fscanf(f,"%d",&v[i]);
    }

    for(int i = 1;i < n;i++){
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    dfs(1,0);

    lant.push_back(SegmentTree(0));

    for(int i = 1;i <= last_comp;i++){
        lant.push_back(SegmentTree(sz[i]));
    }

    for(int i = 1;i <= n;i++){
        lant[hpd[i]].update(ind[i],v[i]);
    }
    
    while(q--){
        int t,x,y;
        fscanf(f,"%d %d %d",&t,&x,&y);

        if(t == 0){
            lant[hpd[x]].update(ind[x],y);
        }
        else{
            fprintf(g,"%d\n",solve(x,y));
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
