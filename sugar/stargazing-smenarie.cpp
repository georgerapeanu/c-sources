#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>

using namespace std;

const int QMAX = 1e5;
const long long NMAX = 1e12;
const long long __CBRT = 1e4;
const long long DIVMAX = __CBRT;
const long long MOD = 1e9 + 7;

long long n;
int q;
pair<long long,int> v[QMAX + 5];

long long gcd(long long a,long long b){
    if(b == 0){
        return a;
    }
    return gcd(b,a % b);
}

vector<pair<long long,int> > fact;
vector<long long> divs;///last 2 bits for config
int frei_bittung = 0;

bool bad_center[DIVMAX + 5];
long long last_left[DIVMAX + 5];
long long first_right[DIVMAX + 5];

vector<long long> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

long long lgmult(long long a,long long b,long long MOD){
    long long ans = 0;
    while(b){
        if(b & 1){
            ans += a;
            if(ans >= MOD){
                ans -= MOD;
            }
        }
        a <<= 1;
        if(a >= MOD){
            a -= MOD;
        }
        b >>= 1;
    }
    return ans;
}

long long lgpow(long long b,long long e,long long MOD){
    long long p = 1;

    while(e){
        if(e & 1){
            p = lgmult(p,b,MOD);
        }
        b = lgmult(b,b,MOD);
        e >>= 1;
    }

    return p;
}

bool is_prime(long long a){
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

void make_divs(int pas,long long d){
    if(pas >= (int)fact.size()){
        for(int conf = 0;conf < (1 << frei_bittung);conf++){
            long long tmpd = ((d << frei_bittung) | conf);
            divs.push_back(tmpd);
        }
        return ;
    }
    for(int k = 0;k <= fact[pas].second;k++){
        make_divs(pas + 1,d);
        d *= fact[pas].first;
    }
}

int main(){

    scanf("%lld %d",&n,&q);

    for(int i = 1;i <= q;i++){
        scanf("%d %lld",&v[i].second,&v[i].first);
    }
 
    sort(v + 1,v + 1 + q);

    vector<long long> left,center,right;

    long long g = 0;
    long long fst_one = -1;
    long long lst_one = -1;

    for(int i = 1;i <= q;i++){
        if(v[i].second == 1){
            if(fst_one == -1){
                fst_one = v[i].first;
            }
            lst_one = v[i].first;
            g = gcd(g,lst_one - fst_one);
        }
    }

    for(int i = 1;i <= q;i++){
        if(v[i].second == 0){
            if(v[i].first < fst_one){
                left.push_back(v[i].first);
            }
            else if(v[i].first < lst_one){
                center.push_back(v[i].first);
            }    
            else{
                right.push_back(v[i].first);
            }
        }
    }

    long long bg = g;

    for(int d = 2;d <= __CBRT;d++){
        if(g % d == 0){
            fact.push_back({d,0});
            while(g % d == 0){
                g /= d;
                fact.back().second++;
            }
        }
    }

    if(g != 1){
        long long rt = sqrt(g);
        if(rt * rt == g){
            fact.push_back({rt,2});
            frei_bittung = 0;
            g = 1;
        }
        else if(is_prime(g)){
            fact.push_back({g,1});
            frei_bittung = 0;
            g = 1;
        }
        else{
            bool found = false;

            for(auto it:left){
                if(found){
                    break;
                }
                long long d = gcd(g,fst_one - it);
                if(d != g && d != 1){
                    fact.push_back({d,1});
                    fact.push_back({g / d,1});
                    found = true;
                }
            }
            for(auto it:center){
                if(found){
                    break;
                }
                long long d = gcd(g,it - fst_one);
                if(d != g && d != 1){
                    fact.push_back({d,1});
                    fact.push_back({g / d,1});
                    found = true;
                }
            }
            for(auto it:right){
                if(found){
                    break;
                }
                long long d = gcd(g,it - fst_one);
                if(d != g && d != 1){
                    fact.push_back({d,1});
                    fact.push_back({g / d,1});
                    found = true;
                }
            }
            g = (found == false ? g:1);
            frei_bittung = 2 * (found == false);
        }
    }

    make_divs(0,1);
    sort(divs.begin(),divs.end());
    long long gp = g;
    g = bg;

    unordered_map<long long,int> remap;

    for(int i = 0;i < (int)divs.size();i++){
        remap[divs[i]] = i;
        last_left[i] = 0;
        first_right[i] = n + 1;
        bad_center[i] = false;
    }

    for(auto it:left){
        long long val = gcd(g,fst_one - it);
        int d = remap[(val << frei_bittung) + ((1 << frei_bittung) - 1) * (val % gp == 0)];
        last_left[d] = max(last_left[d],it);
    }

    for(auto it:center){
        long long val = gcd(g,it - fst_one);
        int d = remap[(val << frei_bittung) + ((1 << frei_bittung) - 1) * (val % gp == 0)];
        bad_center[d] = true;
    }

    for(auto it:right){
        long long val = gcd(g,it - fst_one);
        int d = remap[(val << frei_bittung) + ((1 << frei_bittung) - 1) * (val % gp == 0)];
        first_right[d] = min(first_right[d],it);
    }

    for(int i = (int)divs.size() - 1;i >= 0;i--){
        long long d = (divs[i] >> frei_bittung);
        int config = divs[i] & ((1 << frei_bittung) - 1);
        for(auto it:fact){
            long long td;

            if(d <= NMAX / it.first + 1){
                td = d * it.first;
            }
            else{
                td = NMAX;
            }

            td <<= frei_bittung;

            for(int tconf = config;tconf < (1 << frei_bittung);tconf = (config) | (tconf + 1)){
                td += tconf;
                if(remap.count(td)){
                    int ti = remap[td];
                    bad_center[i] |= bad_center[ti];
                    last_left[i] = max(last_left[i],last_left[ti]);
                    first_right[i] = min(first_right[i],first_right[ti]);
                }
                td -= tconf;
            }
        }
    }

    long long ans = 0;

    for(int i = 0;i < (int)divs.size();i++){
        if(bad_center[i]){
            continue;
        }

        long long st = (fst_one - last_left[i] - 1) / divs[i] + 1;
        long long dr = (first_right[i] - lst_one - 1) / divs[i] + 1;
        ans += 1LL * (st % MOD) * (dr % MOD) % MOD;
        if(ans >= MOD){
            ans -= MOD;
        }
    }
    
    printf("%lld",ans);

    return 0;
}
