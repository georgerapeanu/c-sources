#include<iostream>
#include<vector>
#include<bitset>

using namespace std;

int n,m;
vector<int> graph[1000005];
vector<int> grapht[1000005];
bitset<1000005> u;
bitset<1000005> bagat;

vector<int> solve(bitset<1000005> &u, int last){
	while(last > 0 && u[last]){
		last--;
	}
	
	if(!last){
		return vector<int>();
	}
	
	u[last] = 1;
	for(auto it:graph[last]){
		u[it] = 1;
	}
	
	vector<int> tmp = solve(u,last);
	
	for(auto it:grapht[last]){
		if(bagat[it]){
			return tmp;
		}
	}
	
	tmp.push_back(last);
	bagat[last] = 1;
	return tmp;
}


int main(){
	
	cin.sync_with_stdio(false);cin.tie(0);
	cout.sync_with_stdio(false);cout.tie(0);
	
	cin >> n >> m;
	
	for(int i = 1;i <= m;i++){
		int x,y;
		cin >> x >> y;
		graph[x].push_back(y);
		grapht[y].push_back(x);
	}
	
	vector<int> ans = solve(u,n);
	
	cout << (int)ans.size() << "\n";
	
	for(auto it:ans){
		cout << it << " ";
	}
	
	return 0;
}