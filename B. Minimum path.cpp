#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n,k;
string s[2005];
int ant[2005][2005];
vector<pair<int,pair<int,int>> > q;
vector<pair<int,pair<int,int>> > nq;
vector<pair<int,int> > to_update;
vector< pair<int,int> > stuff;
int best[2005][2005];

int main(){
	cin >> n >> k;
	
	for(int i = 1;i <= n;i++){
		cin >> s[i];
		s[i] = " " + s[i];
	}
	
	
	q.push_back({k,{1,1}});
	
	for(int i = 1;i <= 2 * n;i++){
		
		char mini = 'z' + 1;
		
		for(auto it:q){
			if(it.first > 0){
				mini = 'a';
			}
			else{
				mini = min(mini,s[it.second.first][it.second.second]);
			}
		}
		
		
		for(auto it:q){
			if(s[it.second.first][it.second.second] == mini){
				if(it.second.first + 1 <= n){
					nq.push_back(make_pair(it.first,make_pair(it.second.first + 1,it.second.second)));
					ant[it.second.first + 1][it.second.second] = 0;
				}
				if(it.second.second + 1 <= n){
					nq.push_back(make_pair(it.first,make_pair(it.second.first,it.second.second + 1)));
					ant[it.second.first][it.second.second + 1] = 1;
				}
			}
			
			else if(it.first > 0){
				if(it.second.first + 1 <= n){
					nq.push_back(make_pair(it.first - 1,make_pair(it.second.first + 1,it.second.second)));
					ant[it.second.first + 1][it.second.second] = 0;
				}
				if(it.second.second + 1 <= n){
					nq.push_back(make_pair(it.first - 1,make_pair(it.second.first,it.second.second + 1)));
					ant[it.second.first][it.second.second + 1] = 1;
				}
				to_update.push_back(it.second);
			}
		}
		
		for(auto it:to_update){
			s[it.first][it.second] = 'a';
		}
		
		to_update.clear();
		swap(q,nq);
		nq.clear();
		stuff.clear();
		
		for(auto it:q){
			stuff.push_back(it.second);
			best[it.second.first][it.second.second] = max(best[it.second.first][it.second.second],it.first);
		}
		
		sort(stuff.begin(),stuff.end());
		stuff.resize(unique(stuff.begin(),stuff.end()) - stuff.begin());
		q.clear();
		for(auto it:stuff){
			q.push_back(make_pair(best[it.first][it.second],it));
		}
		
	}
	
	string ans;
	int x = n;
	int y = n;
	
	while(x && y){
		ans += s[x][y];
		if(ant[x][y]){
			y--;
		}
		else{
			x--;
		}
	}
	
	reverse(ans.begin(),ans.end());
	
	cout << ans;
	
	return 0;
}