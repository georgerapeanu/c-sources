#include <iostream>

using namespace std;

int main(){
	int n,k;
	cin >> k >> n;
	for(int i = 1;i < n;i++){
		cout << i << " ";
	}
	cout << k - 1LL * n * (n - 1) / 2;
	return 0;
}