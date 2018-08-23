#include <iostream>

using namespace std;

int n;
string a;

int main(){
	cin >> n;
	while(n--){
		int sz;
		cin >> sz >> a;
		for(int st = 0,dr = (int)a.size() - 1;st < dr;st++,dr--){
			if(abs(a[st] - a[dr]) > 2 || abs(a[st] - a[dr]) % 2 == 1){
				cout << "NO\n";
				goto done1;
			}
		}
		cout << "YES\n";
		done1:;
	}
	return 0;
}