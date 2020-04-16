#include <cstdio>

using namespace std;

FILE *f = fopen("operatie.in","r");
FILE *g = fopen("operatie.out","w");

const int LEN = 1 << 14;
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

int n,b;
int v[1005][1005];
int ans[1005];

void afis() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if((i + j) & 1) {
                if(v[i][j] != ((((1 << b) - 1) ^ ans[i]) | ans[j])) {
                    fprintf(g,"-1\n");
                    return ;
                }
            }
            else if((i + j) & 2) {
                if(v[i][j] != (ans[i] & ans[j])) {
                    fprintf(g,"-1\n");
                    return ;
                }
            }
            else {
                if(v[i][j] != (ans[i] ^ ans[j])) {
                    fprintf(g,"-1\n");
                    return ;
                }
            }
        }
    }
    for(int i = 0; i < n; i++) {
        fprintf(g,"%d ",ans[i]);
    }
}

void solve2(int i) {
    if(i & 1) {
        ans[i] = v[i][i];
        ans[i + 1] = 0;
        for(int h = 0; h < b; h++) {
            int val = (ans[i] >> h) & 1;
            if(val) {
                ans[i + 1] |= (((v[i][i + 1] >> h) & 1) << h);
            }
            else {
                ans[i + 1] |= ((((v[i + 1][i] >> h) & 1) << h) ^ (1 << h));
            }
        }
    }
    else {
        ans[i] = 0;
        ans[i + 1] = v[i + 1][i + 1];
        for(int h = 0; h < b; h++) {
            int val = (ans[i + 1] >> h) & 1;
            if(val) {
                ans[i] |= (((v[i + 1][i] >> h) & 1) << h);
            }
            else {
                ans[i] |= ((((v[i][i + 1] >> h) & 1) << h) ^ (1 << h));
            }
        }
    }
}

int main() {

    n = i32();
    b = i32();

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            v[i][j] = i32();
        }
    }

    for(int i = 0; i < n - 1 && i < 4 - 1; i++) {
        solve2(i);
    }

    for(int i = 4; i < n; i++) {
        ans[i] = v[i][(4 - (i & 3)) & 3] ^ ans[(4 - (i & 3)) & 3];
    }

    afis();

    fclose(f);
    fclose(g);

    return 0;
}
