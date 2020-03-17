#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("conexidad.in","r");
FILE *g = fopen("conexidad.out","w");

const int NMAX = 100;

vector<vector<int>> components[2];

int n,m;
int viz[NMAX + 5];
vector<int> graph[NMAX + 5];

void dfs(int nod,vector<int> &comp){
    comp.push_back(nod);
    viz[nod] = true;
    for(auto it:graph[nod]){
        if(viz[it]){
            continue;
        }
        dfs(it,comp);
    }
}

int main(){

    fscanf(f,"%d %d\n",&n,&m);

    if(n == 1){fprintf(g,"0\n0\n");return 0;}
    if(n == 2){fprintf(g,"1\n1\n1 2\n");return 0;}

    for(int i = 1;i <= m;i++){
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    vector<int> comp;

    for(int i = 1;i <= n;i++){
        if(viz[i]){
            continue;
        }
        comp.clear();
        dfs(i,comp);
        components[comp.size() > 1].push_back(comp);
    }

    int ans_a = 1;
    int ans_b = (int)components[0].size() + (int)components[1].size() - 1;

    vector<pair<int,int> > edges;

    for(int i = 1;i < (int)components[1].size();i++){
        edges.push_back({components[1][i - 1].back(),components[1][i].back()});
        components[1][i - 1].pop_back();
        components[1][i].pop_back();
    }

    vector<int> libere;
    vector<int> gr1;

    for(auto it:components[1]){
        for(auto it2:it){
            libere.push_back(it2);
        }
    }

    for(auto it:components[0]){
        for(auto it2:it){
            gr1.push_back(it2);
        }
    }

    if(libere.size() >= gr1.size()){
        ans_a = 1;
        for(int i = 0;i < (int)gr1.size();i++){
            edges.push_back({libere[i],gr1[i]});
        }
        fprintf(g,"%d\n%d\n",ans_a,ans_b);
        for(auto it:edges){
            fprintf(g,"%d %d\n",it.first,it.second);
        }
    }
    else{
        ans_a = 2;
        for(int i = 1;i < (int)gr1.size();i++){
            edges.push_back({gr1[i - 1],gr1[i]});
        }
        if(gr1.size() && libere.size())edges.push_back({gr1[0],libere.back()});
        fprintf(g,"%d\n%d\n",ans_a,ans_b);
        for(auto it:edges){
            fprintf(g,"%d %d\n",it.first,it.second);
        }
    }


    fclose(f);
    fclose(g);

    return 0;
}
