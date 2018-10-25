#include <iostream>

using namespace std;

int n;
string s;

int main(){
	cin >> n;
	cin >> s;
	for(int i = 1;i < n;i++){
		if(s[i - 1] != s[i]){
			cout << "YES\n";
			cout << s[i - 1] << s[i];
			return 0;
		}
	}
	cout << "NO\n";
	return 0;
}