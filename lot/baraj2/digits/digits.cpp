#include <bits/stdc++.h>

using namespace std;

const int NMAX = 18;
const int MOD = 1e9 + 7;

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

int n,m,b;
int s;
int dp[NMAX + 5][2];

struct restriction_t{
    int i,j;
    int k;
    bool type;
};

vector<restriction_t> r;

int pw[] = {
    1,
    10,
    100,
    1000,
    10000,
    100000,
    1000000
};

int get_digit(int val,int x){
    return (val / pw[x]) % 10;
}

int main(){

    scanf("%d %d %d",&n,&m,&b);

    for(int i = 1;i <= n;i++){
        int val;
        scanf("%d",&val);
        s = s * b + val;
    }

    for(int i = 1;i <= m;i++){
        int _i,_j,_k;
        char c;
        scanf("%d %c %d %d",&_i,&c,&_j,&_k);
        r.push_back({_i,_j,_k,(c == '+')});
    }

    int ans = 0;

    for(int a = 0;a <= s;a++){
        int b = s - a;
        if(a < pw[n - 1] || b < pw[n - 1]){
            continue;
        }
        bool ok = true;
        for(auto it:r){
            int _a = get_digit(a,it.i);
            int _b = get_digit(b,it.j);
            if(it.type == 0){
                ok &= (_a - _b == it.k);
            }else{
                ok &= (_a + _b == it.k);
            }
        }
        ans += ok;
    }

    printf("%d\n",ans);
   
    return 0;
}
