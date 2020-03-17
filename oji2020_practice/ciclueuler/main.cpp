#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("ciclueuler.in","r");
FILE *g = fopen("ciclueuler.out","w");

int n,m;
vector<pair<int,int> > graph[100005];
bool used[500005];
int gr[100005];


int main(){

    fscanf(f,"%d %d",&n,&m);

    for(int i = 1;i <= m;i++){
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        graph[x].push_back({y,i});
        graph[y].push_back({x,i});
        gr[x]++;
        gr[y]++;
    }
    for(int i = 1;i <= n;i++){
        if(gr[i] & 1){
            fprintf(g,"-1\n");
            return 0;
        }
    }

    vector<int> v;
    v.push_back(1);

    while((int)v.size() > 0){
        int nod = v.back();
        while(graph[nod].empty() == false && used[graph[nod].back().second] == true){
            graph[nod].pop_back();
        }
        if(graph[nod].empty()){
            if((int)v.size() > 1){
                fprintf(g,"%d ",nod);
            }
            v.pop_back();
        }
        else{
            used[graph[nod].back().second] = true;
            v.push_back(graph[nod].back().first);
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
