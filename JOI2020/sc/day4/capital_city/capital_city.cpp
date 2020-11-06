#include <bits/stdc++.h>

using namespace std;

const int NMAX = 200000;

int n,k;
int color[NMAX + 5];
vector<int> nodes[NMAX + 5];
vector<int> graph[NMAX + 5];

bool inCentroid[NMAX + 5];
int weight[NMAX + 5];
int father[NMAX + 5];
bool viz[NMAX + 5];
int group[NMAX + 5];
int processed[NMAX + 5];
int global_ans = 1e9;

void predfs(int nod,int tata,int centroid){
    weight[nod] = 1;
    processed[color[nod]] = false;
    viz[nod] = 0;
    group[nod] = centroid;
    father[nod] = tata;

    for(auto it:graph[nod]){
        if(it == tata || inCentroid[it]){
            continue;            
        }
        predfs(it,nod,centroid);
        weight[nod] += weight[it];
    }


}

void dfs(int nod){
    int _father = 0;
    int centroid = nod;

    while(true){
        int bigChild = -1;

        for(auto it:graph[centroid]){
            if(it == _father || inCentroid[it]){
                continue;
            }
            if(bigChild == -1 || weight[bigChild] < weight[it]){
                bigChild = it;
            }
        }
        
        if(weight[bigChild] * 2 > weight[nod]){
            _father = centroid;
            centroid = bigChild;
        }
        else{
            break;    
        }
    }

    predfs(centroid,0,centroid);
    vector<int> colors = {color[centroid]};
    inCentroid[centroid] = true;

    int ans = -1;

    processed[colors.back()] = true;

    while(colors.size()){
        ans++;
        int col = colors.back();
        colors.pop_back();

        for(auto it:nodes[col]){
            if(group[it] != centroid){
                ans = 1e9;
                break;
            }
            int nod = it;
            while(nod && viz[nod] == 0){
                viz[nod] = 1;
                if(processed[color[nod]] == 0){
                    colors.push_back(color[nod]);
                    processed[color[nod]] = true;
                }
                nod = father[nod];
            }
        }

        if(ans == 1e9){
            break;
        }
    }

    global_ans = min(global_ans,ans);

    for(auto it:graph[centroid]){
        if(inCentroid[it] == 0){
            dfs(it);
        }
    }
}

int main(){

    scanf("%d %d",&n,&k);

    for(int i = 1;i < n;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    for(int i = 1;i <= n;i++){
        scanf("%d",&color[i]);
        nodes[color[i]].push_back(i);
    }

    predfs(1,0,0);
    dfs(1);

    printf("%d\n",global_ans);    

    return 0;
}
