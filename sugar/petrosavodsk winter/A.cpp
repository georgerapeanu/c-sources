#include <cstdio>
#include <algorithm>

using namespace std;

const int SMAX = 3;
const int NMAX = 5;
const int inf = 1 << 28;

int n,s;
int dp[(SMAX + 1) * NMAX * 2 + 5][1 << (NMAX * 2)];
int standard[SMAX * 2 * NMAX + 5],num_standard;
int ultimate[NMAX * 2 + 5],num_ultimate;

int order[(SMAX + 1) * NMAX * 2 + 5];
int cnt[(1 << (NMAX * 2))];

inline int worst(int a,int b){
    if(a == inf){
        return b;
    }
    if(b == inf){
        return a;
    }
    return min(a,b);
}

inline int best(int a,int b){
    if(a == inf){
        return b;
    }
    if(b == inf){
        return a;
    }
    return max(a,b);
}

inline int sub(int a,int b){
    if(a == inf || b == inf){
        return inf;
    }
    return a - b;
}

inline int add(int a,int b){
    if(a == inf || b == inf){
        return inf;
    }
    return a + b;
}

inline int best_ult(int conf){
    return ultimate[2 * n + 1 - cnt[conf]];
}

inline int best_standard(int i,int conf){
    int id = 2 * n * (s + 1) - i - (2 * n - cnt[conf]) + 1;
    if(id <= 0 || id > num_standard){
        return inf;
    }
    return standard[id];
}

int main(){

    for(int i = 1;i < (1 << (2 * NMAX));i++){
        cnt[i] = (i & 1) + cnt[i >> 1];
    }

    for(int i = 0;i < (SMAX + 1) * NMAX * 2 + 5;i++){
        for(int j = 0;j < (1 << (NMAX * 2));j++){
            dp[i][j] = inf;
        }
    }

    scanf("%d %d",&n,&s);

    for(int i = 1;i <= (s + 1) * n * 2;i++){
        scanf("%d",&order[i]);
    }

    scanf("%d",&num_standard);

    for(int i = 1;i <= num_standard;i++){
        scanf("%d",&standard[i]);
    }

    scanf("%d",&num_ultimate);

    for(int i = 1;i <= num_ultimate;i++){
        scanf("%d",&ultimate[i]);
    }

    sort(standard + 1,standard + 1 + num_standard);
    reverse(standard + 1,standard + 1 + num_standard);
    sort(ultimate + 1,ultimate + 1 + num_ultimate);
    reverse(ultimate + 1,ultimate + 1 + num_ultimate);

    reverse(order + 1,order + 1 + (s + 1) *n * 2);
    
    dp[0][0] = 0;

    for(int i = 1;i <= (s + 1) * n * 2;i++){
        order[i]--;
        if(order[i] < n){
            for(int conf = 0;conf < (1 << (2 * n));conf++){
                if((conf >> order[i]) & 1){
                    dp[i][conf] = best(dp[i][conf],add(dp[i - 1][conf ^ (1 << order[i])], best_ult(conf)));
                }
                if(best_standard(i,conf) == inf){
                    continue;
                }
                dp[i][conf] = best(dp[i][conf],add(dp[i - 1][conf],best_standard(i,conf)));
            }
        }
        else{
            for(int conf = 0;conf < (1 << (2 * n));conf++){
                if((conf >> order[i]) & 1){
                    dp[i][conf] = worst(dp[i][conf],sub(dp[i - 1][conf ^ (1 << order[i])],best_ult(conf)));
                }
                if(best_standard(i,conf) == inf){
                    continue;
                }
                dp[i][conf] = worst(dp[i][conf],sub(dp[i - 1][conf],best_standard(i,conf)));
            }
        }
    }

    printf("%d\n",dp[(s + 1) * n * 2][(1 << (2 * n)) - 1]);

    return 0;
}
