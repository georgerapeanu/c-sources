#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("rutier.in","r");
FILE *g = fopen("rutier.out","w");

const int BUCK = 5000;
const int NMAX = 5e4;
const int MMAX = 15e4;

int n;
int m;

pair<int,int> father[NMAX + 5];
long long sum = 0;

int x[MMAX + 5];
int y[MMAX + 5];
int z[MMAX + 5];

const int LEN = 1 << 12;
int ind = LEN - 1;
char buff[LEN];

pair<int,pair<int,int> > edges[NMAX + 5];
pair<int,pair<int,int> > tmp_edges[MMAX + 5];
pair<int,pair<int,int> > n_edges[NMAX + 5];
bool wh[NMAX + 5];

int i32(){
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while(!(buff[ind] < '0' || buff[ind] > '9')){
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    return ans;
}

int dsu[NMAX + 5];

void init_dsu(){
    memset(dsu + 1,0,sizeof(int) * n);
}

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

int to_norm[NMAX + 5];
pair<int,int> comp_father[BUCK + 5];
int viz[NMAX + 5];

vector<pair<int,int> > graph[BUCK + 5];

void dfs(int nod,pair<int,int> fa){
    comp_father[nod] = fa;
    for(auto it:graph[nod]){
        if(it.first != fa.first){
            dfs(it.first,{nod,it.second});
        }
    }
}

pair<int,int> tx[BUCK + 5];
pair<int,int> ty[BUCK + 5];
int l_x,l_y;

void add_buck(int l,int r){
    init_dsu();
    int lst1 = 1;
    int lst2 = l;
    int lst = 1;

    while(lst <= n - 1){
        if(lst1 > n - 1){
            if(unite(tmp_edges[lst2].second.first,tmp_edges[lst2].second.second) == false){
                lst2++;
                continue;
            }
            n_edges[lst] = tmp_edges[lst2];
            wh[lst] = true;
            lst2++;
            lst++;
        }
        else if(lst2 > r){
            if(unite(edges[lst1].second.first,edges[lst1].second.second) == false){
                lst1++;
                continue;
            }
            n_edges[lst] = edges[lst1];
            wh[lst] = false;
            lst1++;
            lst++;
        }
        else if(tmp_edges[lst2].first <= edges[lst1].first){
            if(unite(tmp_edges[lst2].second.first,tmp_edges[lst2].second.second) == false){
                lst2++;
                continue;
            }
            n_edges[lst] = tmp_edges[lst2];
            wh[lst] = true;
            lst2++;
            lst++;
        }
        else{
            if(unite(edges[lst1].second.first,edges[lst1].second.second) == false){
                lst1++;
                continue;
            }
            n_edges[lst] = edges[lst1];
            wh[lst] = false;
            lst1++;
            lst++;
        }
    }

    init_dsu();

    for(int i = 1;i < n;i++){
        if(wh[i] == false){
            unite(n_edges[i].second.first,n_edges[i].second.second);
        }
    }

    lst = 0;

    for(int i = 1;i <= n;i++){
        if(dsu[i] == 0){
            to_norm[i] = ++lst;
            graph[lst].clear();
        }
    }

    for(int i = 1;i < n;i++){
        if(fi_root(edges[i].second.first) != fi_root(edges[i].second.second)){
            graph[to_norm[fi_root(edges[i].second.first)]].push_back({to_norm[fi_root(edges[i].second.second)],edges[i].first});
            graph[to_norm[fi_root(edges[i].second.second)]].push_back({to_norm[fi_root(edges[i].second.first)],edges[i].first});
        }
    }

    dfs(to_norm[fi_root(1)],{0,0});

    for(int i = l;i <= r;i++){
        tx[l_x = 1] = {to_norm[fi_root(x[i])],comp_father[to_norm[fi_root(x[i])]].second};
        ty[l_y = 1] = {to_norm[fi_root(y[i])],comp_father[to_norm[fi_root(y[i])]].second};

        while(tx[l_x].first != to_norm[fi_root(1)]){
            tx[l_x + 1].first = comp_father[tx[l_x].first].first;
            tx[l_x + 1].second = comp_father[tx[l_x + 1].first].second;
            l_x++;
        }
        while(ty[l_y].first != to_norm[fi_root(1)]){
            ty[l_y + 1].first = comp_father[ty[l_y].first].first;
            ty[l_y + 1].second = comp_father[ty[l_y + 1].first].second;
            l_y++;
        }

        while(tx[l_x] == ty[l_y]){
            l_x--;
            l_y--;
        }

        pair<int,int> ans = tx[l_x];

        for(int i = 1;i <= l_x;i++){
            if(ans.second < tx[i].second){
                ans = tx[i];
            }
        }
        bool sw = false;
        for(int i = 1;i <= l_y;i++){
            if(ans.second < ty[i].second){
                ans = ty[i];
                sw = true;
            }
        }

        if(ans.second > z[i]){
            sum += z[i] - ans.second;
            if(sw){
                swap(tx,ty);
                swap(l_x,l_y);
            }
            pair<int,int> link = {ty[1].first,z[i]};
            for(int j = 1;j <= l_x;j++){
                comp_father[tx[j].first] = link;
                link = tx[j];
                if(tx[j] == ans){
                    break;
                }
            }
        }
        fprintf(g,"%lld\n",sum);
    }

    for(int i = 1;i < n;i++){
        edges[i] = n_edges[i];
    }
}

int main(){

    n = i32();

    for(int i = 2;i <= n;i++){
        father[i].first = i32();
        father[i].second = i32();
        edges[i - 1] = {father[i].second,{i,father[i].first}};
        sum += father[i].second;
    }

    sort(edges + 1,edges + n);

    m = i32();

    for(int i = 1;i <= m;i++){
        x[i] = i32();
        y[i] = i32();
        z[i] = i32();
        tmp_edges[i] = {z[i],{x[i],y[i]}};
    }

    for(int i = 1;i <= m;i += BUCK){
        sort(tmp_edges + i,tmp_edges + min(i + BUCK,m + 1));
        add_buck(i,min(m,i + BUCK - 1));
    }

    fclose(f);
    fclose(g);

    return 0;
}
