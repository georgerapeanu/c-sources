#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
pair<int,int> v[105];
string ans;

int fr[105];

void Try(int pos){
	memset(fr,0,sizeof(fr));
	int a = 0;
	
	for(int i = 1;i <= pos;i++){
		fr[v[i].first]++;
	}
	
	for(int i = 1;i <= 100;i++){
		a += (fr[i] == 1);
	}
	
	memset(fr,0,sizeof(fr));
	int b = 0;
	
	for(int i = pos + 1;i <= n;i++){
		fr[v[i].first]++;
	}
	
	for(int i = 1;i <= 100;i++){
		b += (fr[i] == 1);
	}
	
	if(a == b){
		cout << "YES\n";
		for(int i = 1;i <= pos;i++){
			ans[v[i].second] = 'A';
		}
		for(int i = pos + 1;i <= n;i++){
			ans[v[i].second] = 'B';
		}
		cout << ans;
		exit(0);
	}
}

int main(){
	cin >> n;
	
	for(int i = 1;i <= n;i++){
		cin >> v[i].first;
		v[i].second = i - 1;
	}

	sort(v + 1,v + 1 + n);
	
	ans.resize(n);
	
	for(int i = 0;i <= n;i++){
		Try(i);
	}
	
	cout << "NO";
	
	return 0;
}