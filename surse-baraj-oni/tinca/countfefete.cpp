#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_N = 200000;
const int MOD = 1000000007;
const int NBITS = 30;
int val[MAX_N];
vector<int> graph[1+MAX_N];
int nod[MAX_N];
int sef[1+MAX_N], dp[1+MAX_N][NBITS][2];

static inline int min(int a, int b) {
	if(a < b)
		return a;
	return b;
}

static inline int max(int a, int b) {
	if(a > b)
		return a;
	return b;
}

bool cmp(int a, int b) {
	return val[a] > val[b] || (val[a] == val[b] && a < b);
}

int myfind(int x) {
	if(sef[x] == x)
		return x;
	else {
		sef[x] = myfind(sef[x]);
		return sef[x];
	}
}

void myunion(int a, int b) {
	int sa = myfind(a), sb = myfind(b);
	if(sa != sb) {
		sef[sa] = sb;
		for(int i = 0; i < NBITS; ++i) {
			int aux[2];
			aux[0] = (((long long)dp[sa][i][0] * dp[sb][i][0] + (long long)dp[sa][i][1] * dp[sb][i][1])) % MOD;
			aux[1] = (((long long)dp[sa][i][0] * dp[sb][i][1] + (long long)dp[sa][i][1] * dp[sb][i][0])) % MOD;
			dp[sb][i][0] = ((long long)dp[sb][i][0] + dp[sa][i][0] + aux[0]) % MOD;
			dp[sb][i][1] = ((long long)dp[sb][i][1] + dp[sa][i][1] + aux[1]) % MOD;
		}
	}
}

int main() {
	int n, a, b, rez = 0;
	FILE *fin = fopen("countfefete.in", "r");
	fscanf(fin, "%d", &n);
	for(int i = 1; i <= n; ++i) {
		fscanf(fin, "%d", &val[i]);
		sef[i] = i;
		nod[i - 1] = i;
	}
	for(int i = 0; i < n - 1; ++i) {
		fscanf(fin, "%d%d", &a, &b);
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	fclose(fin);
	
	sort(nod, nod + n, cmp);

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < graph[nod[i]].size(); ++j) {
			int it = graph[nod[i]][j];
			int sa = myfind(nod[i]), sb = myfind(it);
			if(cmp(it, nod[i]) && sa != sb) {
				for(int b = 0; b < NBITS; ++b) {
					bool xd = ((val[nod[i]] & (1 << b)) > 0);
					int toadd = ((long long)dp[sa][b][0] * dp[sb][b][xd ^ 1] + 
											 (long long)dp[sa][b][1] * dp[sb][b][xd]) % MOD;
					rez = ((1LL << b) * toadd + rez) % MOD;
				}
				myunion(it, nod[i]);
			}
		}
		for(int b = 0; b < NBITS; ++b)
			if((val[nod[i]] & (1 << b)) > 0) {
				int aux[2];
				aux[0] = dp[nod[i]][b][1];
				aux[1] = (dp[nod[i]][b][0] + 1);
				dp[nod[i]][b][0] = (dp[nod[i]][b][0] + aux[0]) % MOD;
				dp[nod[i]][b][1] = (dp[nod[i]][b][1] + aux[1]) % MOD;
				rez = ((1LL << b) * aux[0] + rez) % MOD;
			} else {
				int aux[2];
				aux[0] = dp[nod[i]][b][0] + 1;
				aux[1] = dp[nod[i]][b][1];
				dp[nod[i]][b][0] = (dp[nod[i]][b][0] + aux[0]) % MOD;
				dp[nod[i]][b][1] = (dp[nod[i]][b][1] + aux[1]) % MOD;
				rez = ((1LL << b) * aux[1] + rez) % MOD;
			}
	}

	FILE *fout = fopen("countfefete.out", "w");
	fprintf(fout, "%d", rez);
	fclose(fout);
	return 0;
}


