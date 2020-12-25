#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e3;

int n,m,k;
vector<pair<int,int> > segm;

long long _a[NMAX + 5];
long long _b[NMAX + 5];

void reset(){
    for(int i = 1;i <= n;i++){
        _a[i] = _b[i] = 0;
    }
}

void update(int st,int dr,long long a,long long b){
    if(st < 1){
        b += a * (1 - st);
        st = 1;
    }
    if(dr > n){
        dr = n;
    }
    
    if(dr < st){
        return ;
    }

    _a[st] += a;
    _a[dr + 1] -= a;
    _b[st] += b;
    _b[dr + 1] -= b;
    _b[st] -= a * st;
    _b[dr + 1] += a * st;
}

void calculate(){
    for(int i = 1;i <= n;i++){
        _a[i] += _a[i - 1];
        _b[i] += _b[i - 1];
    }
}

long long get_val(int pos){
    return 1LL * _a[pos] * pos + _b[pos];
}

int main(){

    scanf("%d %d %d",&n,&m,&k);

    segm = vector<pair<int,int> > (m,{0,0});
    
    for(auto &it:segm){
        scanf("%d %d",&it.first,&it.second);
    }

    long long ans = 0;

    for(int i = 1;i <= n - k + 1;i++){
        reset();
        for(auto it:segm){
            int curr_cost = max(0,min(it.second,i + k - 1) - max(it.first,i) + 1);
            int l = it.first;
            int r = it.second - k + 1;
            int ceil_cost = min(it.second - it.first + 1,k);
            if(r < l){
                swap(l,r);
            }

            int delta = ceil_cost - curr_cost;

            update(1,l - delta,0,curr_cost);
            update(l - delta + 1,l,1,curr_cost + 1);
            update(l + 1,r,0,ceil_cost);
            update(r + 1,r + delta,-1,ceil_cost - 1);
            update(r + delta + 1,n,0,curr_cost);
        }

        calculate();

        long long local_ans = 0;
        for(int j = 1;j <= n;j++){
            local_ans = max(local_ans,get_val(j));
        }
        ans = max(local_ans,ans);
    }

    printf("%lld\n",ans);


    return 0;
}
