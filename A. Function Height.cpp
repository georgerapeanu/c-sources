#include <iostream>

using namespace std;

long long n,k;

int main(){
	cin >> n >> k;
	cout << (k + (n - 1))/ n;
	return 0;
}