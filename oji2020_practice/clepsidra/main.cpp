#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("clepsidra.in","r");
FILE *g = fopen("clepsidra.out","w");

const int NMAX = 2e5;
const int MMAX = 2e5;
const int MOD = 666013;

int n,m;
int id[NMAX + 5],lst_id;
int low[NMAX + 5];
pair<int,int> st[MMAX + 5];
int len;

vector<int> graph[NMAX + 5];

int cnt[NMAX + 5];

void dfs(int nod,int tata){
    low[nod] = id[nod] = ++lst_id;
    for(auto it:graph[nod]){
        if(id[it]){
            low[nod] = min(low[nod],id[it]);
        }
        else{
            st[++len] = {nod,it};
            dfs(it,nod);
            low[nod] = min(low[nod],low[it]);
            if(low[it] >= id[nod]){
                while(st[len] != make_pair(nod,it)){
                    len--;
                }
                len--;
                cnt[nod]++;
            }
        }
    }
    cnt[nod] += (tata != 0);
}

int main(){

    fscanf(f,"%d %d",&n,&m);

    for(int i = 1;i <= m;i++){
        int a,b;
        fscanf(f,"%d %d",&a,&b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs(1,0);

    for(int i = 1;i <= n;i++){
        int ans = 1;
        for(int j = 1;j <= cnt[i];j++){
            ans *= 2;
            if(ans >= MOD){
                ans -= MOD;
            }
        }
        ans -= 2;
        if(ans < 0){
            ans += MOD;
        }
        fprintf(g,"%d\n",ans);
    }

    fclose(f);
    fclose(g);

    return 0;
}
