#include <iostream>

using namespace std;

int n;
string a,b;

int main(){
	
	cin >> n;
	cin >> a;
	cin >> b;
	
	int ans = 0;
	
	for(int i = 0;i < n - 1;i++){
		if(a[i] != b[i] && a[i + 1] != b[i + 1] && a[i] == b[i + 1] && a[i + 1] == b[i]){
			ans++;
			swap(a[i],a[i + 1]);
		}
	}
	
	for(int i = 0;i < n;i++){
		ans += (a[i] != b[i]);
	}
	
	cout << ans;
	
	return 0;
}