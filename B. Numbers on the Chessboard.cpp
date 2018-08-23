#include <iostream>

using namespace std;

int n,q;
int x,y;


int main(){
	cin >> n >> q;
	while(q--){
		cin >> x >> y;
		long long pos = 1LL * (x - 1) * n + y;
		cout << (pos + 1) / 2 + 1LL * (pos % 2 == 0) * n * n / 2 << "\n";
	}
	return 0;
}