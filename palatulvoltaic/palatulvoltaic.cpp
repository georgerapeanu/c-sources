#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("palatulvoltaic.in","r");
FILE *g = fopen("palatulvoltaic.out","w");

const int NMAX = 3e5;
const int KMAX = 1e9;
const int VMAX = 1e9;
const int MOD = 1e9 + 7;

int n,k;
int v[NMAX + 5];
vector<int> graph[NMAX + 5];
vector<int> sons[NMAX + 5];
int ans[NMAX + 5];

const int LEN = 1 << 16;
char buff[LEN];
int ind = LEN - 1;

int i32() {
    int ans = 0;
    while(buff[ind] < '0' || buff[ind] > '9') {
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while('0' <= buff[ind] && buff[ind] <= '9') {
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    return ans;
}

int gcd(int a,int b) {
    if(b == 0) {
        return a;
    }
    return gcd(b,a % b);
}

struct data_t {
    vector<pair<int,int> > v;///position and value to which the gcd changes

    data_t() {
        v.clear();
    }

    data_t operator + (const data_t &other)const {
        int gg = 0;
        int i = 0;
        int j = 0;
        data_t ans;
        while(i < (int)v.size() && j < (int)other.v.size()) {
            if(v[i].first < other.v[j].first) {
                gg = gcd(gg,v[i].second);
                if(ans.v.empty() || ans.v.back().second != gg) {
                    ans.v.push_back({v[i].first,gg});
                }
                i++;
            }
            else if(v[i].first == other.v[j].first) {
                gg = gcd(gg,v[i].second);
                gg = gcd(gg,other.v[j].second);
                if(ans.v.empty() || ans.v.back().second != gg) {
                    ans.v.push_back({v[i].first,gg});
                }
                i++;
                j++;
            }
            else {
                gg = gcd(gg,other.v[j].second);
                if(ans.v.empty() || ans.v.back().second != gg) {
                    ans.v.push_back({other.v[j].first,gg});
                }
                j++;
            }
        }
        while(i < (int)v.size()) {
            gg = gcd(gg,v[i].second);
            if(ans.v.empty() || ans.v.back().second != gg) {
                ans.v.push_back({v[i].first,gg});
            }
            i++;
        }
        while(j < (int)other.v.size()) {
            gg = gcd(gg,other.v[j].second);
            if(ans.v.empty() || ans.v.back().second != gg) {
                ans.v.push_back({other.v[j].first,gg});
            }
            j++;
        }
        return ans;
    }
};

data_t node_custom[NMAX + 5];
data_t pref_son[NMAX + 5];
data_t suff_son[NMAX + 5];

void predfs(int nod,int tata) {
    node_custom[nod].v.push_back({0,gcd(v[nod],k + 1)});
    for(int k = 0; k < (int)graph[nod].size(); k++) {
        if(graph[nod][k] == tata) {
            continue;
        }
        predfs(graph[nod][k],nod);
        data_t tmp = node_custom[graph[nod][k]];
        for(auto &it:tmp.v) {
            it.first++;
        }
        pref_son[graph[nod][k]] = tmp;
        if(sons[nod].size()) {
            pref_son[graph[nod][k]] = tmp + pref_son[sons[nod].back()];
        }
        sons[nod].push_back(graph[nod][k]);
    }
    for(int k = (int)sons[nod].size() - 1; k >= 0; k--) {
        data_t tmp = node_custom[sons[nod][k]];
        for(auto &it:tmp.v) {
            it.first++;
        }
        suff_son[sons[nod][k]] = tmp;
        if(k + 1 < (int)sons[nod].size()) {
            suff_son[sons[nod][k]] = tmp + suff_son[sons[nod][k + 1]];
        }
    }
    if(sons[nod].size()) {
        node_custom[nod] = node_custom[nod] + pref_son[sons[nod].back()];
    }
}

void dfs(int nod,int tata) {
    if(tata != 0) {
        node_custom[nod] = node_custom[nod] + node_custom[tata];
    }

    node_custom[nod].v.push_back({n,0});
    /*
        printf("dfs %d:\n",nod);

        for(auto it:node_custom[tata].v){
            printf("%d %d\n",it.first,it.second);
        }
    */
    for(int i = 0; i < (int)node_custom[nod].v.size() - 1; i++) {
        ans[nod] = (ans[nod] + 1LL * (node_custom[nod].v[i + 1].first - node_custom[nod].v[i].first) * (k + 1 - node_custom[nod].v[i].second)) % MOD;
    }

    for(int i = 0; i < (int)sons[nod].size(); i++) {
        node_custom[nod].v.clear();
        node_custom[nod].v.push_back({0,gcd(v[nod],k + 1)});
        if(tata != 0) {
            node_custom[nod] = node_custom[nod] + node_custom[tata];
        }
        if(i != 0) {
            node_custom[nod] = node_custom[nod] + pref_son[sons[nod][i - 1]];
        }
        if(i < (int)sons[nod].size() - 1) {
            node_custom[nod] = node_custom[nod] + suff_son[sons[nod][i + 1]];
        }
        for(auto &it:node_custom[nod].v) {
            it.first++;
        }
        dfs(sons[nod][i],nod);
    }

    node_custom[nod].v.push_back({0,gcd(v[nod],k + 1)});
    if(sons[nod].size()) {
        node_custom[nod] = node_custom[nod] + pref_son[graph[nod].back()];
    }
}

int lgpow(int b,int e) {
    int p = 1;
    while(e) {
        if(e & 1) {
            p = 1LL * b * p % MOD;
        }
        e >>= 1;
        b = 1LL * b * b % MOD;
    }
    return p;
}

int main() {

    n = i32();
    k = i32();

    for(int i = 1; i <= n; i++) {
        v[i] = i32();
    }

    for(int i = 1; i < n; i++) {
        int x,y;
        x = i32();
        y = i32();
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    predfs(1,0);
    /*for(int i = 1;i <= n;i++){
        printf("%d:\n",i);
        for(auto it:node_custom[i].v){
            printf("%d %d\n",it.first,it.second);
        }
    }*/
    dfs(1,0);

    int invn = lgpow(n,MOD - 2);

    for(int i = 1; i <= n; i++) {
        fprintf(g,"%d\n",int(1LL * ans[i] * invn % MOD));
    }

    fclose(f);
    fclose(g);

    return 0;
}
