#include <cstdio>

using namespace std;

const int NMAX = 1e5;

struct time_table {
    int tm[60];

    time_table operator + (const time_table &other)const {
        time_table ans;

        for(int i = 0; i < 60; i++) {
            ans.tm[i] = this->tm[i] + other.tm[(i + this->tm[i]) % 60];
        }

        return ans;
    }
};

time_table aint[4 * NMAX + 5];

void update(int nod,int st,int dr,int pos,int val) {
    if(dr < pos || st > pos) {
        return ;
    }

    if(st == dr) {
        for(int j = 0; j < 60; j++) {
            aint[nod].tm[j] = 1 + (j % val == 0);
        }
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,pos,val);
    update(nod * 2 + 1,mid + 1,dr,pos,val);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

time_table identity;

time_table query(int nod,int st,int dr,int S,int D) {
    if(S <= st && dr <= D) {
        return aint[nod];
    }

    if(dr < S || st > D) {
        return identity;
    }

    int mid = (st + dr) / 2;

    return query(nod * 2,st,mid,S,D) + query(nod * 2 + 1,mid + 1,dr,S,D);
}

int n,q;

int main() {

    for(int i = 0; i < 60; i++) {
        identity.tm[i] = 0;
    }

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        int val;
        scanf("%d",&val);
        update(1,1,n,i,val);
    }

    scanf("%d\n",&q);

    while(q--) {
        char c;
        int x,y;
        scanf("%c %d %d\n",&c,&x,&y);
        if(c == 'A') {
            printf("%d\n",query(1,1,n,x,y - 1).tm[0]);
        }
        else {
            update(1,1,n,x,y);
        }
    }

    return 0;
}
