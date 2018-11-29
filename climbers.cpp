#include <cstdio>
#include <queue>
#include <algorithm>
#include <vector>
#include <bitset>
 
using namespace std;
 
FILE *f = fopen("climbers.in","r");
FILE *g = fopen("climbers.out","w");
 
int n;
int v[5005];
 
long long dist[5000 * 5002 * 2 + 1];
bitset<5000 * 5002 * 2 + 1> in;
 
int state_to_node(int x,int y,int z){
	return x * 5001 * 2 + y * 2 + z;
}
 
pair<pair<int,int>,int> node_to_state(int node){
	return {{node / (2 * 5001),((node % (2 * 5001)) / 2)},node % 2};
}
 
bool is_win(int node){
	auto tmp = node_to_state(node);
	int x = tmp.first.first;
	int y = tmp.first.second;
	int z = tmp.second;
	
	// printf("%d %d %d\n",x,y,z);
	
	if(x == y){
		return true;
	}
	
	if(x == y - 1 && z == 1){
		return true;
	}
	
	return false;
}
 
void add_edge(vector<pair<int,int> > &v,int x,int y,int z,int cost){
	if(!(1 <= x && x <= n))return ;
	if(!(1 <= y && y <= n))return ;
	int tmp = state_to_node(x,y,z);
	if(in[tmp])return;
	v.push_back({tmp,cost});
}
 
vector<pair<int,int> > get_neightbors(int node){
	
	auto tmp = node_to_state(node);
	int i = tmp.first.first;
	int j = tmp.first.second;
	int z = tmp.second;
	
	int dist_i;
	int dist_j;
	int to_i;
	int to_j;
	
	///0
	
	vector<pair<int,int> > ans;
	if(z != 0 || !(min(v[j],v[j + 1]) <= v[i] && v[i] <= max(v[j],v[j + 1]))){
		goto start1;
	}
	
	///move i right
	
	to_i = i + 1;
	dist_i = abs(v[to_i] - v[i]);
	to_j = j + ((v[to_i] > v[i] ? 1:-1) * (v[j + 1] > v[j] ? 1 : -1) == 1);
	dist_j = abs(v[to_j] - v[i]);
	
	if(dist_i < dist_j){
		add_edge(ans,to_i,j,0,dist_i);
	}
	else if(dist_i == dist_j){
		add_edge(ans,to_i,to_j,0,dist_i);
		add_edge(ans,to_i,to_j - 1,0,dist_i);
		add_edge(ans,to_i,to_j,1,dist_i);
		add_edge(ans,to_i - 1,to_j,1,dist_i);
	}
	else{
		add_edge(ans,i,to_j,1,dist_j);
	}
	
	///move i left
	
	to_i = i - 1;
	dist_i = abs(v[to_i] - v[i]);
	to_j = j + ((v[to_i] > v[i] ? 1:-1) * (v[j + 1] > v[j] ? 1 : -1) == 1);
	dist_j = abs(v[to_j] - v[i]);
	
	if(dist_i < dist_j){
		add_edge(ans,to_i,j,0,dist_i);
	}
	else if(dist_i == dist_j){
		add_edge(ans,to_i,to_j,0,dist_i);
		add_edge(ans,to_i,to_j - 1,0,dist_i);
		add_edge(ans,to_i,to_j,1,dist_i);
		add_edge(ans,to_i - 1,to_j,1,dist_i);
	}
	else{
		add_edge(ans,i - 1,to_j,1,dist_j);
	}
	
	///1
	
	start1:;
	
	if(z != 1 || !(min(v[i],v[i + 1]) <= v[j] && v[j] <= max(v[i],v[i + 1]))){
		goto finish;
	}
	
	///move j right
	
	to_j = j + 1;
	dist_j = abs(v[to_j] - v[j]);
	to_i = i + ((v[to_j] > v[j] ? 1:-1) * (v[i + 1] > v[i] ? 1 : -1) == 1);
	dist_i = abs(v[to_i] - v[j]);
	
	if(dist_i < dist_j){
		add_edge(ans,to_i,j,0,dist_i);
	}
	else if(dist_i == dist_j){
		add_edge(ans,to_i,to_j,0,dist_i);
		add_edge(ans,to_i,to_j - 1,0,dist_i);
		add_edge(ans,to_i,to_j,1,dist_i);
		add_edge(ans,to_i - 1,to_j,1,dist_i);
	}
	else{
		add_edge(ans,i,to_j,1,dist_j);
	}
	
	///move j left
	
	to_j = j - 1;
	dist_j = abs(v[to_j] - v[j]);
	to_i = i + ((v[to_j] > v[j] ? 1:-1) * (v[i + 1] > v[i] ? 1 : -1) == 1);
	dist_i = abs(v[to_i] - v[j]);
	
	if(dist_i < dist_j){
		add_edge(ans,to_i,j - 1,0,dist_i);
	}
	else if(dist_i == dist_j){
		add_edge(ans,to_i,to_j,0,dist_i);
		add_edge(ans,to_i,to_j - 1,0,dist_i);
		add_edge(ans,to_i,to_j,1,dist_i);
		add_edge(ans,to_i - 1,to_j,1,dist_i);
	}
	else{
		add_edge(ans,i,to_j,1,dist_j);
	}
	
	finish:;
	
	return ans;
}
 
int main(){
	
	fscanf(f,"%d",&n);
	
	int len = 0;
	
	for(int i = 1;i <= n;i++){
		int val;
		fscanf(f,"%d",&val);
		while(len >= 2 && 1LL * (v[len] - v[len - 1]) * (val - v[len]) >= 0){
			len--;
		}
		v[++len] = val;
	}
	
	n = len;
	
	for(int i = 1;i <= n;i++){
		dist[state_to_node(i,i,0)] = 1LL << 61;
		dist[state_to_node(i,i,1)] = 1LL << 61;
		for(int j = i + 1;j <= n;j++){
			dist[state_to_node(i,j,0)] = 1LL << 61;
			dist[state_to_node(i,j,1)] = 1LL << 61;
			
		}
	}
	
	priority_queue<pair<long long,int>,vector<pair<long long,int> >,greater<pair<long long,int> > > pq;
	
	pq.push({0,state_to_node(1,n,0)});
	pq.push({0,state_to_node(1,n,1)});
	
	dist[state_to_node(1,n,0)] = 0;
	dist[state_to_node(1,n,1)] = 0;
	
	while(!pq.empty()){
		int nod = pq.top().second;
		long long cost = pq.top().first;
		pq.pop();
		in[nod] = true;
		if(cost != dist[nod]){
			continue;
		}
		
		if(is_win(nod)){
			fprintf(g,"%lld",cost);
			return 0;
		}
		
		vector<pair<int,int> > neighbors = get_neightbors(nod);
		for(auto it:neighbors){
			if(dist[nod] + it.second < dist[it.first]){
				dist[it.first] = dist[nod] + it.second;
				pq.push({dist[it.first],it.first});
			}
		}
	}
	fprintf(g,"NO");
	
	fclose(f);
	fclose(g);
	
	return 0;
}