#include <iostream>

using namespace std;

int main(){
	string a;
	int num = 0;
	cin >> a;
	long long ans = 0;
	for(auto it:a){
		num += (it == 'B');
		ans += num * (it == 'W');
	}
	cout << ans;
	return 0;
}