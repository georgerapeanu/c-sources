#include <iostream>

using namespace std;

int f[200005];

int main(){

	int ans = 0;

	for(int i = 2;i <= 200000;i++){
		f[i] = 2 * (f[(i + 1) / 2]) + 1;
		ans = max(ans,f[i] - i);
	}
	
	cout << ans;

	return 0;
}
