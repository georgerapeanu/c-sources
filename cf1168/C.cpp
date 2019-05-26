#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <iostream>
#include <cstdlib>

using namespace std;

const int NMAX = 3e5;
const int LGMAX = 19;
const int VMAX = 3e5;

int n,q;
int v[NMAX + 5];

int nxt[NMAX + 1][LGMAX + 1];///nxt after pos who has a bit in common and bit j set

int last[LGMAX + 1][LGMAX + 1];

void prepare() {

    for(auto &it:last){
        for(auto &it2:it)it2 = n + 1;
    }

    for(int i = n;i;i--){
        for(int b = 0;b < LGMAX;b++){
            nxt[i][b] = n + 1;
        }
        for(int b = 0;b < LGMAX;b++){
            if((v[i] >> b) & 1){
                for(int j = 0;j < LGMAX;j++){
                    nxt[i][j] = min(nxt[i][j],last[b][j]);
                }
            }
        }
        for(int b = 0;b < LGMAX;b++){
            if((v[i] >> b) & 1){
                for(int bb = 0;bb < LGMAX;bb++){
                    if((v[i] >> bb) & 1){
                        last[b][bb] = i;
                    }
                }
            }
        }
    }

}

int fst_pos[LGMAX + 5];
bool inside[LGMAX + 5];
bool bfs(int pos,int target) {

    for(auto &it:fst_pos){
        it = n + 1;
    }

    for(auto &it:inside){
        it = false;
    }

    for(int bit = 0;bit < LGMAX;bit++){
        if((v[pos] >> bit) & 1){
            fst_pos[bit] = pos;
        }
    }

    while(true) {

        int pos = target + 1,b = -1;

        for(int bit = 0;bit < LGMAX;bit++){
            if(inside[bit] == false && fst_pos[bit] < pos){
                b = bit;
                pos = fst_pos[bit];
            }
        }

        if(pos == target + 1){
            break;
        }

        inside[b] = true;

        if(v[pos] & v[target]){
            return true;
        }

        for(int to = 0; to < LGMAX; to++) {
            int tmp_pos = nxt[pos][to];
            if(tmp_pos == n + 1) {
                continue;
            }
            if(tmp_pos < fst_pos[to]) {
                fst_pos[to] = tmp_pos;
            }
        }
    }

    return false;
}

bool solve(int x,int y) {
    return bfs(x,y);
}

int main() {

    scanf("%d %d",&n,&q);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&v[i]);
    }

    prepare();

    for(int i = 1; i <= q; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        printf("%s\n",(solve(x,y) == 1 ? "Shi":"Fou"));
    }

    return 0;
}
