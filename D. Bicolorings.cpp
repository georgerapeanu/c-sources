#include <iostream>

using namespace std;

const int MOD = 998244353;

int dp[1005][2005][4];
int n,k;

void add(int &a,int b){
	a += b;
	if(a >= MOD){
		a -= MOD;
	}
}

void propaga(int i,int j){	
	add(dp[i + 1][j][0],dp[i][j][0]);
	add(dp[i + 1][j + 1][1],dp[i][j][0]);
	add(dp[i + 1][j + 1][2],dp[i][j][0]);
	add(dp[i + 1][j + 1][3],dp[i][j][0]);

	add(dp[i + 1][j][0],dp[i][j][1]);
	add(dp[i + 1][j][1],dp[i][j][1]);
	add(dp[i + 1][j + 2][2],dp[i][j][1]);
	add(dp[i + 1][j][3],dp[i][j][1]);

	add(dp[i + 1][j][0],dp[i][j][2]);
	add(dp[i + 1][j + 2][1],dp[i][j][2]);
	add(dp[i + 1][j][2],dp[i][j][2]);
	add(dp[i + 1][j][3],dp[i][j][2]);

	add(dp[i + 1][j + 1][0],dp[i][j][3]);
	add(dp[i + 1][j + 1][1],dp[i][j][3]);
	add(dp[i + 1][j + 1][2],dp[i][j][3]);
	add(dp[i + 1][j][3],dp[i][j][3]);
}

int main(){
	cin >> n >> k;
	dp[1][1][0] = dp[1][1][3] = 1;
	dp[1][2][1] = dp[1][2][2] = 1;
	for(int i = 1;i < n;i++){
		for(int j = 1;j <= 2 * i;j++){
			propaga(i,j);
		}
	}
	
	add(dp[n][k][0],dp[n][k][1]);
	add(dp[n][k][0],dp[n][k][2]);
	add(dp[n][k][0],dp[n][k][3]);
	cout << dp[n][k][0];
	return 0;
}