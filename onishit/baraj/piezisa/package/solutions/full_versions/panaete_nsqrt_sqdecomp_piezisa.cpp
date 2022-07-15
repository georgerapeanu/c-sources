#include "piezisa.h"
#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 1e9;
constexpr int DIM = 5e5;
constexpr int rad = 1000;

int best[(DIM + rad - 1) / rad][DIM];
int nx[DIM + 1];

inline void norm(vector <int> &a) {
	// makes sure that we have 0 in our set
	vector <int> b(a.size() + 1, 0);
	copy(a.begin(), a.end(), b.begin() + 1);

	sort(b.begin(), b.end());
	b.erase(unique(b.begin(), b.end()), b.end());

	for (auto &it : a)
		it = lower_bound(b.begin(), b.end(), it) - b.begin();
}

void solve(int n, int v[], int q, int l[], int r[], int solutions[]){
	vector <int> a(n);
	for (int i = 0; i < n ; ++i) {
		static int last = 0;

		a[i] = v[i] ^ last;
		last ^= v[i];
	}

	norm(a);

	int mx = 0;
	for (auto it : a)
		mx = max(it, mx);

	int n_buck = (n + rad - 1) / rad;

	// prec right
	memset(nx, -0x3f, sizeof(nx));
	for (int buck = 0; buck < n_buck ; ++buck) {
		int l = buck * rad, r = min(l + rad - 1, n - 1);
		for (int i = l; i <= r ; ++i)
			nx[a[i]] = i;

		for (int i = n - 1; i > r ; --i) {
			best[buck][i] = n + 1;

			best[buck][i] = min(best[buck][i], i - nx[a[i]]);

			if (buck - 1 >= 0)
				best[buck][i] = min(best[buck][i], best[buck - 1][i]);

			if (i + 1 < n)
				best[buck][i] = min(best[buck][i], best[buck][i + 1]);
		}
	}

	// prec left
	memset(nx, 0x3f, sizeof(nx));
	for (int buck = n_buck - 1; buck >= 1 ; --buck) {
		int l = buck * rad, r = min(l + rad - 1, n - 1);
		for (int i = r; i >= l ; --i)
			nx[a[i]] = i;

		for (int i = 0; i < l ; ++i) {
			best[buck][i] = n + 1;

			best[buck][i] = min(best[buck][i], nx[a[i]] - i);

			if (buck < n_buck - 1)
				best[buck][i] = min(best[buck][i], best[buck + 1][i]);

			if (i > 0)
				best[buck][i] = min(best[buck][i], best[buck][i - 1]);
		}
	}	

	vector <int> zero(n, n + 1);
	if (a[n - 1] == 0)
		zero[n - 1] = n;

	for (int i = n - 2; i >= 0 ; --i) {
		zero[i] = zero[i + 1];
		if (a[i] == 0)
			zero[i] = i + 1;
	}

	for (int i = 0; i < q ; ++i) {
		static vector <int> last(n + 1, -2);
		int lb, rb;

		--l[i];
		if (l[i] == -1) {
			solutions[i] = zero[r[i]];
			if (solutions[i] == n + 1)
				solutions[i] = -1;
			continue;
		}

		lb = l[i] / rad;
		rb = r[i] / rad;

		int ans = zero[r[i]];
		if (lb - 1 >= 0)
			ans = min(ans, best[lb - 1][r[i]]);

		if (rb + 1 < n_buck)
			ans = min(ans, best[rb + 1][l[i]]);

		int ll = lb * rad, lr = l[i];
		int rl = r[i], rr = min((rb + 1) * rad - 1, n - 1);

		if (lb != rb && ll + rad - 1 == lr) {
			ans = min(ans, best[lb][r[i]]);
		} else if (lb != rb && rl % rad == 0 && min(rl + rad - 1, n - 1) == rr) {
			ans = min(ans, best[rb][l[i]]);
		} else {
			for (int i = ll; i <= lr ; ++i)
				last[a[i]] = i;

			for (int i = rl; i <= rr ; ++i)
				if (last[a[i]] >= ll && last[a[i]] <= lr)
					ans = min(ans, i - last[a[i]]);
		}

		if (ans == n + 1)
			ans = -1;

		solutions[i] = ans;
	}

	return;
}


