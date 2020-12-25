#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("connect.in","r");
FILE *g = fopen("connect.out","w");

const int NMAX = 2e5;

class DSU{
    int n;
    vector<int> father;
    vector<int> sz;
    
    vector<pair<int,int> > history;
    vector<int> edge_history;

    int l,r;
    int cnt;

    public:

    DSU(int n){
        this->n = n;
        father = vector<int>(n + 1,0);
        sz = vector<int>(n + 1,1);
        l = r = 0;
        cnt = n;
        sz[0] = 0;
    }

    int find_root(int nod){
        if(father[nod] == 0){
            return nod;
        }
        return find_root(father[nod]);
    }
    
    bool unite(int x,int y,int id){
        edge_history.push_back(id);
        if(l == 0 && r == 0){
            l = r = id;
        }
        else if(id == l - 1){
            l--;
        }
        else{
            r++;
        }
        x = find_root(x);
        y = find_root(y);

        if(x == y){
            history.push_back({0,0});
            return false;
        }

        if(sz[x] > sz[y]){
            swap(x,y);
        }

        father[x] = y;
        sz[y] += sz[x];

        history.push_back({x,y});
        cnt--;
        return true;
    }

    void undo(){
        if(!(history.back().first == 0 && history.back().second == 0)){
            cnt++;
        }
        father[history.back().first] = 0;
        sz[history.back().second] -= sz[history.back().first];
        history.pop_back();
        if(edge_history.back() == l){
            l++;
        }
        else{
            r--;
        }
        edge_history.pop_back();
        if(edge_history.empty()){
            l = r = 0;
        }
    }

    int get_left(){
        return l;
    }

    int get_right(){
        return r;
    }

    void undo_until_in_range(int st,int dr){
        while(edge_history.size() > 0 && (l < st || r > dr)){
            this->undo();        
        }
    }

    int cnt_comp(){
        return cnt;
    }

};

int n,m;
pair<int,int> edges[NMAX + 5];

int find_optimal(int pos,int st,int dr,int l,int r,DSU &stuff){
    l = max(l,pos);
    r = min(r,m);
    stuff.undo_until_in_range(dr + 1,l - 1);
    
    if(dr + 1 <= l - 1){
        if(stuff.get_left() == 0 && stuff.get_right() == 0){
            stuff.unite(edges[dr + 1].first,edges[dr + 1].second,dr + 1);
        }
        for(int i = stuff.get_left() - 1;i >= pos;i--){
            stuff.unite(edges[i].first,edges[i].second,i);
        }
        for(int i = stuff.get_right() + 1;i < l;i++){
            stuff.unite(edges[i].first,edges[i].second,i);
        }

        for(int i = l;i <= r;i++){
            stuff.unite(edges[i].first,edges[i].second,i);
            if(stuff.cnt_comp() == 1){
                return i;
            }
        }
        return r + 1;
    }
    else{
        for(int i = pos;i <= r;i++){
            stuff.unite(edges[i].first,edges[i].second,i);
            if(stuff.cnt_comp() == 1){
                return i;
            }
        }
        return r + 1;
    }

}

long long solve(int st,int dr,int l,int r,DSU &stuff){
    if(st > dr){
        return 0;
    }
    if(r == l){
        return 1LL * (m - r + 1) * (dr - st + 1);
    }

    int mid = (st + dr) / 2;
    int tmp = find_optimal(mid,st,dr,l,r,stuff);

    long long ans = m - tmp + 1;

    ans += solve(st,mid - 1,l,tmp,stuff);
    ans += solve(mid + 1,dr,tmp,r,stuff);

    return ans;
}

const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;

int i32(){
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    while(!(buff[ind] < '0' || buff[ind] > '9')){
        ans = ans * 10 + buff[ind] - '0';
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    return ans;
}

int main(){

    n = i32();
    m = i32();

    for(int i = 1;i <= m;i++){
        edges[i].first = i32();
        edges[i].second = i32();
    }

    DSU dsu(n);
    fprintf(g,"%lld\n",solve(1,m,1,m,dsu));

    fclose(f);
    fclose(g);

    return 0;
}
