#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

const int NMAX = 5e4;

int n;
string a[NMAX + 5];
string b[NMAX + 5];

map<string,vector<string> > graph;
map<string,bool> viz;

vector<int> dfs(string nod){
	viz[nod] = true;
	vector<int> ans;
	
	if('0' <= nod[0] && nod[0] <= '9'){
		ans.push_back(nod[0] - '0');
	}
	
	for(auto it:graph[nod]){
		if(viz[it] == false){
			vector<int> tmp = dfs(it);
			for(auto it:tmp){
				ans.push_back(it);
			}
		}
	}
	
	return ans;
}

int main(){
	
	cin >> n;
	
	for(int i = 1;i <= n;i++){
		cin >> a[i];
	}
	
	for(int i = 1;i <= n;i++){
		cin >> b[i];
		graph[a[i]].push_back(b[i]);
		graph[b[i]].push_back(a[i]);
	}
	
	for(auto it:graph){
		if(!viz[it.first]){
			vector<int> tmp = dfs(it.first);
			if(tmp.size() > 1){
				cout << "NE";
				return 0;
			}
		}
	}
	
	cout << "DA";
	
	return 0;
}