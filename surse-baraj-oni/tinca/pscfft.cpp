#include <cstdio>

const int MAX_N = 500000;
const int MOD = 1000000007;
int v[MAX_N], dv[MAX_N];
int pattern[MAX_N];

int getlgs(int n, int s) {
	int lgs = 0;
	while(n > 1) {
		lgs++;
		n /= s;
	}
	return lgs;
}

int lgput(int a, int b) {
	int ac = 1;
	while(b > 0) {
		if(b % 2 == 1)
			ac = (long long)ac * a % MOD;
		a = (long long)a * a % MOD;
		b /= 2;
	}
	return ac;
}

void solve(FILE *fin, FILE *fout) {
	int n, s;
	fscanf(fin, "%d%d", &n, &s);
	for(int i = 0; i < n; ++i)
		fscanf(fin, "%d", &v[i]);
	for(int i = 0; i < n - 1; ++i) {
		dv[i] = (s + v[i + 1] - v[i]) % s;
		pattern[i] = -1;
	}
	if(n == 1)
		fprintf(fout, "%d\n", v[0]);
	else {
		--n;
		int ps = 1, lgs = 1;
		while((long long)ps * s <= n) {
			ps = ps * s;
			++lgs;
		}

		int poz = 0;
		for(int i = 0; i < n; ++i)
			if(dv[i] > dv[poz])
				poz = i;
		
		if(dv[poz] >= lgs) { //check pattern
			int psc = ps;
			pattern[poz] = dv[poz];
			while(psc >= 1) {
				for(int i = poz; i < n; i += psc)
					if(pattern[i] == -1)
						pattern[i] = lgs;
				for(int i = poz; i >= 0; i -= psc)
					if(pattern[i] == -1)
						pattern[i] = lgs;
				psc /= s;
				lgs--;
			}

			for(int i = 0; i < n; ++i)
				if(pattern[i] != dv[i]) {
					fprintf(fout, "-1\n");
					return;
				}
			fprintf(fout, "%d\n", (long long)lgput(s, lgs - 1) * ((s - v[poz] - 1) % s + poz + 1) % MOD);
		} else {
			fprintf(fout, "-1\n");
			return;
		}
	}
}

int main() {
	int t;
	FILE *fin = fopen("pscfft.in", "r");
	FILE *fout = fopen("pscfft.out", "w");
	fscanf(fin, "%d", &t);
	while(t--) solve(fin, fout);
	fclose(fin);
	fclose(fout);
	return 0;
}

