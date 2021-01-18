#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("media.in","r");
FILE *g = fopen("media.out","w");

const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;

struct hsh_t{
    int h1,h2;

    hsh_t(){
        h1 = h2 = 1;
    }

    hsh_t(int val){
        this->h1 = val % MOD1;
        this->h2 = val % MOD2;
    }

    hsh_t operator * (const hsh_t &other)const{
        hsh_t ans;

        ans.h1 = 1LL * this->h1 * other.h1 % MOD1;
        ans.h2 = 1LL * this->h2 * other.h2 % MOD2;

        return ans;
    }

    bool operator < (const hsh_t &other)const{
        if(h1 != other.h1){
            return h1 < other.h1;
        }else{
            return h2 < other.h2;
        }
    }
};

int lgpow(int b,int e,int mod){
    int p = 1;

    while(e){
        if(e & 1){
            p = 1LL * p * b % mod;
        }
        b = 1LL * b * b % mod; 
        e >>= 1;
    }

    return p;
}

int n;
int m;
hsh_t pref[50005];

long long get_good(int lst){
    sort(pref + 0,pref + 1 + lst);

    long long ans = 0;
    int len = 0;

    for(int i = 0;i <= lst;i++){
        if(i != 0 && pref[i - 1] < pref[i]){
            ans += len * (len - 1) / 2;
            len = 0;
        }
        len++;
    }
    
    ans += len * (len - 1) / 2;

    return ans;
}

int main(){
   
    fscanf(f,"%d %d",&n,&m);

    pref[0] = hsh_t();

    hsh_t inv;
    inv.h1 = lgpow(m,MOD1 - 2,MOD1);
    inv.h2 = lgpow(m,MOD2 - 2,MOD2);

    int lst = 0;
    long long ans = 0;

    for(int i = 1;i <= n;i++){
        int val;
        fscanf(f,"%d",&val);
        if(val == 0){
            ans += get_good(lst);
            lst = 0;
        }
        else{
            lst++;
            pref[lst] = pref[lst - 1] * hsh_t(val) * inv;
        }
    }

    ans += get_good(lst);

    fprintf(g,"%lld\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
