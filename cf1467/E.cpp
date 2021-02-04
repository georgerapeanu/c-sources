#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

int n;
vector<int> graph[NMAX + 5];
int color[NMAX + 5];
int l[NMAX + 5];
int r[NMAX + 5];
map<int,set<int>> positions;
int lst;

void dfs(int nod,int tata){
    l[nod] = ++lst;
    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        dfs(it,nod);
    }
    r[nod] = ++lst;
}

bool ok_up[NMAX + 5];
bool ok_down[NMAX + 5];

void dfs2(int nod,int tata,bool ok_up_father){
    ok_up[nod] = ok_up_father;
    if(ok_up[nod]){
        if(*positions[color[nod]].begin() < l[nod] || *positions[color[nod]].rbegin() > r[nod]){
            ok_up[nod] = false;
        }
    }

    ok_down[nod] = true;
    set<int> :: iterator fst = positions[color[nod]].begin();
    set<int> :: iterator snd = positions[color[nod]].find(*positions[color[nod]].rbegin());
    
    bool valid_fst = true;
    bool valid_snd = true;

    if(*fst == l[nod]){
        fst++;
        if(fst == positions[color[nod]].end()){
            valid_fst = false;
        }
    }
    if(*snd == l[nod]){
        if(snd == positions[color[nod]].begin()){
            valid_snd = false;
        }else{
            snd--;
        }
    }


    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        bool ok_son = ok_up[nod];
       
        if(valid_fst){
            if(*fst < l[it] || *fst > r[it]){
                ok_son = false;
            }
        }
        if(valid_snd){
            if(*snd < l[it] || *snd > r[it]){
                ok_son = false;
            }
        }

        dfs2(it,nod,ok_son);
        ok_down[nod] &= ok_down[it];
    }

    set<int>::iterator it = positions[color[nod]].lower_bound(l[nod] + 1);
    if(it != positions[color[nod]].end() && *it <= r[nod]){
        ok_down[nod] = false;
    }
}

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&color[i]); 
    }
    for(int i = 1;i < n;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1,0);

    for(int i = 1;i <= n;i++){
        positions[color[i]].insert(l[i]);
    }

    dfs2(1,0,true);

    int ans = 0;

    for(int i = 1;i <= n;i++){
        ans += (ok_down[i] && ok_up[i]);
    }

    printf("%d\n",ans);

    return 0;
}
