#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("soc2.in","r");
FILE *g = fopen("soc2.out","w");

const int NMAX = 256;
const int MMAX = NMAX * (NMAX - 1) / 2;

struct node_t{
    vector<int> clique;
    bool in[NMAX + 5];

    void add(int nod){
        clique.push_back(nod);
        in[nod] = true;
    }
};

int n,m;
int val[NMAX + 5];
vector<int> graph[NMAX + 5];
bool adj[NMAX + 5][NMAX + 5];
vector<int> clique_tree[NMAX + 5];
vector<int> order;
int pos_in_order[NMAX + 5];
node_t stuff[NMAX + 5];

bool in[NMAX + 5];

int weight[NMAX + 5];///-1 if taken
vector<int> get_ins_order(){
    vector<int> ans;
    
    for(int i = 1;i <= n;i++){
        int bst = -1;
        for(int j = 1;j <= n;j++){
            if(weight[j] == -1){
                continue;
            }
            if(bst == -1 || weight[j] > weight[bst]){
                bst = j;
            }
        }
        weight[bst] = -1;
        ans.push_back(bst);
        for(auto it:graph[bst]){
            if(weight[it] == -1){
                continue;
            }
            weight[it]++;
        }
    }

    return ans;
}

int dp[NMAX + 5][NMAX + 5];

void dfs(int nod){
    for(auto it:clique_tree[nod]){
        dfs(it);
    }
    
    vector<int> best_without_clique_nodes;

    dp[nod][0] = 0;
    for(auto it:clique_tree[nod]){
        best_without_clique_nodes.push_back(dp[it][0]);
        for(auto it2:stuff[it].clique){
            if(stuff[nod].in[it2] == false){
                best_without_clique_nodes.back() = max(best_without_clique_nodes.back(),dp[it][it2]);
            }
        }
        dp[nod][0] += best_without_clique_nodes.back();
    }

    for(auto it:stuff[nod].clique){
        dp[nod][it] = val[it];
        for(int son = 0;son < (int)clique_tree[nod].size();son++){
            dp[nod][it] += (stuff[clique_tree[nod][son]].in[it] == true ? dp[clique_tree[nod][son]][it] - val[it]:best_without_clique_nodes[son]);
        }
    }
}

bool in_ans[NMAX + 5];

void recon(int nod,int son){
    in_ans[son] = true;

    for(auto it:clique_tree[nod]){
        if(stuff[it].in[son] == true){
            recon(it,son);
        }
        else{
            int pos = 0;
            for(auto it2:stuff[it].clique){
                if(stuff[nod].in[it2] == true){
                    continue;
                }
                if(dp[it][it2] > dp[it][pos]){
                    pos = it2;
                }
            }
            recon(it,pos);
        }
    }
}

int main(){
    
    fscanf(f,"%d %d",&n,&m);
    
    for(int i = 1;i <= n;i++){
        fscanf(f,"%d",&val[i]);
    }

    while(m--){
        int u,v;
        fscanf(f,"%d %d",&u,&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
        adj[u][v] = true;
        adj[v][u] = true;
    }

    order = get_ins_order();

    for(int i = 0;i < (int)order.size();i++){
        stuff[i].add(order[i]);
        pos_in_order[order[i]] = i;

        int father = -1;

        for(auto it:graph[order[i]]){
            if(in[it] == false){
                continue;
            }
            father = ((father == -1 || father < pos_in_order[it]) ? pos_in_order[it]:father);
            stuff[i].add(it);
        }

        if(father != -1){
            clique_tree[father].push_back(i);
        }

        in[order[i]] = true;
    }

    dfs(0);

    int pos = 0;

    for(auto it:stuff[0].clique){
        if(dp[0][pos] < dp[0][it]){
            pos = it;
        }
    }

    fprintf(g,"%d\n",dp[0][pos]);

    recon(0,pos);

	int cnt = 0;
    for(int i = 1;i <= n;i++){
        if(in_ans[i] == true){
			cnt++;
        }
    }
	
	fprintf(g,"%d\n",cnt);
	
	for(int i = 1;i <= n;i++){
        if(in_ans[i] == true){
			fprintf(g,"%d ",i); 
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}