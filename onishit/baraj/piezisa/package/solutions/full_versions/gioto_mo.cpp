#include "piezisa.h"
#include <bits/stdc++.h>
using namespace std;

constexpr int rad = 300;
constexpr int INF = 1e9;

struct query {
	int l, r, pos;
};

namespace black_box {
	int ans;
	vector <int> left_best, right_best;
	stack <pair <int, int>> undo_stack;

	inline void init(int valmax) {
		left_best.resize(valmax);
		right_best.resize(valmax);

		fill(left_best.begin(), left_best.end(), -2);
		fill(right_best.begin(), right_best.end(), -2);

		left_best[0] = -1;
	}

	inline void add_left(int pos, int val) {
		undo_stack.push({left_best[val], ans});

		left_best[val] = pos;	
		if (right_best[val] != -2)
			ans = min(ans, right_best[val] - left_best[val]);
	}

	inline void add_right(int pos, int val) {
		right_best[val] = pos;
		if (left_best[val] != -2)
			ans = min(ans, right_best[val] - left_best[val]);
	}

	inline void undo(int val) {
		left_best[val] = undo_stack.top().first;
		ans = undo_stack.top().second;
		undo_stack.pop();
	}

	inline void clear() {
		fill(left_best.begin(), left_best.end(), -2);
		fill(right_best.begin(), right_best.end(), -2);

		left_best[0] = -1;

		while (!undo_stack.empty())
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
	vector <int> a(n), b(n);
	for (int i = 0; i < n ; ++i) {
		static int last = 0;

		a[i] = v[i] ^ last;
		last ^= v[i];
	}

	norm(a);

	vector <query> my_q(q);
	for (int i = 0; i < q ; ++i) {
		my_q[i].l = l[i];
		my_q[i].r = r[i];
		my_q[i].pos = i;
	}

	sort(my_q.begin(), my_q.end(),
		[](query &x, query &y) {
			if (x.l / rad != y.l / rad)
				return x.l < y.l;

			return x.r > y.r;
		}
	);

	black_box::init(n + 1);
	black_box::ans = n + 1;

	for (auto it : my_q) {
		static int l, r, lb, last = -1;	
		if (it.l / rad != last) {
			lb = it.l / rad * rad;

			black_box::clear();
			black_box::ans = n + 1;
			for (int i = 0; i < lb ; ++i)
				black_box::add_left(i, a[i]);

			l = lb;
			r = n;

			last = it.l / rad;
		}
		
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

	return;
}
