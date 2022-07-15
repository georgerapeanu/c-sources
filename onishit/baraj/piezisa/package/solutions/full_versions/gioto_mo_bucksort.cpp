#include "piezisa.h"
#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 1e9;

struct query {
	int l, r, pos;
};

namespace black_box {
	const int DIM = 5e5 + 5;
	int valmax;
	int ans;
	int left_best[DIM], right_best[DIM];
	stack <pair <int, int>> undo_stack;

	inline void init(int _valmax) {
		valmax = _valmax;
		memset(left_best, -0x3f, sizeof(int) * valmax);
		memset(right_best, -0x3f, sizeof(int) * valmax);

		left_best[0] = -1;
	}

	inline void add_left(int &pos, int &val) {
		undo_stack.push({left_best[val], ans});

		left_best[val] = pos;	
		if (right_best[val] > -2)
			ans = min(ans, right_best[val] - left_best[val]);
	}

	inline void add_right(int &pos, int &val) {
		right_best[val] = pos;
		if (left_best[val] > -2)
			ans = min(ans, right_best[val] - left_best[val]);
	}

	inline void remove_right(int &pos, int &val) {
		right_best[val] = -3;
	}


	inline void undo(int &val) {
		left_best[val] = undo_stack.top().first;
		ans = undo_stack.top().second;
		undo_stack.pop();
	}
}

inline void norm(vector <int> &a) {
	vector <int> b(a.size() + 1, 0);
	copy(a.begin(), a.end(), b.begin() + 1);

	sort(b.begin(), b.end());
	b.erase(unique(b.begin(), b.end()), b.end());

	for (auto &it : a)
		it = lower_bound(b.begin(), b.end(), it) - b.begin();
}


void solve(int n, int v[], int q, int l[], int r[], int solutions[]){
	int rad = n / sqrt(q);
	if (rad <= 5)
	    rad = 69;

	vector <int> a(n);
	for (int i = 0; i < n ; ++i) {
		static int last = 0;

		a[i] = v[i] ^ last;
		last ^= v[i];
	}

	norm(a);

	vector <vector <query>> my_q((n + rad - 1) / rad);
	for (int i = 0; i < q ; ++i) {
		int buck = l[i] / rad;
		my_q[buck].push_back({l[i], r[i], i});
	}


	black_box::init(n + 1);
	black_box::ans = n + 1;

	for (auto &buck : my_q) {
		static int l = 0;
		if (buck.empty())
			continue;

		sort(buck.begin(), buck.end(),
			[&rad](query &x, query &y) {
				if (x.l / rad != y.l / rad)
					return x.l < y.l;

				return x.r > y.r;
			}
		);

		int r, lb = buck[0].l / rad * rad;	

		//black_box::clear();
		black_box::ans = n + 1;
		while (l < lb)
				black_box::add_left(l, a[l]), ++l;

		r = n;

		for (auto &it : buck) { 
			while (r > it.r)
				--r, black_box::add_right(r, a[r]);

			while (l < it.l)
				black_box::add_left(l, a[l]), ++l;

			solutions[it.pos] = black_box::ans;
			if (solutions[it.pos] == n + 1)
				solutions[it.pos] = -1;

			while (l > lb)
				black_box::undo(a[--l]);
		}

		while (r < n)
			black_box::remove_right(r, a[r]), ++r;
	}

	return;
}

