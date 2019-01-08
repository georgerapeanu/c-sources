#include <cstdio>
#include <bitset>

using namespace std;

const int VMAX = 7e3;
const int NMAX = 1e5;
const int QMAX = 1e6;

bitset<VMAX + 1> state[NMAX + 1];
bitset<VMAX + 1> masks[VMAX + 1];
bitset<VMAX + 1> initials[VMAX + 1];

bool sqr_free[VMAX + 1];

int main() {

    for(int i  = 0; i <= VMAX; i++) {
        sqr_free[i] = true;
    }

    for(int i  = 2; i <= VMAX; i++) {
        for(int j = i * i; j <= VMAX; j += i * i) {
            sqr_free[j]= false;
        }
    }

    for(int i = 1; i <= VMAX; i++) {
        for(int j = i; j <= VMAX; j += i) {
            initials[j][i] = 1;
            masks[i][j] = sqr_free[j / i];
        }
    }

    int n,q;
    scanf("%d %d",&n,&q);

    while(q--) {
        int t,x,y,z,v;
        scanf("%d",&t);

        if(t == 1) {
            scanf("%d %d",&x,&v);
            state[x] = initials[v];
        }
        else if(t == 2) {
            scanf("%d %d %d",&x,&y,&z);
            state[x] = state[y] ^ state[z];
        }
        else if(t == 3) {
            scanf("%d %d %d",&x,&y,&z);
            state[x] = state[y] & state[z];
        }
        else {
            scanf("%d %d",&x,&v);
            printf("%d",(int)(state[x] & masks[v]).count() & 1);
        }
    }
    return 0;
}
