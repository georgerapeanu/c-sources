#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int n;
int t;
vector<int> graph[1005];
bool isx[1005];
bool isy[1005];

int dfs(int nod,int tata){
	if(isx[nod]){
		return nod;
	}
	
	int ans = 0;
	
	for(auto it:graph[nod]){
		if(it == tata){
			continue;
		}
		int tmp = dfs(it,nod);
		if(tmp){
			ans = tmp;
		}
	}
	return ans;
}

int main(){
	cin >> t;
	while(t--){
		cin >> n;
		
		for(int i = 1;i <= n;i++){
			graph[i].clear();
		}
		
		memset(isx,0,sizeof(isx));
		memset(isy,0,sizeof(isy));
		
		for(int i = 1;i < n;i++){
			int x,y;
			cin >> x >> y;
			graph[x].push_back(y);
			graph[y].push_back(x);
		}
		
		int k1;
		int a;
		cin >> k1;
		
		for(int i = 1;i <= k1;i++){
			cin >> a;
			isx[a] = true;
		}
		
		int k2;
		int b;
		cin >> k2;
		
		for(int i = 1;i <= k2;i++){
			cin >> b;
			isy[b] = true;
		}
		
		cout << "B " << b << endl;
		cin >> b;
		
		int tmp = dfs(b,0);
		
		cout << "A " << tmp << endl;
		cin >> a;
		
		if(!isy[a]){
			cout << "C " << -1 << endl;
		}
		else{
			cout << "C " << tmp << endl;
		}
	}
	return 0;
}