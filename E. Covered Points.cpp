#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int n;
int x[1005];
int y[1005];
int xx[1005];
int yy[1005];

long long ans;

int gcd(int a,int b){
	if(!b)return a;
	return gcd(b,a % b);
}

int main(){
	cin >> n;
	
	for(int i = 1;i <= n;i++){
		cin >> x[i] >> y[i] >> xx[i] >> yy[i];
	}
	
	for(int i = 1;i <= n;i++){
		for(int j = 1;j < i;j++){
			if(1LL * (yy[j] - y[j]) * (xx[i] - x[i]) == 1LL * (yy[i] - y[i]) * (xx[i] - x[i])){
				if(sect(i,j)){
					scoate(i,j);
				}
			}
		}
		for(int j = 1;j < i;j++){
		}
	}
	
	return 0;
}