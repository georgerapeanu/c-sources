#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e5;
const int VMAX = 1e6;
const int BASE = 2;
const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;

int pw1[VMAX + 5];
int pw2[VMAX + 5];

inline int add(int a,int b,int MOD){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
    return a;
}

struct hash_t{
    int h1,h2;

    hash_t(){
        h1 = h2 = 0;
    }

    void set(int pos){
        h1 = add(h1,pw1[pos],MOD1);
        h2 = add(h2,pw2[pos],MOD2);
    }
    
    bool operator < (const hash_t &other)const{
        if(h1 != other.h1){
            return h1 < other.h1; 
        }
        return h2 < other.h2;
    }

    bool operator == (const hash_t &other)const{
        return h1 == other.h1 && h2 == other.h2;
    }
    
    bool operator != (const hash_t &other)const{
        return !(h1 == other.h1 && h2 == other.h2);
    }
};

int t;
int n;
int q;

hash_t hsh[VMAX + 5];
bool not_prime[VMAX + 5];

int main(){

    pw1[0] = pw2[0] = 1;

    for(int i = 1;i <= VMAX;i++){
        pw1[i] = 1LL * BASE * pw1[i - 1] % MOD1;
        pw2[i] = 1LL * BASE * pw2[i - 1] % MOD2;
    }

    int cnt_primes = 0;

    not_prime[0] = not_prime[1] = true;

    for(int i = 2;i <= VMAX;i++){
        if(not_prime[i] == false){
            cnt_primes++;
            for(int j = i;j <= VMAX;j += i){
                if(j != i){
                    not_prime[j] = true;
                }
                int tmp = j;
                int exp = 0;
                while(tmp % i == 0){
                    tmp /= i;
                    exp ^= 1;
                }
                if(exp == 1){
                    hsh[j].set(cnt_primes - 1);
                }
            }
        }
    }

    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);

        vector<hash_t> hashes;

        for(int i = 1;i <= n;i++){
            int value;
            scanf("%d",&value);
            hashes.push_back(hsh[value]);
        }
        sort(hashes.begin(),hashes.end());

        int len = 0;
        int ans_zero = 0;
        int maximal_zero_group = 0;

        for(int i = 0;i < (int)hashes.size();i++){
            if(i == 0 || hashes[i - 1] != hashes[i]){
                ans_zero = max(ans_zero,len);
                if(len % 2 == 0 || (i != 0 && hashes[i - 1].h1 == 0 && hashes[i - 1].h2 == 0)){
                    maximal_zero_group += len;
                }
                len = 0;
            }
            len++;
        }
        
        ans_zero = max(ans_zero,len);
        if(len % 2 == 0 || hashes[(int)hashes.size() - 1].h1 == 0 && hashes[(int)hashes.size() - 1].h2 == 0){
            maximal_zero_group += len;
        }
        len = 0;
        int ans_nonzero = max(ans_zero,maximal_zero_group);

        scanf("%d",&q);

        while(q--){
            long long w;
            scanf("%lld",&w);
            if(w == 0){
                printf("%d\n",ans_zero);
            }else{
                printf("%d\n",ans_nonzero);
            }
        }

    }

    return 0;
}
