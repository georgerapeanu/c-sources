#include "piezisa.h"
#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 1e9;
constexpr int rad = 1000;

struct query {
	int l, r, pos;
};

inline void norm(vector <int> &a) {
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

	vector <int> left(n + 1, -1); 
	for (int i = 0; i < n && i < rad ; ++i)
		left[a[i]] = i;
		
	for (int i = 0; i < q ; ++i) {
		--l[i];
		int ans = n + 1;
		for (int x = max(l[i] - rad, 0); x <= l[i] ; ++x)
			left[a[x]] = x;

		for (int y = r[i]; y < r[i] + rad && y < n ; ++y) {
			if (a[y] == 0)
				ans = min(ans, y + 1);

			if (left[a[y]] <= l[i] && left[a[y]] >= 0)
				ans = min(ans, y - left[a[y]]);
		}

		if (ans == n + 1)
			ans = -1;

		solutions[i] = ans;
	}

}


