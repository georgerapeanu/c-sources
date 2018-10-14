#include <iostream>
#include <algorithm>

using namespace std;

string a;

int main(){
	int n;
	cin >> n;
	cin >> a;
	sort(a.begin(),a.end());
	cout << a;
	return 0;
}