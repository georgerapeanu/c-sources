#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("ciocolata.in","r");
FILE *g = fopen("ciocolata.out","w");

const int LGMAX = 16;

int t;
int dp[1 << LGMAX][2];

int main(){

    for(int conf = 0;conf < (1 << 15);conf++){
        dp[conf][0] = 1 << 28;
        dp[conf][1] = -(1 << 28);
    }

    dp[0][0] = 0;
    dp[0][1] = 0;

    for(int conf = 1;conf < (1 << 15);conf++){
        for(int i = 0;i < 15;i++){
            if((conf >> i) & 1){
                if(i == 0){
                    dp[conf][0] = min(dp[conf][0],dp[conf ^ 1][1] + 2);
                    dp[conf][1] = max(dp[conf][1],dp[conf ^ 1][0] - 2);
                }
                else{
                    dp[conf][0] = min(dp[conf][0],dp[conf ^ (1 << i) ^ (1 << (i - 1))][1] + 1);
                    dp[conf][1] = max(dp[conf][1],dp[conf ^ (1 << i) ^ (1 << (i - 1))][0] - 1);
                    for(int j = 2;j <= i;j++){
                        int nconf = conf ^ (1 << i);
                        nconf ^= (1 << (j - 2));
                        nconf ^= (1 << (i - j));
                        dp[conf][0] = min(dp[conf][0],dp[nconf][1]);        
                        dp[conf][1] = max(dp[conf][1],dp[nconf][0]);
                    }
                }
            }
        }
    }

    fscanf(f,"%d",&t);

    while(t--){
        int sum = 0;
        int conf = 0;
        for(int i = 0;i < 15;i++){
            int x;
            fscanf(f,"%d",&x);
            sum += x * (i + 2);
            conf |= ((x & 1) << i);
        }
        fprintf(g,"%d %d\n",(sum + dp[conf][0]) / 2,(sum - dp[conf][0]) / 2);
    }

    fclose(f);
    fclose(g);

    return 0;
}
