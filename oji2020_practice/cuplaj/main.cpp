#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("cuplaj.in","r");
FILE *g = fopen("cuplaj.out","w");

const int NMAX = 1e4;

int n,m,e;
vector<int> graph[NMAX + 5];
int lft[NMAX + 5];
int rgt[NMAX + 5];
bool viz[NMAX + 5];

bool pairup(int x){
    if(viz[x]){
        return false;
    }
    viz[x] = true;

    for(auto it:graph[x]){
        if(rgt[it] == 0){
            lft[x] = it;
            rgt[it] = x;
            return true;
        }
    }

    for(auto it:graph[x]){
        if(pairup(rgt[it])){
            rgt[it] = x;
            lft[x] = it;
            return true;
        }
    }
    return false;
}

int cuplaj(){
    int c = 0;
    bool ok = true;

    while(ok){
        memset(viz,0,sizeof(viz));
        ok = false;
        for(int i = 1;i <= n;i++){
            if(lft[i] == 0 && pairup(i)){
                ok = true;
                c++;
            }
        }
    }
    return c;
}

int main(){

    fscanf(f,"%d %d %d",&n,&m,&e);

    for(int i = 1;i <= e;i++){
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        graph[x].push_back(y);
    }

    fprintf(g,"%d\n",cuplaj());

    for(int i = 1;i <= n;i++){
        if(lft[i] != 0){
            fprintf(g,"%d %d\n",i,lft[i]);
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
