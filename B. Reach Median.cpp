#include <iostream>
#include <algorithm>

using namespace std;

int n,target;
int v[(int)2e5 + 5];

int main(){
	
	cin >> n >> target;
	
	for(int i = 1;i <= n;i++){
		cin >> v[i];
	}
	
	sort(v + 1,v + 1 + n);
	
	long long ans = 0;
	
	if(v[n / 2 + 1] <= target){
		for(int i = n / 2 + 1;i <= n;i++){
			ans += max(0,target - v[i]);
		}
	}
	else{
		for(int i = n / 2 + 1;i;i--){
			ans += max(0,-target + v[i]);
		}
	}
	
	cout << ans;
	
	return 0;
}