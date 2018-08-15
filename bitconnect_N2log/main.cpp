///O(N^2logN)

#include <cstdio>
#include <vector>
#include <map>
#include <set>

using namespace std;

FILE *f = fopen("bitconnect.in","r");
FILE *g1 = fopen("bitconnect_bitMode_N2log.out","w");
FILE *g2 = fopen("bitconnect_connectMode_N2log.out","w");

const int NMAX = 1e5;
const int LGMAX = 30;
const int LEN = 1e4;

char buff[LEN];
int N;
int ind = LEN - 1;
map<int,int> viz;
map<int,int> Nodes;
map<int,set<int> > G;

int i32(){
    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    int rez = 0;

    while(buff[ind] >= '0' && buff[ind] <= '9'){
        rez = rez * 10 + (buff[ind] - '0');
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    return rez;
}

int Q[NMAX + 5],stq,drq;

int BFS(int S,int D){

    if(S == D){
        return 0;
    }

    viz.clear();

    stq = 1;drq = 0;
    Q[++drq] = S;
    viz[S] = 0;

    while(stq <= drq){
        int node = Q[stq++];
        for(auto it:G[node]){
            if(!viz.count(it)){
                viz[it] = 1 + viz[node];
                Q[++drq] = it;
                if(it == D){
                    return viz[it];
                }
            }
        }
    }

    return -1;
}

void baga(int x){
    for(auto it:Nodes){
        if(x & it.first){
            G[x].insert(it.first);
            G[it.first].insert(x);
        }
    }
    Nodes[x]++;
}

void scoate(int x){
    for(auto it:Nodes){
        if(x & it.first){
            G[x].erase(it.first);
            G[it.first].erase(x);
        }
    }
    Nodes[x]--;
    if(!Nodes[x]){
        Nodes.erase(x);
    }
}

int main(){

    fprintf(g1,"bit\n");
    fprintf(g2,"connect\n");

    N = i32();

    while(N--){
        int t,x,y;
        t = i32();
        if(t == 3){
            x = i32();
            y = i32();
            int ans = BFS(x,y);
            fprintf(g1,"%d\n",ans);
            fprintf(g2,"%d\n",(ans != -1));
        }
        else{
            x = i32();
            if(t == 1){
                baga(x);
            }
            else{
                scoate(x);
            }
        }
    }


    fclose(f);
    fclose(g1);
    fclose(g2);

    return 0;
}
