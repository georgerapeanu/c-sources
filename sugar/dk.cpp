#include <cstdio>
#include <vector>
 
using namespace std;
 
FILE *f = fopen("dk.in","r");
FILE *g = fopen("dk.out","w");
 
vector<int> primes = {2,3, 61};
 
int lgpow(int b,int e,int MOD){
    int p = 1;
 
    while(e){
        if(e & 1){
            p = 1LL * p * b % MOD;
        }
        e >>= 1;
        b = 1LL * b * b % MOD;
    }
 
    return p;
}
 
int n;
 
bool is_prime(int a){
    if(a <= 1){
        return false;
    }
    for(auto it:primes){
        if(a <= it){
            return true;
        }
        if(lgpow(it,a - 1,a) != 1){
            return false;
        }
    }
    return true;
}

 
int main(){
 
    fscanf(f,"%d",&n);
 
    int cnt = 0;
    while(n--){
        int x;
        fscanf(f,"%d",&x);
        cnt += is_prime(x);
    }
 
    fprintf(g,"%d\n",cnt);
 
    fclose(f);
    fclose(g);
    return 0;
}
