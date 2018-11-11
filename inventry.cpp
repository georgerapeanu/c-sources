#include <iostream>
#include <queue>

using namespace std;

int wh,last;
int t,n;
queue<int> q;
string s;

int main(){
	cin >> t;
	
	while(t--){
		string s;
		cin >> n;
		cin >> s;
		s = " " + s;
		
		long long ans = 0;
		for(int i = 1;i <= n;i++){
			if(s[i] != '#'){
				break;
			}
			if(i == n){
				cout << "0\n";
				goto done1;
			}
		}

		wh = 1;
		last = -1;
		while(q.size())q.pop();
		
		
		for(int i = 1;i < n;i++){
			if(s[i] == '#'){
				if(i == wh ||  last < i - 1){
					last = i;
					ans += (i - wh);
					wh++;
				}
				else{
					q.push(i);
				}
			}
			else if(!q.empty()){
				if(last < i - 1){
					last = i;
					ans += i - wh + i - q.front();
					wh++;
					q.pop();
				}
			}
		}
		
		if(!q.empty() || s[n] == '#'){
			cout << "-1\n";
		}
		else{
			cout << ans << "\n";
		}
		done1:;
	}
	
	return 0;
}