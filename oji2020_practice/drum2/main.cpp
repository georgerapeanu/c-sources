#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("drum2.in","r");
FILE *g = fopen("drum2.out","w");

inline int get_pos(int x,int y,int z){
    return (x - 1) * x * (2 * x - 1) / 6 + (y - 1) * x + (z - 1) + 1;
}

const int NMAX = 31;
const int SMAX = NMAX * (NMAX + 1) * (2 * NMAX + 1) / 6;

int n;

int v[SMAX + 5];
int dp[SMAX + 5];

int main(){

    fscanf(f,"%d",&n);

    for(int i = 1;i <= get_pos(n,n,n);i++){
        fscanf(f,"%d",&v[i]);
    }

    for(int i = n;i;i--){
        for(int j = i;j;j--){
            for(int k = i;k;k--){
                int pos = get_pos(i,j,k);
                int a = get_pos(i + 1,j + 1,k + 1);
                int b = get_pos(i + 1,j + 1,k);
                int c = get_pos(i + 1,j,k + 1);
                dp[pos] = v[pos] + max(dp[a],max(dp[b],dp[c]));
            }
        }
    }

    fprintf(g,"%d\n",dp[get_pos(1,1,1)]);

    int x = 1,y = 1;

    for(int i = 1;i <= n;i++){
        fprintf(g,"%d ",get_pos(i,x,y));
        int pos = get_pos(i,x,y);
        int a = get_pos(i + 1,x + 1,y + 1);
        int b = get_pos(i + 1,x + 1,y);
        int c = get_pos(i + 1,x,y + 1);

        if(dp[pos] - v[pos] == dp[c]){
            y++;
        }
        else if(dp[pos] - v[pos] == dp[b]){
            x++;
        }
        else{
            x++;
            y++;
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
