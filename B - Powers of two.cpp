#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

const int NMAX = 2e5;

int n;
int a[NMAX + 5];

map<int,int> vals;

bool ok(int val){
	for(int num = 0;num < 30;num++){
		int suf = (val & ((1 << (num + 1)) - 1));
		int neg = ((((1 << (num + 1)) - 1) ^ suf)) + 1;
		int actual = neg + val;
		
		if(((-actual) & actual) == actual && vals[neg] > 0){
			vals[neg]--;
			return true;
		}
	}
	return false;
}

void add(int val){
	vals[val]++;
}

int main(){
	cin >> n;
	for(int i = 1;i <= n;i++){
		cin >> a[i];
	}
	sort(a + 1,a + 1 + n);
	reverse(a + 1,a + 1 + n);
	
	int ans = 0;
	
	for(int i = 1;i <= n;i++){
		if(ok(a[i])){
			ans++;
		}
		else{
			add(a[i]);
		}
	}
	
	cout << ans;
	return 0;
}