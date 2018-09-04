#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = stdin;
FILE *g = stdout;

struct edge_t{
	int to,cost;
	
	edge_t(){
		to = cost = 0;
	}
	
	edge_t(int to,int cost){
		this->to = to;
		this->cost = cost;
	}
};

const int NMAX = 2e5;

int n;
vector<edge_t> graph[NMAX + 5];
int dp[NMAX + 5][2];
int best_nodes[NMAX + 5][2];
int best_cost[NMAX + 5][2];
int ans;



void dfs1(int nod,int tata,int cost_tata){
	dp[nod][0] = dp[nod][1] = 0;
	best_nodes[nod][0] = best_nodes[nod][1] = 0;
	int best_upgrade_cost = -(1 << 30);
	int best_upgrade_cost2 = -(1 << 30);
	for(auto it:graph[nod]){
		if(it.to == tata){
			continue;
		}
		dfs1(it.to,nod,it.cost);
		dp[nod][0] += max(dp[it.to][0],dp[it.to][1]);
		int it_cost_to_upgrade = dp[it.to][0] - max(dp[it.to][0],dp[it.to][1]) + it.cost;
		if(it_cost_to_upgrade > best_upgrade_cost){
			best_upgrade_cost2 = best_upgrade_cost;
			best_nodes[nod][1] = best_nodes[nod][0];
			best_upgrade_cost = it_cost_to_upgrade;
			best_nodes[nod][0]= it.to;
		}
		else if(it_cost_to_upgrade > best_upgrade_cost2){
			best_upgrade_cost2 = it_cost_to_upgrade;
			best_nodes[nod][1]= it.to;
		}
	}
	
	best_cost[nod][0] = best_upgrade_cost;
	best_cost[nod][1] = best_upgrade_cost2;
	
	if(tata){
		if(best_upgrade_cost == -(1 << 30)){
			dp[nod][1] = -(1 << 30);
		}
		else{
			dp[nod][1] = dp[nod][0] + best_upgrade_cost + cost_tata;
		}
	}
	
	else{
		if(best_upgrade_cost2 == -(1 << 30)){
			dp[nod][1] = -(1 << 30);
		}
		else{
			dp[nod][1] = dp[nod][0] + best_upgrade_cost + best_upgrade_cost2;
		}
	}
	
}

void dfs2(int nod,int tata){
	ans = max(ans,dp[nod][0]);
	ans = max(ans,dp[nod][1]);
	
	int back_son[2];
	int back[2] = {dp[nod][0],dp[nod][1]};
	
	for(auto it:graph[nod]){
		if(it.to == tata){
			continue;
		}
		
		back_son[0] = dp[it.to][0];
		back_son[1] = dp[it.to][1];
		
		dp[nod][0] -= max(dp[it.to][0],dp[it.to][1]);
		if(it.to == best_nodes[nod][0] || it.to == best_nodes[nod][1]){
			if(best_cost[nod][1] != -(1 << 30)){
				dp[nod][1] -= dp[it.to][0];
			}
			else{
				dp[nod][1] = -(1 << 30);
			}
		}
		else{
			if(best_cost[nod][1] == -(1 << 30)){
				dp[nod][1] = -(1 << 30);
			}
			else{
				dp[nod][1] = dp[nod][1] - max(dp[it.to][0],dp[it.to][1]) - best_cost[nod][1] + it.cost;
			}
		}
		
		dp[it.to][0] += max(dp[nod][0],dp[nod][1]);
		int nod_cost = dp[nod][0] - max(dp[nod][0],dp[nod][1]) + it.cost;
		
		if(best_cost[it.to][0] < nod_cost){
			best_cost[it.to][1] = best_cost[it.to][0];
			best_nodes[it.to][1] = best_nodes[it.to][0];
			best_cost[it.to][0] = nod_cost;
			best_nodes[it.to][0] = nod;
		}
		
		else if(best_cost[it.to][1] < nod_cost){
			best_cost[it.to][1] = nod_cost;
			best_nodes[it.to][1] = nod;
		}
		
		if(best_cost[it.to][1] == -(1 << 30)){
			dp[it.to][1] = -(1 << 30);
		}
		else{
			dp[it.to][1] = dp[it.to][0] + best_cost[it.to][0] + best_cost[it.to][1];
		}
		
		dfs2(it.to,nod);
		
		dp[it.to][0] = back_son[0];
		dp[it.to][1] = back_son[1];
		dp[nod][0] = back[0];
		dp[nod][1] = back[1];
		
	}
}

int main(){
	
	fscanf(f,"%d",&n);
	
	for(int i = 1;i < n;i++){
		int a,b,c;
		fscanf(f,"%d %d %d",&a,&b,&c);
		graph[a].push_back(edge_t(b,c));
		graph[b].push_back(edge_t(a,c));
	}
	
	dfs1(1,0,0);
	dfs2(1,0);
	
	fprintf(g,"%d",ans);
	
	return 0;
}