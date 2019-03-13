#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

const long long VMAX = 1e18;
const long long DIVMAX = cbrt((long double)VMAX) + 5;
const int DIVNUM = 10;
const int EMAX = 60;
const int PMAX = 30;
vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};
vector<pair<long long,vector<pair<int,int> > > > dp[PMAX + 5][DIVMAX + 5];

vector<pair<int,long long> > stuff;

void add_to(int i,int d,vector<pair<long long,vector<pair<int,int> > > > &propag){
    vector<pair<long long,vector<pair<int,int> > > > v((int)dp[i][d].size() + (int)propag.size());
    merge(dp[i][d].begin(),dp[i][d].end(),propag.begin(),propag.end(),v.begin());
    v.resize(min(DIVNUM,(int)v.size()));
    dp[i][d] = v;
}

void make_dp(){
    dp[0][1].push_back({1,{}});

    for(int i = 0;i < (int)primes.size();i++){
        for(int d = 1;d <= DIVMAX;d++){
            vector<pair<long long,vector<pair<int,int> > > > propag = dp[i][d];
            for(auto &it:propag){
                it.second.push_back({i,0});
            }
            for(int e = 0;e <= EMAX && 1LL * d * (e + 1) <= DIVMAX && (int)propag.size();e++){

                int nd = d * (e + 1);

                add_to(i + 1,nd,propag);

                while(!propag.empty() && propag.back().first > VMAX / primes[i]){
                    propag.pop_back();
                }
                
                for(auto &it:propag){
                    it.first *= primes[i];
                    it.second.back().second++;
                }
            }
        }
    }

    for(int d = 1;d <= DIVMAX;d++){
        if(dp[(int)primes.size()][d].empty()){
            continue;
        }
        stuff.push_back({d,dp[(int)primes.size()][d][0].first});
    }
}

vector<pair<int,pair<long long,vector<pair<int,int> > >> > get_hcns_less(long long x){
    int st = 0,dr = (int)stuff.size();

    while(dr - st > 1){
        int mid = (st + dr) / 2;
        if(stuff[mid].second <= x){
            st = mid;
        }
        else{
            dr = mid;
        }
    }

    vector<pair<int,pair<long long,vector<pair<int,int> > >> > ans;

    for(int i = stuff[st].first;i > 0 && (int)ans.size() < DIVNUM;i--){
        for(auto it:dp[(int)primes.size()][i]){
            if(it.first > x || (int)ans.size() >= DIVNUM){
                break;
            }
            ans.push_back({i,it});
        }
    }
    
    sort(ans.begin(),ans.end());

    return ans;
}

void print_pair(int p,int e){
    printf("%d",p);
    if(e != 1){
        printf("^%d",e);
    }
}

void print_desc(vector<pair<int,int> > v){
    int lst = 0;
    while(lst < (int)v.size() && v[lst].second == 0){
        lst++;
    }
    print_pair(primes[v[lst].first],v[lst].second);
    for(int i = lst + 1;i < (int)v.size();i++){
        if(v[i].second == 0){
            continue;
        }
        printf("*");
        print_pair(primes[v[i].first],v[i].second);
    }
}

int main(){

    long long n;

    scanf("%lld",&n);


    make_dp();

    vector<pair<int,pair<long long,vector<pair<int,int> > >> > tmp = get_hcns_less(n);

    for(auto it:tmp){
        printf("%lld %d ",it.second.first,it.first);
        print_desc(it.second.second);
        printf("\n");
    }

    return 0;
}
