#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("copsamica.in","r");
FILE *g = fopen("copsamica.out","w");

int t;
int n;

pair<int,pair<int,int> > edges[1000 * 999 / 2 + 5];
int gr[1005];
int dsu[1005];
int sz[1005];

int fi_root(int nod) {
    if(dsu[nod] == 0) {
        return nod;
    }
    return dsu[nod] = fi_root(dsu[nod]);
}

bool unite(int x,int y) {
    x = fi_root(x);
    y = fi_root(y);

    if(x == y) {
        return false;
    }

    if(sz[x] > sz[y]) {
        swap(x,y);
    }

    dsu[x] = y;
    sz[y] += sz[x];

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

    t = i32();

    while(t--) {

        n = i32();

        int lst = 0;

        for(int i = 1; i <= n; i++) {
            for(int j = i + 1; j <= n; j++) {
                edges[++lst] = {i32(),{i,j}};
            }
            gr[i] = 0;
            dsu[i] = 0;
            sz[i] = 1;
        }

        sort(edges + 1,edges + 1 + lst);
        reverse(edges + 1,edges + 1 + lst);

        for(int i = 1; i <= lst; i++) {
            pair<int,pair<int,int> > it = edges[i];
            if(gr[it.second.first] < 2 && gr[it.second.second] < 2 && unite(it.second.first,it.second.second)) {
                fprintf(g,"%d %d %d\n",it.second.first,it.second.second,it.first);
                gr[it.second.first]++;
                gr[it.second.second]++;
            }
        }

        vector<int> tmp;

        for(int i = 1; i <= n; i++) {
            if(gr[i] == 1) {
                tmp.push_back(i);
            }
        }

        fprintf(g,"%d %d 0\n",tmp[0],tmp[1]);
    }
    fclose(f);
    fclose(g);

    return 0;
}
