#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

string s;
int ans[1005];

int main(){
	
	cin >> s;
	
	int n = s.size();
	
	int fr = 0;
	char ch = 'a';

	vector<pair<char,int> > v;
		
	for(auto it:s){
		if(it != ch){
			if(fr)v.push_back({ch,fr});
			ch = it;
			fr = 0;
		}
		fr++;
	}
	if(fr)v.push_back({ch,fr});
	
	int pos = 0;

	for(auto it:v){
		if(it.first == 'a'){
			if(pos != 0)ans[pos] = 1;
			ans[pos + it.second] = 1;
		}
		pos += it.second;
	}

	for(int i = 1;i <= n;i++)cout << ans[i] << " ";

	return 0;
}