#include <iostream>

using namespace std;

int n;

int main(){
	cin >> n;
	
	int ans = 0;
	for(int bit = 0;bit <= 30;bit++){
		ans += ((1LL << bit) <= n);
	}
	
	cout << ans;
	return 0;
}