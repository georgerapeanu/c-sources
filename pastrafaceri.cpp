#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("pastrafaceri.in","r");
FILE *g = fopen("pastrafaceri.out","w");

const int NMAX = 3e5;

int n,m;
int v[NMAX + 5];
vector<int> graph[NMAX + 5];
int in_cycle[NMAX + 5];
vector<vector<int> > cycles;

bool viz[NMAX + 5];
vector<int> st;
bool in_st[NMAX + 5];

void get_cycles(int nod,int tata) {
    viz[nod] = true;
    in_st[nod] = true;
    st.push_back(nod);

    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }

        if(viz[it]) {
            if(!in_st[it]) {
                continue;
            }

            vector<int> cycle;
            int ind = (int)st.size() - 1;
            while(st[ind] != it) {
                cycle.push_back(st[ind]);
                ind--;
            }
            cycle.push_back(st[ind]);
            reverse(cycle.begin(),cycle.end());
            for(auto it:cycle) {
                in_cycle[it] = cycles.size();
            }
            cycles.push_back(cycle);
        }
        else {
            get_cycles(it,nod);
        }
    }

    st.pop_back();
    in_st[nod] = false;
}

long long ans;

long long dfs(int nod,int tata) {
    if(in_cycle[nod] == -1) {
        long long tmp_ans = v[nod];
        for(auto it:graph[nod]) {
            if(it != tata) {
                tmp_ans = tmp_ans + max(0LL,dfs(it,nod));
            }
        }
        ans = max(ans,tmp_ans);
        return tmp_ans;
    }

    int num = in_cycle[nod];

    vector<long long> costs(cycles[num].size(),0LL);

    for(int i = 0; i < (int)cycles[num].size(); i++) {
        costs[i] = v[cycles[num][i]];
        for(auto it:graph[cycles[num][i]]) {
            if(it != tata && in_cycle[it] != num) {
                costs[i] = costs[i] + max(0LL,dfs(it,cycles[num][i]));
            }
        }
    }

    if(tata != 0) {
        long long sum = 0;
        long long tmp_ans = -(1LL << 60);

        for(auto it:costs) {
            sum += it;
        }

        long long ma = costs[0];
        long long pref = 0;

        for(auto it:costs) {
            pref += it;
            ma = max(ma,pref);
            tmp_ans = max(tmp_ans,sum - (pref - ma));
        }

        ma = pref = 0;

        long long mi = 0;

        for(auto it:costs) {
            pref += it;
            ma = max(ma,pref);
            mi = min(mi,pref);
            ans = max(ans,pref - mi);
            ans = max(ans,sum - (pref - ma));
        }

        ans = max(ans,tmp_ans);

        return tmp_ans;
    }
    else {
        long long sum = 0;
        long long tmp_ans = -(1LL << 60);

        for(auto it:costs) {
            sum += it;
        }

        long long ma = 0;
        long long mi = 0;
        long long pref = 0;

        for(auto it:costs) {
            pref += it;
            ma = max(ma,pref);
            mi = min(mi,pref);
            tmp_ans = max(tmp_ans,sum - (pref - ma));
            tmp_ans = max(tmp_ans,pref - mi);
        }

        ans = max(ans,tmp_ans);

        return tmp_ans;
    }
}

int main() {

    fscanf(f,"%d %d",&n,&m);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&v[i]);
        in_cycle[i] = -1;
    }

    for(int i = 1; i <= m; i++) {
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    get_cycles(1,0);
    dfs(1,0);

    fprintf(g,"%lld",ans);

    fclose(f);
    fclose(g);

    return 0;
}
