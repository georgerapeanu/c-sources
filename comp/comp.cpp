#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("comp.in","r");
FILE *g = fopen("comp.out","w");

const int NMAX = 16000;

int n;

int perm[NMAX + 5][4];

vector<int> sons[NMAX + 5];
int weight[NMAX + 5];

///solves nod's subtree
///assumes that nod color is 1,and remaps the sons's colors to assure a difference of at most 1(also a color prefix whould have more than the rest)
///for example,if we have 2 sons,with weights 2 and 2
///both would have the representation 110
///we know that nod is 1,so we want to flip colors 2 and 1 for both sons,so 1 is now free
///and to assure they have different colors,we cyclicly shift one of them
void dfs(int nod){
    
    weight[nod] = 1;
    perm[nod][1] = 1;perm[nod][2] = 2;perm[nod][3] = 3;

    if((int)sons[nod].size() == 0){
        return ;
    }

    if((int)sons[nod].size() == 1){
        int u = sons[nod][0];
        dfs(u);
        perm[u][1] = 2;perm[u][2] = 3;perm[u][3] = 1;
        weight[nod] += weight[u];
        return ;
    }

    if((int)sons[nod].size() == 2){
        int u = sons[nod][0];
        int v = sons[nod][1];
        
        dfs(u);
        dfs(v);

        int wu = weight[u] % 3;
        int wv = weight[v] % 3;

        weight[nod] += wu + wv;

        if(wu > wv){
            swap(wu,wv);
            swap(u,v);
        }

        if(wu == 0){
            perm[u][1] = 3;perm[u][2] = 1;perm[u][3] = 2;
            perm[v][1] = 2;perm[v][2] = 3;perm[v][3] = 1;
        }
        else if(wu == 1){
            perm[u][1] = 2;perm[u][2] = 3;perm[u][3] = 1;
            perm[v][1] = 3;perm[v][2] = 1;perm[v][3] = 2;
        }
        else{
            perm[u][1] = 2;perm[u][2] = 1;perm[u][3] = 3;
            perm[v][1] = 3;perm[v][2] = 2;perm[v][3] = 1;
        }
    }
}

int colors[NMAX + 5];

void get_colors(int nod,const vector<int> &global_perm){
    vector<int> tmp_perm = {0,1,2,3};
    for(int i = 1;i < 4;i++){
        tmp_perm[i] = global_perm[perm[nod][i]];
    }
    
    colors[nod] = tmp_perm[1];

    for(auto it:sons[nod]){
        get_colors(it,tmp_perm);
    }
}

int main(){
    
    fscanf(f,"%d",&n);

    for(int i = 1;i < n;i++){
        int a,b;
        fscanf(f,"%d %d",&a,&b);
        sons[b].push_back(a);
    }

    dfs(1);
    get_colors(1,{0,1,2,3});

    for(int i = 1;i <= n;i++){
        fprintf(g,"%d ",colors[i]);
    }

    fclose(f);
    fclose(g);

    return 0;
}
