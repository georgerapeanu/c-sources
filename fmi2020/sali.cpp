#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

FILE *f = fopen("sali.in","r");
FILE *g = fopen("sali.out","w");

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

const int NMAX = 1000;

int n,m;
vector<int> graph[NMAX + 5];
int dist[NMAX + 5];
int where[NMAX + 5];

int bfs(int nod){
    queue<int> q;
    
    dist[nod] = 1;
    q.push(nod);
    int bst = 0;

    while(!q.empty()){
        int nod = q.front();
        bst = max(bst,dist[nod]);
        q.pop();
        for(auto it:graph[nod]){
            if(dist[it] == 0){
                dist[it] = 1 + dist[nod];
                q.push(it);
            }
        }
    }

    return bst;
}

pair<int,vector<pair<int,int> > > solve(int nod){
    vector<int> comp;
    comp.push_back(nod);
    dist[nod] = 1;

    for(int i = 0;i < (int)comp.size();i++){
        int nod = comp[i];
        for(auto it:graph[nod]){
            if(dist[it] == 0){
                dist[it] = 1;
                comp.push_back(it);
            }
        }
    }

    int ans = 0;
    
    vector<pair<int,int> > bst;

    for(int i = 0;i < (int)comp.size();i++){
        for(auto it:comp){
            dist[it] = 0;
        }
        int tmp = bfs(comp[i]);
        if(ans < tmp){
            ans = tmp;
            bst.clear();
            for(auto it:comp){
                bst.push_back({it,dist[it]});
            }
        }
    }

    return {ans,bst};
}



int main(){

    n = i32();
    m = i32();

    for(int i = 1;i <= m;i++){
        int x,y;
        x = i32();
        y = i32();
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    int ans = 0;

    for(int i = 1;i <= n;i++){
        if(dist[i] == 0){
            pair<int,vector<pair<int,int> > > tmp = solve(i);
            for(auto it:tmp.second){
                where[it.first] = ans + it.second;
            }
            ans += tmp.first;
        }
    }

    fprintf(g,"%d\n",ans);

    for(int i = 1;i <= n;i++){
        fprintf(g,"%d ",where[i]);
    }

    fclose(f);
    fclose(g);

    return 0;
}
