#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;
const int MMAX = 10;
const int BUCK = 320;

int n,m,q;
char c[NMAX + 5][MMAX + 5];

pair<int,int> ins_buck[NMAX + 5][MMAX + 5];
int l_buck[NMAX + 5];
int r_buck[NMAX + 5];
int buck[NMAX + 5];
int buck_cnt;

void init() {
    buck_cnt = 0;
    for(int i = 1; i <= n; i += BUCK) {
        buck_cnt++;
        l_buck[buck_cnt] = i;
        for(int j = i; j < i + BUCK && j <= n; j++) {
            buck[j] = buck_cnt;
            r_buck[buck_cnt] = j;
        }
    }

    for(int i = 1; i <= n; i++) {
        ins_buck[i][0] = {i,0};
        ins_buck[i][m + 1] = {i,m + 1};
    }

    for(int j = 1; j <= m; j++) {
        ins_buck[0][j] = {0,j};
    }

    for(int i = 1; i <= buck_cnt; i++) {
        for(int j = l_buck[i]; j <= r_buck[i]; j++) {
            for(int k = 1; k <= m; k++) {
                ins_buck[j][k] = {j,k};
            }
            for(int k = 1; k <= m; k++) {
                if(c[j][k] == '<') {
                    ins_buck[j][k] = ins_buck[j][k - 1];
                }
            }
            for(int k = m; k; k--) {
                if(c[j][k] == '>') {
                    ins_buck[j][k] = ins_buck[j][k + 1];
                }
            }
            for(int k = 1; k <= m; k++) {
                if(c[j][k] == '<') {
                    ins_buck[j][k] = ins_buck[j][k - 1];
                }
                if(ins_buck[j][k].second >= 0 && (c[j][ins_buck[j][k].second] == '<' || c[j][ins_buck[j][k].second] == '>')) {
                    ins_buck[j][k] = {-2,-2};
                }
            }
            for(int k = 1; k <= m; k++) {
                if(c[j][k] == '^') {
                    ins_buck[j][k] = {j - 1,k};
                }
            }
        }
        for(int k = 1; k <= m; k++) {
            int j = l_buck[i];
            if(ins_buck[j][k].second > 0 && ins_buck[j][k].second <= m) {
                ins_buck[j][k] = {j - 1,ins_buck[j][k].second};
            }
        }
        for(int j = l_buck[i] + 1; j <= r_buck[i]; j++) {
            for(int k = 1; k <= m; k++) {
                if(ins_buck[j][k].second > 0 && ins_buck[j][k].second <= m) {
                    ins_buck[j][k] = ins_buck[j - 1][ins_buck[j][k].second];
                }
            }
        }
    }
}

void update(int x,int y,char nc) {
    c[x][y] = nc;
    int i = buck[x];
    for(int j = l_buck[i]; j <= r_buck[i]; j++) {
        for(int k = 1; k <= m; k++) {
            ins_buck[j][k] = {j,k};
        }
        for(int k = 1; k <= m; k++) {
            if(c[j][k] == '<') {
                ins_buck[j][k] = ins_buck[j][k - 1];
            }
        }
        for(int k = m; k; k--) {
            if(c[j][k] == '>') {
                ins_buck[j][k] = ins_buck[j][k + 1];
            }
        }
        for(int k = 1; k <= m; k++) {
            if(c[j][k] == '<') {
                ins_buck[j][k] = ins_buck[j][k - 1];
            }
            if(ins_buck[j][k].second >= 0 && (c[j][ins_buck[j][k].second] == '<' || c[j][ins_buck[j][k].second] == '>')) {
                ins_buck[j][k] = {-2,-2};
            }
        }
        for(int k = 1; k <= m; k++) {
            if(c[j][k] == '^') {
                ins_buck[j][k] = {j - 1,k};
            }
        }
    }
    for(int k = 1; k <= m; k++) {
        int j = l_buck[i];
        if(ins_buck[j][k].second > 0 && ins_buck[j][k].second <= m) {
            ins_buck[j][k] = {j - 1,ins_buck[j][k].second};
        }
    }
    for(int j = l_buck[i] + 1; j <= r_buck[i]; j++) {
        for(int k = 1; k <= m; k++) {
            if(ins_buck[j][k].second > 0 && ins_buck[j][k].second <= m) {
                ins_buck[j][k] = ins_buck[j - 1][ins_buck[j][k].second];
            }
        }
    }
}

pair<int,int> query(int x,int y) {
    while(true) {
        if(ins_buck[x][y].first == -2) {
            return {-1,-1};
        }
        if(x == 0) {
            return {x,y};
        }
        if(ins_buck[x][y].second == 0 || ins_buck[x][y].second == m + 1) {
            return ins_buck[x][y];
        }
        y = ins_buck[x][y].second;
        x = r_buck[buck[x] - 1];
    }
}

void afis() {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            printf("%d %d %d %d\n",i,j,ins_buck[i][j].first,ins_buck[i][j].second);
        }
    }
    printf("\n\n");
}

int main() {

    scanf("%d %d %d\n",&n,&m,&q);
    for(int i = 1; i <= n; i++) {
        fgets(c[i] + 1,MMAX + 5,stdin);
    }

    init();

    for(int i = 1; i <= q; i++) {
        char c;
        int x,y;
        char d;
        scanf("%c %d %d",&c,&x,&y);
        if(c == 'C') {
            scanf(" %c\n",&d);
            update(x,y,d);
        }
        else {
            scanf("\n");
            pair<int,int> tmp = query(x,y);
            printf("%d %d\n",tmp.first,tmp.second);
        }
    }

    return 0;
}
