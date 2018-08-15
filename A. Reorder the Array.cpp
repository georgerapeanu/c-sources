#include <iostream>
#include <vector>
#include <map>

using namespace std;

map<int,int> M;

int N;

int main(){
	
	cin >> N;
	
	for(int i = 1;i <= N;i++){
		int val;
		cin >> val;
		M[val]++;
	}
	
	vector<int> tmp;
	
	for(auto it:M){
		tmp.push_back(it.second);
	}
	
	int free_pos = 0,ans = 0;
	
	for(auto it:tmp){
		ans += min(free_pos,it);
		free_pos -= min(free_pos,it);
		free_pos += it;
	}

	cout << ans;
	
	return 0;
}