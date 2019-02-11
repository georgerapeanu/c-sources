#include <cstdio>

const int MAX_F = 20;
const int MAX_LAYER = (1<<(MAX_F - 1));
const int MOD = 1000000007;
int dp[MAX_F][MAX_LAYER];

int main() {
	int f, t, a, b;
	FILE *fin = fopen("fft2d.in", "r");
	fscanf(fin, "%d%d", &f, &t);
	for(int i = 0; i < t; ++i) {
		fscanf(fin, "%d%d", &a, &b);
		dp[a][b] = -1;
	}
	fclose(fin);
	
	for(int i = 0; i < (1 << (f - 1)); ++i)
		if(dp[f - 1][i] == -1)
			dp[f - 1][i] = 0;
		else
			dp[f - 1][i] = 1;
	
	for(int i = f - 2; i >= 0; --i) {
		int xd = (1 << (f - i - 2));
		for(int j = 0; j < (1 << (f - 1)); ++j)
			if(dp[i][j] == -1)
				dp[i][j] = 0;
			else
				dp[i][j] = (dp[i + 1][j] + dp[i + 1][j ^ xd]) % MOD;
	}
	
	int rez = 0;
	for(int i = 0; i < (1 << (f - 1)); ++i)
		rez = (rez + dp[0][i]) % MOD;
	FILE *fout = fopen("fft2d.out", "w");
	fprintf(fout, "%d", rez);
	fclose(fout);
	return 0;
}

