#include <bits/stdc++.h>

using namespace std;

int gcd(int a,int b){
    if(!b)return a;
    return gcd(b,a % b);
}

vector<int> get_query(int n,int g,mt19937 &rng){
    assert(n % g == 0);

    n /= g;

    if(n == 1){
        return {g};
    }

    vector<int> primes;

    for(int i = 2;1LL * i * i <= n;i++){
        if(n % i == 0){
            primes.push_back(i);
            while(n % i == 0){
                n /= i;
            }
        }
    }

    if(n != 1){
        primes.push_back(n);
        n /= n;
    }
    
    int MASK_ALL = (1 << ((int)primes.size())) - 1;

    vector<int> confs;

    int minimum_primes = (rng() % (int)primes.size()) + 1;

    for(int i = 0;i <= (int)MASK_ALL;i++){
        if(__builtin_popcount(i) >= minimum_primes){
            confs.push_back(i);
        }
    }

    shuffle(confs.begin(),confs.end(),rng);

    int low = confs.size() / 2;
    int high = (int)confs.size() - 1;

    confs.resize((rng() % (high - low + 1)) + low + 1);

    vector<int> answer;

    int mask = MASK_ALL;
    for(auto it:confs){
        mask &= it;
        int p = 1;
        for(int i = 0;i < (int)primes.size();i++){
            if((it >> i) & 1){
                p *= primes[i];
            }
        }
        answer.push_back(p);
    }

    if(mask != 0){
        int conf = (MASK_ALL ^ mask);
        int p = 1;
        for(int i = 0;i < (int)primes.size();i++){
            if((conf >> i) & 1){
                p *= primes[i];
            }
        }
        answer.push_back(p);
    }

    sort(answer.begin(),answer.end());

    for(auto &it:answer){
        it *= g;
    }
    
    int actual_gcd = 0;

    for(auto it:answer){
        actual_gcd = gcd(actual_gcd,it);
    }

    assert(actual_gcd == g);

    return answer;
}

int main(){
    
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    vector<int> query = get_query(83160,1,rng);

    for(auto it:query){
       printf("%d ",it); 
    }

    return 0;
}
