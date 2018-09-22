#include <iostream>

using namespace std;

long long l,r;

int main(){
	cin >> l >> r;
	cout << "YES\n";
	for(long long i = l;i <= r;i += 2){
		cout << i << " " << i + 1 << "\n";
	}
	return 0;
}