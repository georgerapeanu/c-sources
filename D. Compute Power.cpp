#include <iostream>
#include <algorithm>
using namespace std;

const long long inf = 1LL << 60;
int N;
long long dp[55][55][55];
pair<long long,long long> V[55];

bool ok(long long val){
	for(int i = 0;i < 55;i++){
		for(int j = 0;j < 55;j++){
			for(int k = 0;k < 55;k++){
				dp[i][j][k] = inf;
			}
		}
	}
	dp[0][0][0] = 0;
	int lafel = 0;
	for(int i = 1;i <= N;i++){
		lafel = 1 + lafel * (V[i - 1].first == V[i].first);
		for(int j = 0;j <= N;j++){
			for(int k = 0;k <= lafel && k <= j;k++){
				if(lafel > 1){
					if(j && k){
						dp[i][j][k] = min(dp[i][j][k],dp[i - 1][j - 1][k - 1] + 1000 * V[i].first - val * V[i].second);
					}
					if(j + 1 > k){
						dp[i][j][k] = min(dp[i][j][k],dp[i - 1][j + 1][k]);
					}
				}
				else{
					if(k == 0){
						for(int orice = 0;orice <= N;orice++){
							dp[i][j][0] = min(dp[i][j][0],dp[i - 1][j + 1][orice]);
						}
					}
					else if(j){
						for(int orice = 0;orice <= N;orice++){
							dp[i][j][1] = min(dp[i][j][1],dp[i - 1][j - 1][orice] + 1000 * V[i].first - val * V[i].second);
						}
					}
				}
			}
		}
	}

	for(int j = 0;j <= N;j++){
		for(int k = 0;k <= N;k++){
			if(dp[N][j][k] <= 0){
				return 1;
			}
		}
	}
	return 0;
}

int main(){
	cin >> N;
	for(int i = 1;i <= N;i++){
		cin >> V[i].first;
	}
	for(int i = 1;i <= N;i++){
		cin >> V[i].second;
	}

	sort(V + 1,V + 1 + N);
	reverse(V + 1,V + 1 + N);

	long long st = -1,dr = (1e11) + 5;
	ok(1000);
	while(dr - st > 1){
		long long mid = (st + dr) / 2;
		if(ok(mid)){
			dr = mid;
		}
		else{
			st = mid;
		}
	}

	cout << dr;

	return 0;
}
