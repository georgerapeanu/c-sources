#include "coolrot.h"
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 1e5;
const int QMAX = 1e5;

int _n;
int v[NMAX];
int best_shift[NMAX];
long long cnt_inversions[NMAX];

int aib[NMAX + 5];

void aib_update(int pos,int val){
    pos++;
    for(;pos <= _n;pos += (-pos) & pos){
        aib[pos] += val;
    }
}

int aib_query(int pos){
    pos++;
    int ans = 0;
    for(;pos;pos -= (-pos) & pos){
        ans += aib[pos];
    }
    return ans;
}

void init(int n,const int a[],int q){
    _n = n;
    for(int i = 0;i < _n;i++){
        v[i] = a[i];
    }

    long long inv = 0;

    for(int i = 0;i < _n;i++){
        inv += i - aib_query(v[i]);
        aib_update(v[i],1);
    }

    for(int i = 0;i < _n;i++){
        cnt_inversions[i] = inv;
        inv += (-v[i]) + (n - 1 - v[i]);
    }

    for(int h = 1;h < _n;h++){
        best_shift[h] = -1;
        for(int i = 0;i < _n;i += h){
            if(best_shift[h] == -1 || make_pair(cnt_inversions[best_shift[h]],v[best_shift[h]]) > make_pair(cnt_inversions[i],v[i])){
                best_shift[h] = i;
            }
        }
    }
}

int add(int a,int b,int mod){
    a += b;
    if(a >= mod){
        a -= mod;
    }
    return a;
}

int scad(int a,int b,int mod){
    a -= b;
    if(a < 0){
        a += mod;
    }
    return a;
}

int mult(int a,int b,int mod){
    return 1LL * a * b % mod;
}

int gcd(int a,int b,int &x,int &y){
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }

    int g = gcd(b,a % b,x,y);

    int _x,_y;

    _x = y;
    _y = scad(x,mult((a / b),y,_n),_n);

    x = _x;
    y = _y;

    return g;
}

void query(int m,const int ds[]){

    vector<pair<int,int> > coef(m);

    coef[0] = {1,1};

    int g = ds[0];

    for(int i = 1;i < m;i++){
        int x,y;
        g = gcd(g,ds[i],x,y);

        coef[i - 1].second = mult(coef[i - 1].second,x,_n);
        coef[i] = {y,1};
    }

    for(int i = m - 1;i >= 0;i--){
        if(i < m - 1){
            coef[i].second = mult(coef[i].second,coef[i + 1].second,_n);
        }
        coef[i].first = mult(coef[i].first,coef[i].second,_n);
    }

    if(g == _n){
        return ;
    }

    int target = best_shift[g];
    
    for(int i = 0;i < m;i++){
        coef[i].first = mult(coef[i].first,target / g,_n);
        coef[i].first %= (_n / ds[i]);
        if(coef[i].first){
            update(ds[i],coef[i].first);
        }
    }

    return ;
}
