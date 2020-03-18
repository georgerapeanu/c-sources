#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("rusuoaica.in","r");
FILE *g = fopen("rusuoaica.out","w");

const int NMAX = 1e5;

int n,m,a;
vector<pair<int,pair<int,int> > > edges;

int dsu[NMAX + 5];

int fi_root(int x) {
    if(dsu[x] == 0) {
        return x;
    }
    return dsu[x] = fi_root(dsu[x]);
}

bool unite(int x,int y) {
    x = fi_root(x);
    y = fi_root(y);
    if(x == y) {
        return false;
    }
    dsu[x] = y;
    return true;
}

const int LEN = 1 << 13;
char buff[LEN];
int ind = LEN - 1;

int i32() {
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9') {
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while(!(buff[ind] < '0' || buff[ind] > '9')) {
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    return ans;
}

int main() {

    n = i32();
    m = i32();
    a = i32();

    int ans = 0;

    for(int i = 1; i <= m; i++) {
        int u,v,w;
        u = i32();
        v = i32();
        w = i32();
        if(w > a) {
            ans -= w;
            //       printf("eat %d %d %d, ans is %d\n",u,v,w,ans);
        }
        else {
            edges.push_back({w,{u,v}});
        }
    }

    sort(edges.begin(),edges.end());

    int cnt = 0;

    for(auto it:edges) {
        if(unite(it.second.first,it.second.second)) {
            cnt++;
            ans += it.first;
            //        printf("build edge %d %d %d,ans is %d\n",it.first,it.second.first,it.second.second,ans);
        }
        else {
            ans -= it.first;
            //        printf("sell edge %d %d %d,ans is %d\n",it.first,it.second.first,it.second.second,ans);
        }
    }

    ans += a * ((n - 1) - cnt);

    // printf("build remaining %d edges,ans is %d\n",n - 1 - cnt,ans);

    fprintf(g,"%d\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
