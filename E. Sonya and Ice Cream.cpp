#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int N,K;

vector< pair<int,int> > G[100005];
int H[100005];
int maxH[100005];
int T[100005];
int dist[100005],maxD;

void predfs(int nod,int tata){
	H[nod] = 0;
	for(auto it:G[nod]){
		if(it.first != tata){
			predfs(it.first,nod);
			H[nod] = max(H[nod],it.second + H[it.first]);
		}
	}
}

void dfs(int nod,int tata){
	
	int max1 = 0,max2 = 0;
	
	for(auto it:G[nod]){
		maxH[nod] = max(maxH[nod],H[it.first] + it.second);
		if(max1 < H[it.first] + it.second){
			max2 = max1;
			max1 = H[it.first] + it.second;
		}
		else if(max2 < H[it.first] + it.second){
			max2 = H[it.first] + it.second;
		}
	}
	
	int tmp = H[nod];
	
	for(auto it:G[nod]){
		if(it.first != tata){
			if(H[it.first] + it.second == max1){
				H[nod] = max2; 
			}
			else{
				H[nod] = max1;
			}
			dfs(it.first,nod);
			H[nod] = tmp;
		}
	}
	
	H[nod] = tmp;
}

int main(){
	
	cin >> N >> K;
	
	for(int i = 1; i < N;i++){
		int x,y,val;
		cin >> x >> y >> val;
		G[x].push_back({y,val});
		G[y].push_back({x,val});
	}
	
	int nod = 1;
	
	predfs(1,0);
	
	dfs(1,0);
	
	for(int i = 1;i <= N;i++){
		if(maxH[i] < maxH[nod]){
			nod = i;
		}
	}
	
	predfs(nod,0);
	
	priority_queue< pair<int,int> > Q;
	
	T[nod] = -1;
	Q.push({0,nod});
	vector<int> path;
	while(K && !Q.empty()){
		int nod = Q.top().second;
		int cost = Q.top().first;
		path.push_back(nod);
		K--;
		Q.pop();
		int max1 = 0,max2 = 0,nod1,nod2;
		for(auto it:G[nod]){
			if(it.first != T[nod]){
				if(max1 < H[it.first] + it.second){
					max2 = max1;
					max1 = H[it.first] + it.second;
					nod2 = nod1;
					nod1 = it.first;
				}
				else if(max2 < H[it.first] + it.second){
					max2 = H[it.first] + it.second;
					nod2 = it.first;
				}
			}
		}
		if(G[nod].size()){
			T[nod1] = nod;
			Q.push({max1,nod1});
			if(G[nod].size() > 1){
				if(T[nod] == -1){
					T[nod2] = nod;
					Q.push({max2,nod2});
				}
			}
		}
	}
	
	queue<int> QQ;
	
	for(auto it:path){
		QQ.push(it);
		dist[it] = 1;
	}
	
	while(!QQ.empty()){
		int nod = QQ.front();
		maxD = max(maxD,dist[nod]);
		QQ.pop();
		for(auto it:G[nod]){
			if(!dist[it.first]){
				dist[it.first] = dist[nod] + it.second;
				QQ.push(it.first);
			}
		}
	}
	
	cout << maxD - 1 << "\n";
	
	return 0;
}