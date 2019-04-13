#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e4;
const int LGMAX = 30;

vector<pair<int,int> > pref_op;
vector<pair<int,int> > suff_op;

int n;
int x[NMAX + 5];
int y[NMAX + 5];
int bx[LGMAX + 5];
int by[LGMAX + 5];

void do_op(int x[],int i,int j,vector<pair<int,int> > &op) {
    x[i] ^= x[j];
    op.push_back({i,j});
}

void sw(int x[],int i,int j,vector<pair<int,int> > &op) {
    if(i == j) {
        return;
    }
    do_op(x,i,j,op);
    do_op(x,j,i,op);
    do_op(x,i,j,op);
}

int do_gauss(int a[],int b[],vector<pair<int,int> > &op) {
    int l = 0;

    for(int i = 0; i <= LGMAX; i++) {
        for(int j = l + 1; j <= n; j++) {
            if((a[j] >> i) & 1) {
                sw(a,++l,j,op);
                b[l] = i;
                break;
            }
        }

        if(b[l] != i) {
            continue;
        }

        for(int j = 1; j <= n; j++) {
            if(j != l && (((a[j] & a[l]) >> i) & 1)) {
                do_op(a,j,l,op);
            }
        }
    }

    return l;
}

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&x[i]);
    }

    for(int i = 1; i <= n; i++) {
        scanf("%d",&y[i]);
    }

    int n1 = do_gauss(x,bx,pref_op);
    int n2 = do_gauss(y,by,suff_op);

    if(n1 < n2) {
        printf("-1\n");
        return 0;
    }

    int l = 0;

    for(int i = 1; i <= n2; i++) {
        if(bx[i] != by[i]) {
            do_op(x,i,i,pref_op);
        }
        for(int j = i + 1; j <= n1; j++) {
            if(((x[i] ^ y[i]) >> bx[j]) & 1) {
                do_op(x,i,j,pref_op);
            }
        }
    }

    for(int i = 1; i <= n1; i++) {
        if(y[i] == 0) {
            do_op(x,i,i,pref_op);
        }
        if(x[i] != y[i]) {
            printf("-1\n");
            return 0;
        }
    }

    while(suff_op.size()) {
        pref_op.push_back(suff_op.back());
        suff_op.pop_back();
    }

    printf("%d\n",(int)pref_op.size());

    for(auto it:pref_op) {
        printf("%d %d\n",it.first,it.second);
    }

    return 0;
}
