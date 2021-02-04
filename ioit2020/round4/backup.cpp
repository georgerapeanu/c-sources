#include <cstdio>
#include <deque>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 500;

int n;
int d[NMAX + 5];
vector<int> graph[NMAX + 5];
int gr[NMAX + 5];

vector<int> paths[NMAX + 5];

int inv_pos[NMAX + 5];
int taken[NMAX + 5];
int cnt_free = 0;

bool viz[NMAX + 5];

void btr(int pos,int &best,int ans){
    if(pos >= n){
        best = max(best,ans);
        return ;
    }
    int potential_ans = ans + cnt_free;
    if(potential_ans < best){
        return ;
    }
    if(taken[pos]){
        btr(pos + 1,best,ans);
    }else{
        for(auto it:paths[pos]){
            cnt_free -= (taken[it] == 0);
            taken[it]++;
        }
        btr(pos + 1,best,ans + 1);
        for(auto it:paths[pos]){
            taken[it]--;
            cnt_free += (taken[it] == 0);
        }
        cnt_free--;
        btr(pos + 1,best,ans);
        cnt_free++;
    }
}

void dfs(int nod,vector<int> &paths){
    viz[nod] = 1;
    paths.push_back(inv_pos[nod]);

    for(auto it:graph[nod]){
        if(viz[it] == 0){
            dfs(it,paths);
        }
    }
}

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&d[i]);
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            int c;
            scanf("%d",&c);
            if(i != j && d[i] + c <= d[j]){
                gr[j]++;
                graph[i].push_back(j);
            }
        }
    }

    vector<int> roots;

    for(int i = 1;i <= n;i++){
        if(gr[i] == 0){
            roots.push_back(i);
        }
    }

    int max_roots = 0;
    for(int i = 0;i < (int)roots.size();i++){
        max_roots = max(max_roots,(int)roots.size() - i);
        int nod = roots[i];
        for(auto it:graph[nod]){
            gr[it]--;
            if(gr[it] == 0){
                roots.push_back(it);
            }
        }
    }

    for(int i = 0;i < (int)roots.size();i++){
        inv_pos[roots[i]] = i;
    }

    for(int i = 0;i < (int)roots.size();i++){
        for(int i = 1;i <= n;i++){
            viz[i] = false;
        }
        dfs(roots[i],paths[i]);
    }

    cnt_free = n;
    btr(0,max_roots,0);

    printf("%d\n",max_roots);

    return 0;
}
