#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int n;
int s;

int main(){
	
	cin >> n;
	
	int ma = 0;
	
	for(int i = 1;i <= n;i++){
		int v;
		cin >> v;
		ma = max(ma,v);
		s += v;
	}
	
	int k = (2 * s) / n;
	
	while(k * n <= 2 * s){
		k++;
	}
	
	cout << max(k,ma);
	
	return 0;
}