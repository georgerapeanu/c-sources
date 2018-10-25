#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int n;
string s;
int x,y;

int dx[300];
int dy[300];

int spx[int(2e5) + 5];
int spy[int(2e5) + 5];

bool ok(int st,int dr){
	int nx = (st ? spx[st - 1]:0) + spx[n - 1] - spx[dr];
	int ny = (st ? spy[st - 1]:0) + spy[n - 1] - spy[dr];
	int deltax = x - nx;
	int deltay = y - ny;
	
	// if(st == 0 && dr == 0){
		// cout << spx[n - 1] << " " << spy[n - 1] << "\n";
		// cout << nx << " " << ny << " " << deltax << " " << deltay << "\n";
	// }
	
	if(abs(deltax) + abs(deltay) > dr - st + 1){
		return false;
	}
	
	if((abs(deltax) + abs(deltay)) % 2 != (dr - st + 1) % 2){
		return false;
	}
	
	return true;
}

int main(){
	
	dy['U'] = 1;
	dx['R'] = 1;
	dy['D'] = -1;
	dx['L'] = -1;
	
	cin >> n;
	cin >> s;
	cin >> x >> y;
	
	if(abs(x) + abs(y) > n){
		cout << -1;
		return 0;
	}
	
	if(n % 2 != (abs(x) + abs(y)) % 2){
		cout << -1;
		return 0;
	}
		
	for(int i = 0;i < n;i++){
		spx[i] = (i ? spx[i - 1]:0) + dx[s[i]];
		spy[i] = (i ? spy[i - 1]:0) + dy[s[i]];
	}
	
	int st = 0;
	int ans = 1 << 30;	
	
	if(spx[n - 1] == x && spy[n - 1] == y){
		cout << 0;
		return 0;
	}
	
	for(int dr = 0;dr < n;dr++){
		while(st <= dr && ok(st,dr)){
			st++;
		}
		
		if(st && ok(st - 1,dr)){
			// cout << st << " " << dr << "\n";
			ans = min(ans,dr - st + 2);
		}
	}
	
	cout << (ans == 1 << 30 ? -1:ans);
	
	return 0;
}