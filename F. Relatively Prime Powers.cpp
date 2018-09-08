#include <iostream>
#include <cmath>

using namespace std;

long long n;

bool ciur[105];
int sign[105];
int pp[105];

long long root(int exp,long long target){
	long long ans = pow(target,(long double)1 / exp);
	return ans;
}

long long solve(long long n){
	
	long long ans = n - 1;

	for(int i = 2;i <= 60;i++){
		if(!pp[i]){
			long long tmp = root(i,n);
			ans += (tmp - 1) * sign[i];
		}
	}
	return ans;
}

int main(){

	for(int i = 0;i <= 100;i++){
		sign[i] = 1;
	}

	ciur[0] = ciur[1] = 1;

	for(int p = 2;p <= 100;p++){
		if(!ciur[p]){
			sign[p] *= -1;
			for(int j = 2 * p;j <= 100;j += p){
				ciur[j] = 1;
				sign[j] *= -1;
			}
		}
	}

	for(int i = 1;i <= 10;i++){
		pp[i * i] = 1;
	}
	int T;
	
	cin >> T;

	while(T--){
		long long n;
		cin >> n;
		cout << solve(n) << "\n";
	}
	
	return 0;
}