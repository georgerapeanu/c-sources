#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("rover.in","r");
FILE *g = fopen("rover.out","w");

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

    if(v[n][m] != -1){
        ok[n][m] = true;
        if(p == 1){
            dp[n][m] = 1;
        }
        else if(p == 2){
            dp[n][m] = 1;
        }
        else{
            dp[n][m] = v[n][m];
        }
    }
    else{
        ok[n][m] = false;
        if(p == 1){
            dp[n][m] = smax;
        }
        else if(p == 2){
            dp[n][m] = 0;
        }
        else{
            dp[n][m] = -smax;
        }
    }

    for(int i = n;i > 0;i--){
        for(int j = m;j > 0;j--){
            if(i != n || j != m){
                if(v[i][j] != -1){
                    ok[i][j] = (ok[i + 1][j] | ok[i + 1][j + 1] | ok[i][j + 1]);
                    if(p == 1){
                        dp[i][j] = smax;
                        if(i + 1 <= n && ok[i + 1][j]){
                            dp[i][j] = min(dp[i][j],dp[i + 1][j]);
                        }
                        if(i + 1 <= n && j + 1 <= m && ok[i + 1][j + 1]){
                            dp[i][j] = min(dp[i][j],dp[i + 1][j + 1]);
                        }
                        if(j + 1 <= m && ok[i][j + 1]){
                            dp[i][j] = min(dp[i][j],dp[i][j + 1]);
                        }
                        dp[i][j]++;
                    }
                    else if(p == 2){
                        dp[i][j] = 0;
                        if(i + 1 <= n && ok[i + 1][j]){
                            dp[i][j] = adun(dp[i][j],dp[i + 1][j]);
                        }
                        if(i + 1 <= n && j + 1 <= m && ok[i + 1][j + 1]){
                            dp[i][j] = adun(dp[i][j],dp[i + 1][j + 1]);
                        }
                        if(j + 1 <= m && ok[i][j + 1]){
                            dp[i][j] = adun(dp[i][j],dp[i][j + 1]);
                        }
                    }
                    else{
                        dp[i][j] = -smax;
                        if(i + 1 <= n && ok[i + 1][j]){
                            dp[i][j] = max(dp[i][j],dp[i + 1][j]);
                        }
                        if(i + 1 <= n && j + 1 <= m && ok[i + 1][j + 1]){
                            dp[i][j] = max(dp[i][j],dp[i + 1][j + 1]);
                        }
                        if(j + 1 <= m && ok[i][j + 1]){
                            dp[i][j] = max(dp[i][j],dp[i][j + 1]);
                        }
                        dp[i][j] += v[i][j];
                    }
                }
            }
        }
    }

    if(ok[1][1] == false){
        fprintf(g,"nu exista traseu\n");
        return 0;
    }

    if(p == 1){
        fprintf(g,"%d\n",dp[1][1]);

        int x = 1,y = 1;

        while(x != n || y != m){
            fprintf(g,"%d %d\n",x,y);
            if(ok[x][y + 1] && dp[x][y + 1] + 1 == dp[x][y]){
                y++;
            }
            else if(ok[x + 1][y] && dp[x + 1][y] + 1 == dp[x][y]){
                x++;
            }
            else{
                x++;
                y++;
            }
        }
        fprintf(g,"%d %d\n",x,y);
    }
    else{
        fprintf(g,"%d\n",dp[1][1]);
    }

    fclose(f);
    fclose(g);

    return 0;
}
