#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int NMAX = 1e5;

int n,m;
int a[NMAX + 5];
int b[NMAX + 5];

bool ok(int val){
	int last = 1;
	
	for(int i = 1;i <= n;i++){
		
		while(last <= m && a[i] - b[last] > val){
			last++;
		}
		
		if(last > m){
			return false;
		}
		
		if(a[i] + val < b[last]){
			return false;
		}
		
		last++;
	}
	
	return true;
}

int main(){
	
	cin >> n >> m;
	
	for(int i = 1;i <= n;i++){
		cin >> a[i];
	}
	
	for(int i = 1;i <= m;i++){
		cin >> b[i];
	}
	
	if(n > m){
		for(int i = 1;i <= n || i <= m;i++){
			swap(a[i],b[i]);
		}
		swap(n,m);
	}
	
	sort(a + 1,a + 1 + n);
	sort(b + 1,b + 1 + m);
	
	int st = -1,dr = 1e9;
	while(dr - st > 1){
		int mid = (st + dr) / 2;
		if(ok(mid)){
			dr = mid;
		}
		else{
			st = mid;
		}
	}

	cout << dr;
	
	return 0;
}