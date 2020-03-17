#include <iostream>
#include <cstdio>
#include <stack>
#define MOD 666013
using namespace std;

int cul[100006];
char C[100006];
int nr=0,N,M;
int ind=1;

int invM;
int invM1;

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

pair<int,int> compose(pair<int,int> dp,pair<int,int> tmp){
    pair<int,int> dp2 = {0,0};
    dp2.second = add(dp2.second,mult(mult(dp.first,tmp.first),mult(M - 1,invM)));
    dp2.first = add(dp2.first,mult(mult(dp.first,tmp.second),mult(1,invM)));
    dp2.second = add(dp2.second,mult(mult(dp.first,tmp.second),mult(M - 2,invM)));
    dp2.first = add(dp2.first,mult(mult(dp.second,tmp.first),mult(1,invM)));
    dp2.second = add(dp2.second,mult(mult(dp.second,tmp.first),mult(M - 2,invM)));
    dp2.first = add(dp2.first,mult(mult(dp.second,tmp.second),mult(mult(1,invM),mult(M - 2,invM1))));
    dp2.second = add(dp2.second,mult(mult(dp.second,tmp.second),mult(mult(1,invM),add(M - 2,invM1))));
    return dp2;
}

pair<int,int> dfs()
{
    if(C[ind]==')')
    {
        ind++;
        return {0,mult(M,M - 1)};
    }

    pair<int,int> dp = {-1,-1};
    while(C[ind]!=')')
    {
        ind++;
        pair<int,int> tmp=dfs();
        if(dp.first == -1){
            dp = tmp;
        }
        else{
            dp = compose(dp,tmp);
        }
    }

    pair<int,int> dp2 = {0,0};

    dp2.first = 0;
    dp2.second = add(dp2.second,mult(mult(M - 2,M - 1),dp.first));
    dp2.second = add(dp2.second,mult(add(M - 1,mult(M - 2,M - 2)),dp.second));
    dp = dp2;

    ind++;
    return dp;
}
int main()
{
    freopen("spirt.in","r",stdin);
    freopen("spirt.out","w",stdout);
    cin>>N>>M;
    cin.getline(C+1,1000006);
    cin.getline(C+1,1000006);
    ind=1;
    invM = lgpow(M,MOD - 2);
    invM1 = lgpow(M - 1,MOD - 2);
    bool fst=1;
    pair<int,int> dp = {-1,-1};
    while(ind<=N)
    {
        ind++;
        pair<int,int> tmp=dfs();
        if(dp.first == -1){
            dp = tmp;
        }
        else{
            dp = compose(dp,tmp);
        }

    }
    cout<<add(dp.first,dp.second);
    return 0;
}
