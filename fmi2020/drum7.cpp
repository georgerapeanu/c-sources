#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("drum7.in","r");
FILE *g = fopen("drum7.out","w");

const int NMAX = 1e5;

int n,q;
int cnt_towers[NMAX + 5];
vector<int> graph[NMAX + 5];
int active[NMAX + 5];
int ans;

void predfs(int nod,int tata){
    bool has_q = false;
    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        predfs(it,nod);
        cnt_towers[nod] += cnt_towers[it];
        has_q |= (cnt_towers[it] == q);
    }

    if(cnt_towers[nod] > 0 && has_q == false){
        active[nod] = 1;
    }
    ans += 2 * active[nod];
}

pair<int,int> dfs(int nod,int tata){
    pair<int,int> bst = {0,nod};
    for(auto it:graph[nod]){
        if(it == tata || active[it] == 0){
            continue;
        }
        pair<int,int> tmp = dfs(it,nod);
        tmp.first++;
        bst = max(bst,tmp);
    }
    return bst;
}

const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;

int i32(){
    int ans = 0;
    
    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    
    while(!(buff[ind] < '0' || buff[ind] > '9')){
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    return ans;
}

int main(){
    
    n = i32();

    for(int i = 1;i < n;i++){
        int u,v;
        u = i32();
        v = i32();
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    q = i32();

    for(int i = 1;i <= q;i++){
        int id;
        id = i32();
        cnt_towers[id]++;
    }

    ans = -2;
    predfs(1,0);
    
    for(int i = 1;i <= n;i++){
        if(active[i]){
            pair<int,int> tmp = dfs(i,0);
            ans -= dfs(tmp.second,0).first;
            break;
        }
    }

    fprintf(g,"%d\n",ans);
    
    fclose(f);
    fclose(g);

    return 0;
}
