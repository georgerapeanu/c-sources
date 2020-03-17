#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("curent.in","r");
FILE *g = fopen("curent.out","w");

const int NMAX = 100011;
const int MMAX = 100022;
const int TMAX = 100033;

struct query_t{
    int id;
    int day;
    int node;
    int delta;

    bool operator < (const query_t &other)const{
        if(day != other.day){
            return day < other.day;
        }
        if(delta != other.delta){
            if(delta == 0){
                return 1;
            }
            if(other.delta == 0){
                return 0;
            }
            return delta < other.delta;
        }
        if(node != other.node){
            return node < other.node;
        }
        return id < other.id;
    }
};

struct node_t{
    int cnt_mi;
    int mi;
    int lazy;

    node_t(){
        cnt_mi = mi = lazy = 0;
    }

    node_t(int cnt_mi,int mi,int lazy){
        this->cnt_mi = cnt_mi;
        this->mi = mi;
        this->lazy = lazy;
    }

    node_t operator + (const node_t &other)const{
        node_t ans;

        if(this->mi <= other.mi){
            ans.mi = this->mi;
            ans.cnt_mi += cnt_mi;
        }
        if(this->mi >= other.mi){
            ans.mi = other.mi;
            ans.cnt_mi += other.cnt_mi;
        }

        return ans;
    }
};

node_t aint[4 * NMAX + 5];

void build(int nod,int st,int dr){
    aint[nod] = node_t(1,0,0);
    if(st == dr){
        return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

void propag(int nod,int st,int dr){
    if(st == dr || aint[nod].lazy == 0){
        return ;
    }

    aint[nod * 2].lazy += aint[nod].lazy;
    aint[nod * 2].mi += aint[nod].lazy;

    aint[nod * 2 + 1].lazy += aint[nod].lazy;
    aint[nod * 2 + 1].mi += aint[nod].lazy;

    aint[nod].lazy = 0;
}

void update(int nod,int st,int dr,int l,int r,int val){
    propag(nod,st,dr);
    if(r < st || l > dr){
        return ;
    }
    if(l <= st && dr <= r){
        aint[nod].lazy += val;
        aint[nod].mi += val;
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,l,r,val);
    update(nod * 2 + 1,mid + 1,dr,l,r,val);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

int query(){
    return (aint[1].mi == 0) * aint[1].cnt_mi;
}

vector<int> graph[NMAX + 5];
int n,m,t;
int st[NMAX + 5];
int dr[NMAX + 5];
int len;
bool broken[NMAX + 5];
int ans[NMAX + 5];

void dfs(int nod){
    st[nod] = ++len;

    for(auto it:graph[nod]){
        dfs(it);
    }

    dr[nod] = len;
}

vector<query_t> stuff;

const int LEN = 1 << 13;
char buff[LEN];
int ind = LEN - 1;

int i32(){
    int ans = 0;
    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            fread(buff,1,LEN,f);
            ind = 0;
        }
    }

    while(!(buff[ind] < '0' || buff[ind] > '9')){
        ans = ans * 10 + buff[ind] - '0';
        if(++ind >= LEN){
            fread(buff,1,LEN,f);
            ind = 0;
        }
    }

    return ans;
}

int main(){

    n = i32();

    build(1,1,n);

    for(int i = 2;i <= n;i++){
        int fa;
        fa = i32();
        graph[fa].push_back(i);
    }

    dfs(1);

    m = i32();

    for(int i = 1;i <= m;i++){
        int a,b,c;
        a = i32();
        b = i32();
        c = i32();
        if(c == 0){
            stuff.push_back({0,a,b,1});
        }
        else{
            stuff.push_back({0,a,b,-1});
        }
    }

    t = i32();

    for(int i = 1;i <= t;i++){
        int a;
        a = i32();
        stuff.push_back({i,a,1,0});
    }

    sort(stuff.begin(),stuff.end());

    for(auto it:stuff){
        if(it.delta == -1 && broken[it.node] == false){
            continue;
        }
        if(it.delta == 1 && broken[it.node] == true){
            continue;
        }
        update(1,1,n,st[it.node],dr[it.node],it.delta);
        if(it.delta == -1){
            broken[it.node] = false;
        }
        else if(it.delta == 1){
            broken[it.node] = true;
        }
        ans[it.id] = query();
    }

    for(int i = 1;i <= t;i++){
        fprintf(g,"%d\n",ans[i]);
    }

    fclose(f);
    fclose(g);

    return 0;
}
