#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
const int NMAX = 250000;

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

int lgpow(int b,int e){
    int p = 1;
    
    while(e){
        if(e & 1){
            p = mult(p,b);
        }
        b = mult(b,b);
        e >>= 1;
    }

    return p;
}

int n,k;
int v[NMAX + 5];
int cnt_lower[NMAX + 5];
int ans = 1;

int main(){
    scanf("%d %d",&n,&k);

    for(int i = 1;i <= k;i++){
        scanf("%d",&v[i]);
    }

    for(int i = 1;i < k;i++){
        if(v[i] > v[i + 1]){
            for(int j = i + 1;j <= k;j++){
                cnt_lower[v[j]]++;
            }
            for(int i = 1;i <= n;i++){
                cnt_lower[i] += cnt_lower[i - 1];
            }
            for(int j = 1;j <= i;j++){
                v[j] -= cnt_lower[v[j]];
            }
            n -= (k - i);
            k = i;
            break;
        }
    }

    if(v[1] != 1){
        ans = 0;
    }else{
        for(int i = 2;i <= k;i++){
            for(int val = v[i - 1] + 1;val < v[i];val++){
                ans = mult(ans,val - 1);
            }
        }

        for(int val = v[k] + 1;val <= n;val++){
            ans = mult(ans,val);
        }
    }

    printf("%d\n",ans);
    
    return 0;    
}
