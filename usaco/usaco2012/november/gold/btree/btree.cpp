#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("btree.in","r");
FILE *g = fopen("btree.out","w");

const int NMAX = 4e4;

int n;
int label[NMAX + 5];
bool viz[NMAX + 5];

vector<int> graph[NMAX + 5];

int weight[NMAX + 5];

void get_weights(int nod,int tata) {
    weight[nod] = 1;

    for(auto it:graph[nod]) {
        if(viz[it] || it == tata) {
            continue;
        }
        get_weights(it,nod);
        weight[nod] += weight[it];
    }
}

int get_centroid(int nod) {
    int total_weight = weight[nod];

    while(true) {
        int nxt = -1;
        for(auto it:graph[nod]) {
            if(weight[it] > weight[nod] || viz[it]) {
                continue;
            }
            if(weight[it] * 2 > total_weight) {
                nxt = it;
            }
        }
        if(nxt == -1) {
            break;
        }
        nod = nxt;
    }
    return nod;
}

int best[NMAX + 5];

int dfs(int nod,int tata,bool wr,int h,int mi_h,int ma_h) {

    if((label[nod] == '(') != wr) {
        h++;
        mi_h = min(0,mi_h + 1);
        ma_h = max(0,ma_h + 1);
    }
    else {
        h--;
        mi_h = min(0,mi_h - 1);
        ma_h = max(0,ma_h - 1);
    }

    int ans = 0;

    if(mi_h >= 0) {
        if(wr == false) {
            if(best[h] > 0) {
                ans = max(ans,max(ma_h,best[h]));
            }
        }
        else {
            best[h] = max(best[h],ma_h);
        }
    }

    for(auto it:graph[nod]) {
        if(it == tata || viz[it] == true) {
            continue;
        }
        ans = max(ans,dfs(it,nod,wr,h,mi_h,ma_h));
    }

    return ans;
}

int solve(int nod) {
    nod = get_centroid(nod);
    get_weights(nod,0);

    viz[nod] = true;

    int ans = 0;

    for(int i = 0; i <= weight[nod]; i++) {
        best[i] = 0;
    }

    for(auto it:graph[nod]) {
        if(viz[it] == true)continue;
        ans = max(ans,dfs(it,nod,false,(label[nod] == '(' ? 1:-1),(label[nod] == '(' ? 0:-1),(label[nod] == '(' ? 1:0)));
        dfs(it,nod,true,0,0,0);
    }

    for(int i = 0; i <= weight[nod]; i++) {
        best[i] = 0;
    }

    reverse(graph[nod].begin(),graph[nod].end());

    for(auto it:graph[nod]) {
        if(viz[it] == true)continue;
        ans = max(ans,dfs(it,nod,false,(label[nod] == '(' ? 1:-1),(label[nod] == '(' ? 0:-1),(label[nod] == '(' ? 1:0)));
        dfs(it,nod,true,0,0,0);
    }

    for(auto it:graph[nod]) {
        if(viz[it] == false) {
            ans = max(ans,solve(it));
        }
    }

    return ans;
}

int main() {

    fscanf(f,"%d\n",&n);

    for(int i = 2; i <= n; i++) {
        int p;
        fscanf(f,"%d\n",&p);
        graph[p].push_back(i);
        graph[i].push_back(p);
    }

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%c\n",&label[i]);
    }

    get_weights(1,0);

    fprintf(g,"%d\n",solve(1));

    fclose(f);
    fclose(g);

    return 0;
}
