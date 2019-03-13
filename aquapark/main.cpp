#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("aquapark.in","r");
FILE *g = fopen("aquapark.out","w");

const int NMAX = 70000;
const int MMAX = 100000;

int c,n,m;
pair<int,int> v[MMAX + 5];

vector<int> graph[NMAX + 5];
int viz[NMAX + 5];

int father[NMAX + 5];

int ans[NMAX + 5];

int fi_root(int a){
    if(father[a]){
        return father[a] = fi_root(father[a]);
    }
    return a;
}

void join(int a,int b){
    a = fi_root(a);
    b = fi_root(b);

    if(a == b){
        return ;
    }

    father[a] = b;
}

void dfs(int nod,int cul){
    viz[nod] = true;
    ans[nod] = cul;

    for(auto it:graph[nod]){
        if(!viz[it]){
            dfs(it,!cul);
        }
    }
}
#define x first
#define y second
bool ok(pair<int,int> a,pair<int,int> b){
    return a.y <= b.x || a.x >= b.y || (a.x <= b.x && b.y <= a.y) || (b.x <= a.x && a.y <= b.y);
}

int main(){

    fscanf(f,"%d %d %d",&c,&n,&m);

    for(int i = 1;i <= m;i++){
        fscanf(f,"%d %d",&v[i].first,&v[i].second);
        if(v[i].first > v[i].second){
            swap(v[i].first,v[i].second);
        }
    }


    for(int i = 1;i <= m;i++){
        for(int j = 1;j < i;j++){
            if(!ok(v[i],v[j])){
                join(i,j);
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }

    int cnt = 0;

    for(int i = 1;i <= m;i++){
        if(father[i] == 0){
            cnt++;
            dfs(i,0);
        }
    }

    if(c == 1){
        for(int i = 1;i <= m;i++){
            fprintf(g,"%d %d %d\n",v[i].first,v[i].second,ans[i] + 1);
        }
    }
    else{
        int ans = 1;
        while(cnt--){
            ans *= 2;
            if(ans >= 666013){
                ans -= 666013;
            }
        }

        fprintf(g,"%d",ans);
    }


    fclose(f);
    fclose(g);

    return 0;
}
