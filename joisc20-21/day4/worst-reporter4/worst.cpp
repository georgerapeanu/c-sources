#include <bits/stdc++.h>

using namespace std;

struct slope_magic_t{
    map<int,long long> slope_change;

    slope_magic_t(){
        slope_change = map<int,long long>();
    }

    void merge(slope_magic_t &other){
        for(auto it:other.slope_change){
            slope_change[it.first] += it.second;
        }
    }

    void add_value(int value,int cost){
        slope_change[0] += cost;
        slope_change[value] -= cost;
        slope_change[value + 1] += cost;

        long long relative_height = 0;
        map<int,long long> :: iterator it,it2;
        it = slope_change.lower_bound(value);

        long long current_diff = slope_change[value];
        
        while(current_diff < 0){
            it2 = it;
            if(it2 == slope_change.begin()){
                break;
            }
            it2--;
            if(it2 == slope_change.begin() || current_diff + it2->second >= 0){
                it2->second += current_diff;
                slope_change.erase(it);
                break;
            }
            relative_height = -current_diff - it2->second;
            slope_change.erase(it2);
            current_diff = -relative_height;
        }
    }

    int size(){
        return (int)slope_change.size();
    }

    void swap(slope_magic_t &other){
        slope_change.swap(other.slope_change);
    }

};

const int NMAX = 2e5;

int n;
slope_magic_t dp[NMAX + 5];
vector<int> graph[NMAX + 5];
vector<int> graph2[NMAX + 5];
int father[NMAX + 5];
int c[NMAX + 5];
int h[NMAX + 5];


bool viz[NMAX + 5];
void dfs(int nod){
    viz[nod] = true;
    for(auto it:graph[nod]){
        dfs(it);
        if(dp[it].size() > dp[nod].size()){
            dp[nod].swap(dp[it]);
        }
        dp[nod].merge(dp[it]);
    }
    dp[nod].add_value(h[nod],c[nod]);
}

int lvl[NMAX + 5];
int st[NMAX + 5];
int len;
vector<int> cycle;
bool on_cycle[NMAX + 5];

void predfs(int nod){
    st[++len] = nod;
    lvl[nod] = len;
    viz[nod] = true;
    for(auto it:graph2[nod]){
        if(viz[it] == false){
            predfs(it);
        }else{
            for(int i = lvl[it];i <= lvl[nod];i++){
                on_cycle[st[i]] = true;
                cycle.push_back(st[i]);
            }
        }
    }
    len--;

}

long long solve(int nod){
    cycle.clear();
    predfs(nod);

    slope_magic_t global;

    for(auto it:cycle){
         for(auto it2:graph[it]){
            if(on_cycle[it2] == false){
                dfs(it2);
                global.merge(dp[it2]);
            }
        }
    }

    for(auto it:cycle){
        global.slope_change[0] += c[it];
        global.slope_change[h[it]] -= c[it];
        global.slope_change[h[it] + 1] += c[it];
    }

    long long curr_cost = 0;
    long long ans = 2e18;

    for(auto it:global.slope_change){
        curr_cost += it.second;
        ans = min(ans,curr_cost);
    }

    return ans;
}

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d %d %d",&father[i],&h[i],&c[i]);
        graph[father[i]].push_back(i);
        graph2[i].push_back(father[i]);
    }


    long long ans = 0;

    for(int i = 1;i <= n;i++){
        if(viz[i] == false){
            long long tmp = solve(i);
            ans += tmp;
        }
    }
    printf("%lld\n",ans);

    return 0;
}

