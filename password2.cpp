#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n,s;

vector<string> strings;

string mer(string &a,string &b){
	int ind = 0;
	string pref = "";
	
	while(ind < (int)b.size()){
		string tmp = pref + b[ind] + a;
		cout << tmp << endl;
		int ans;
		cin >> ans;
		if(ans == (int)tmp.size()){
			pref += b[ind];
			ind++;
		}
		else{
			break;
		}
	}
	
	for(int i = 0;i < (int)a.size();i++){
		pref += a[i];
		while(ind < (int)b.size()){
			string tmp = pref + b[ind] + a.substr(i + 1);
			cout << tmp << endl;
			int ans;
			cin >> ans;
			if(ans == (int)tmp.size()){
				pref += b[ind];
				ind++;
			}
			else{
				break;
			}
		}
	}
	return pref;
}

int main(){
	cin >> n >> s;
	for(char c = 'a'; c < 'a' + s;c++){
		string tmp(n,c);
		cout << tmp << endl;
		int ans;
		cin >> ans;
		if(ans){
			tmp.resize(ans);
			strings.push_back(tmp);
		}
	}
	
	while((int)strings.size() > 1){
		sort(strings.begin(),strings.end(),[&](string a,string b){return a.size() > b.size();});
		string tmp = strings.back();
		strings.pop_back();
		strings.back() = mer(tmp,strings.back());
	}
		
	return 0;
}