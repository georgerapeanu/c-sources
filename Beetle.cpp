#include <iostream>
#include <algorithm>

using namespace std;

int V[305];
long long dp[305][305][2];
long long T[305][305][2];

int best;
int N,M;

int main(){
	cin >> N >> M;

	bool Zero = 0;

	for(int i = 1;i <= N;i++){
		cin >> V[i];
		Zero |= (V[i] == 0);
	}

	if(!Zero){
		V[++N] = 0;
	}

	sort(V + 1,V + 1 + N);

	int Start = 0;

	for(int i = 1;i <= N;i++){
        dp[i][i][0] = dp[i][i][1] = (1LL << 58);
		if(V[i] == 0){
			Start = i;
		}
	}

	dp[Start][Start][0] = dp[Start][Start][1] = 0;

	for(int l = 1;l <= N;l++){
		for(int i = 1;i <= N - l;i++){
			int j = i + l;
			dp[i][j][0] = min(min(dp[i + 1][j][0] + V[i + 1] - V[i],dp[i + 1][j][1] + V[j] - V[i]),min(dp[i][j - 1][0] + (V[j] - V[i]),dp[i][j - 1][1] + V[j] - V[j - 1] + V[j] - V[i]));
			dp[i][j][1] = min(min(dp[i + 1][j][0] + V[i + 1] - V[i] + V[j] - V[i],dp[i + 1][j][1] + (V[j] - V[i])),min(dp[i][j - 1][0] + V[j] - V[i],dp[i][j - 1][1] + V[j] - V[j - 1]));
			T[i][j][0] = min(min(T[i + 1][j][0] + dp[i + 1][j][0] + V[i + 1] - V[i],T[i + 1][j][1] + dp[i + 1][j][1] + V[j] - V[i]),min(T[i][j - 1][0] + dp[i][j - 1][0] + (V[j] - V[i]),T[i][j - 1][1] + dp[i][j - 1][1] + V[j] - V[j - 1] + V[j] - V[i]));
			T[i][j][1] = min(min(T[i + 1][j][0] + dp[i + 1][j][0] + V[i + 1] - V[i] + V[j] - V[i],T[i + 1][j][1] + dp[i + 1][j][1] + (V[j] - V[i])),min(T[i][j - 1][0] + dp[i][j - 1][0] + V[j] - V[i],T[i][j - 1][1] + dp[i][j - 1][1] + V[j] - V[j - 1]));
			dp[i][j][0] = min(dp[i][j][0],1LL << 58);
			T[i][j][0] = min(T[i][j][0],1LL << 58);
			dp[i][j][1] = min(dp[i][j][1],1LL << 58);
			T[i][j][1] = min(T[i][j][1],1LL << 58);
		}
	}

	long long best = 0;

	for(int i = 1;i <= N;i++){
		for(int j = i;j <= N;j++){
			long long sum = min(T[i][j][0],T[i][j][1]);
			best = max(best,1LL * (j - i + 1) * M - sum);
		}
	}

	cout << best - M * (Zero == 0);

	return 0;
}
