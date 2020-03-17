#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("seif.in","r");
FILE *g = fopen("seif.out","w");

const int TMAX = 10;
const int NMAX = 1000;
const int SIGMA = 'z' - 'a' + 1;


int t;
char a[NMAX + 5];
char b[NMAX + 5];
int len_a,len_b;
int nxt_a[NMAX + 5][SIGMA + 5];
int nxt_b[NMAX + 5][SIGMA + 5];

int dp[NMAX + 5][NMAX + 5];

int main(){

    fscanf(f,"%d\n",&t);

    while(t--){
        int k;
        fscanf(f,"%d\n",&k);
        fgets(a + 1,NMAX + 5,f);len_a = strlen(a + 1);len_a -= (a[len_a] == '\n');
        fgets(b + 1,NMAX + 5,f);len_b = strlen(b + 1);len_b -= (b[len_b] == '\n');

        for(int i = len_a;i;i--){
            for(int j = 0;j < SIGMA;j++){
                nxt_a[i][j] = (i < len_a ? nxt_a[i + 1][j]:-1);
            }
            nxt_a[i][a[i] - 'A'] = i;
        }

        for(int i = len_b;i;i--){
            for(int j = 0;j < SIGMA;j++){
                nxt_b[i][j] = (i < len_b ? nxt_b[i + 1][j]:-1);
            }
            nxt_b[i][b[i] - 'A'] = i;
        }

        for(int i = len_a;i;i--){
            for(int j = len_b;j;j--){
                if(a[i] == b[j]){
                    dp[i][j] = 1 + (i < len_a && j < len_b ? dp[i + 1][j + 1]:0);
                }
                else{
                    dp[i][j] = max((i < len_a ? dp[i + 1][j]:0),(j < len_b ? dp[i][j + 1]:0));
                }
            }
        }

        int x = 1;
        int y = 1;
        bool ok = true;

        while(ok && x <= len_a && y <= len_b){
            ok = false;
            for(int c = 'z' - 'a';c >= 0;c--){
                if(nxt_a[x][c] != -1 && nxt_b[y][c] != -1 && dp[nxt_a[x][c]][nxt_b[y][c]] >= k){
                    fprintf(g,"%c",c + 'A');
                    x = nxt_a[x][c] + 1;
                    y = nxt_b[y][c] + 1;
                    k--;
                    ok = true;
                    break;
                }
            }
        }
        fprintf(g,"\n");
    }

    fclose(f);
    fclose(g);

    return 0;
}
