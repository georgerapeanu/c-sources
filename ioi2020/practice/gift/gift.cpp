#include "gift.h"
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 5e5;

struct dsu_t{
    int n;
    int father[NMAX + 5];
    int l[NMAX + 5];
    int r[NMAX + 5];

    dsu_t(int n){
        this->n = n;

        for(int i = 1;i <= n;i++){
            father[i] = 0;
            l[i] = r[i] = i;
        }
    }

    int find_root(int nod){
        if(father[nod] == 0){
            return nod;
        }
        return father[nod] = find_root(father[nod]);
    }

    bool unite(int x,int y){
        x = find_root(x);
        y = find_root(y);

        if(x == y){
            return false;
        }

        father[x] = y;
        l[y] = min(l[y],l[x]);
        r[y] = max(r[y],r[x]);

        return true;
    }
};

int construct(int n, int r, vector<int> a, vector<int> b, vector<int> x) {
    for(auto &it:a)it++;
    for(auto &it:b)it++;

    dsu_t dsu(n);

    for(int k = 0;k < r;k++){
        if(x[k] == 2){
            continue;
        }
        for(int pos = dsu.r[dsu.find_root(a[k])];pos < b[k];pos = dsu.r[dsu.find_root(pos + 1)]){
            dsu.unite(pos,pos + 1);
        }
    }

    for(int k = 0;k < r;k++){
        if(x[k] == 2){
            if(dsu.find_root(a[k]) == dsu.find_root(b[k])){
                return 0;
            }
        }
    }

    string s(n, 'R');

    int col = 0;

    for(int pos = 1;pos <= n; pos = dsu.r[dsu.find_root(pos)] + 1){
        for(int i = dsu.l[dsu.find_root(pos)];i <= dsu.r[dsu.find_root(pos)];i++){
            s[i - 1] = (col == 0 ? 'R':'B');
        }
        col ^= 1;
    }

    craft(s);

    return 1;
}
