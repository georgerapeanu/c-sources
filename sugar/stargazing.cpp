#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

const int QMAX = 1e5;
const long long NMAX = 1e12;
const long long DIVMAX = 1e4;
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

vector<long long> fact;
vector<long long> divs;

bool bad_center[DIVMAX + 5];
long long last_left[DIVMAX + 5];
long long first_right[DIVMAX + 5];

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

    for(int d = 1;1LL * d * d <= g;d++){
        if(g % d == 0){
            divs.push_back(d);
            if(g / d != d){
                divs.push_back(g / d);
            }
        }
    }

    sort(divs.begin(),divs.end()); 
    
    for(int d = 2;1LL * d * d <= g;d++){
        if(g % d == 0){
            fact.push_back(d);
            while(g % d == 0){
                g /= d;
            }
        }
    }

    if(g != 1){
        fact.push_back(g);
    }

    g = bg;

    unordered_map<long long,int> remap;

    for(int i = 0;i < (int)divs.size();i++){
        remap[divs[i]] = i;
        last_left[i] = 0;
        first_right[i] = n + 1;
        bad_center[i] = false;
    }

    for(auto it:left){
        int d = remap[gcd(g,fst_one - it)];
        last_left[d] = max(last_left[d],it);
    }

    for(auto it:center){
        int d = remap[gcd(g,it - fst_one)];
        bad_center[d] = true;
    }

    for(auto it:right){
        int d = remap[gcd(g,it - lst_one)];
        first_right[d] = min(first_right[d],it);
    }

    for(int i = (int)divs.size() - 1;i >= 0;i--){
        long long d = divs[i];
        for(auto it:fact){
            long long td;

            if(d <= NMAX / it + 1){
                td = d * it;
            }
            else{
                td = NMAX;
            }

            if(remap.count(td)){
                int ti = remap[td];
                bad_center[i] |= bad_center[ti];
                last_left[i] = max(last_left[i],last_left[ti]);
                first_right[i] = min(first_right[i],first_right[ti]);
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
