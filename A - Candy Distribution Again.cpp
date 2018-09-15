#include <iostream>
#include <algorithm>

using namespace std;

int n,x;
int v[105];

int main(){
	cin >> n >> x;
	
	for(int i = 1;i <= n;i++){
		cin >> v[i];
	}
	
	sort(v + 1,v + 1 + n);
	
	for(int i = 1;i <= n;i++){
		if(x < v[i]){
			cout << i - 1;
			return 0;
		}
		x -= v[i];
	}
	
	cout << n - (x != 0);
	
	return 0;
}