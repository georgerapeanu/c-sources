#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int WMAX = 2e5;

int h,w,n;
vector<int> dia[2 * WMAX + 5];
vector< pair<int,int> > obstacles;

int main(){
	
	
	cin >> h >> w >> n;
	
	for(int i = 1;i <= n;i++){
		int x,y;
		cin >> x >> y;
		dia[h - x + y].push_back(x);
		obstacles.push_back({x,y});
	}
	
	for(int i = 1;i <= w;i++){
		dia[h - (h + 1) + i].push_back(h + 1);
		obstacles.push_back({h + 1,i});
	}
	
	for(int i = 0;i <= 2 * WMAX + 2;i++){
		sort(dia[i].begin(),dia[i].end());
	}
	
	sort(obstacles.begin(),obstacles.end());
	
	for(auto it:obstacles){
		int x = it.first - 1;
		int y = it.second;
		
		if(x < y){
			continue;
		}
		
		if(dia[h - x + y].empty() || dia[h - x + y][0] > x){
			cout << x;
			return 0;
		}
	}
		
	return 0;
}