#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("in","r");
FILE *g = fopen("out","r");

const int NMAX = 1000;
const int MMAX = 1000;
const int MOD = 100003;

const int smax = 1000000000;

int p;
int n,m;
int v[NMAX + 5][MMAX +5];
bool ok[NMAX + 5][MMAX + 5];
int dp[NMAX + 5][MMAX + 5];

int adun(int a,int b){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
    return a;
}

const int LEN = 1 << 12;
int pind = LEN - 1;
char buff[LEN];

int parsare_int(){
    int sgn = 1;
    int ans = 0;

    while((buff[pind] != '-') && (buff[pind] < '0' || buff[pind] > '9')){
        if(++pind >= LEN){
            pind = 0;
            fread(buff,1,LEN,f);
        }
    }

    if(buff[pind] == '-'){
        sgn *= -1;
        if(++pind >= LEN){
            pind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while(!(buff[pind] < '0' || buff[pind] > '9')){
        ans = ans * 10 + (buff[pind] - '0');
        if(++pind >= LEN){
            pind = 0;
            fread(buff,1,LEN,f);
        }
    }

    return ans * sgn;
}

int main(){

    p = parsare_int();
    n = parsare_int();
    m = parsare_int();

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            v[i][j] = parsare_int();
        }
    }

    int cnt;

    fscanf(g,"%d",&cnt);

    while(cnt--){
        int x,y;
        fscanf(g,"%d %d",&x,&y);
        if(v[x][y] == -1){
            printf("muieeeeee %d %d\n",x,y);
        }
    }

    printf("okboss");

    fclose(f);
    fclose(g);

    return 0;
}
