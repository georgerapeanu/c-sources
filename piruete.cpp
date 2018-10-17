#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("piruete.in","r");
FILE *g = fopen("piruete.out","w");

const int MOD = 1e9+7;

int add(int a,int b){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
    return a;
}

int mult(int a,int b){
    return 1LL * a * b % MOD;
}

int t,n,k;

int delta[2][105][105][105];
int dp[2][105][105][105];

int main(){
    fscanf(f,"%d %d %d",&t,&n,&k);

	t /= 2;
	
    dp[0][0][0][0] = 1;
    int ans = 0;

    for(int i = 0,l = 0;i < k;i++,l ^= 1){
        for(int j = i * (i + 1) / 2;j <= t;j++){
            for(int x = i / 2;x <= n + 1;x++){
                for(int y = i / 2 + (i % 2);y <= n + 1;y++){
					if(j + min(x + 1,n + 1) <= 100){
						delta[l ^ 1][j + min(x + 1,n + 1)][y][min(x + 1,n + 1)] = add(delta[l ^ 1][j + min(x + 1,n + 1)][y][min(x + 1,n + 1)],dp[l][j][x][y]);
					}
					
                    delta[l][j][x][y] = 0;
                }
            }
        }

        for(int j = (i + 1) * (i + 2) / 2;j <= t;j++){
            for(int x = (i + 1) / 2;x <= n + 1;x++){
                for(int y = (i + 1)/ 2 + ((i + 1) % 2);y <= n + 1;y++){
                    if(j && y){
                        dp[l ^ 1][j][x][y] = add(delta[l ^ 1][j][x][y],dp[l ^ 1][j - 1][x][y - 1]);
                    }
                }
            }
        }
		
		int init = ans;
		
		for(int x = 0;x <= n + 1;x++){
			for(int y = 0;y <= n + 1;y++){
				ans = add(ans,dp[l ^ 1][t][x][y]);
			}
		}
		printf("%d\n",ans - init);
    }


    fprintf(g,"%d",ans);

    fclose(f);
    fclose(g);

    return 0;
}
