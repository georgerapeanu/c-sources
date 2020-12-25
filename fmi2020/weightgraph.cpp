#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

FILE *f = fopen("weightgraph.in","r");
FILE *g = fopen("weightgraph.out","w");

const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;

int i32(){
    int ans = 0;
    int sgn = 1;


    while((buff[ind] < '0' || buff[ind] > '9') && buff[ind] != '-'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    
    if(buff[ind] == '-'){
        sgn *= -1;
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
    return ans * sgn;
}

struct edge_t{
    int x,y;
    edge_t(){
        x = y = 0;
    }
    edge_t(int x,int y){
        this->x = x;
        this->y = y;
    }
    int other(int v){
        return x ^ y ^ v;
    }
};

const int NMAX = 1e5;
const int MMAX = 2e5;

int n,m,k;
vector<int> graph[NMAX + 5];
int dist[NMAX + 5];
vector<int> st;
edge_t edges[MMAX + 5];
int weight[MMAX + 5];
int father[NMAX + 5];
int father_edge[NMAX + 5];
int gr[NMAX + 5];

void dfs(int nod,int tata){
    dist[nod] = 1 + dist[tata];
    father[nod] = tata;

    for(auto it:graph[nod]){
        int to = edges[it].other(nod);
        if(to == tata){
            continue;
        }
        if(dist[to] == 0){
            gr[nod]++;
            father_edge[to] = it;
            dfs(to,nod);
        }
    }
}

int main(){

    n = i32();m = i32();k = i32();

    for(int i = 1;i <= m;i++){
        int x,y;
        x = i32();
        y = i32();
        graph[x].push_back(i);
        graph[y].push_back(i);
        edges[i] = edge_t(x,y);
    }

    dfs(1,0);

    vector<int> q;

    for(int i = 1;i <= n;i++){
        if(gr[i] == 0){
            q.push_back(i);
        }
    }

    k = n - 1 - k;

    for(int i = 0;i < (int)q.size();i++){
        int nod = q[i];
        gr[father[nod]]--;
        if(gr[father[nod]] == 0){
            q.push_back(father[nod]);
        }
        if(k > 0){
           k--; 
        }
        else{
            weight[father_edge[nod]] = 1;
        }
    }

    for(int i = 1;i <= m;i++){
        fprintf(g,"%d\n",weight[i]);
    }

    fclose(f);
    fclose(g);

    return 0;
}
