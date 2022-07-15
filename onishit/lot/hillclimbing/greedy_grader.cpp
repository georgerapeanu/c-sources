#include <bits/stdc++.h>
using namespace std;

struct DSU {
	using ll = long long;

	struct usu {
		int st, dr, val;
	};

	struct cost_func {
		int le, pos;
		bool cap;

		int cost() const {
			if (cap) return 2 * le;
			return le;
		}

		bool operator < (const cost_func &aux)const {
			if (cost() != aux.cost()) return cost() > aux.cost();
			return cap > aux.cap;
		}
	};

	int n;
	vector <int> tt, sz;
	vector <usu> info;

	DSU (const int &_n, int V[]) : n(_n), tt(_n + 1), sz(_n + 1), info(_n + 1) {
		for (int i = 1; i <= n ; ++i)	{
			tt[i] = i;
			sz[i] = 1;
			info[i].st = i - 1; info[i].dr = i + 1;
      info[i].val = V[i - 1];
		}
	}

	int find(int x) {
		if (x != tt[x]) return tt[x] = find(tt[x]);
		return x;
	}

	void unite(int x, int y) {
		x = find(x); y = find(y);
		if (x == y) return ;

		if (sz[x] < sz[y]) swap(x, y);

		tt[y] = x;
		sz[x] += sz[y];
		info[x].st = min(info[x].st, info[y].st);
		info[x].dr = max(info[x].dr, info[y].dr);
		info[x].val = max(info[x].val, info[y].val);
	}

	ll solve(ll k) {
		ll ans = 0;
		for (int i = 1; i < n ; ++i)
			ans = ans + abs(info[i].val - info[i + 1].val);

		for (int i = 1; i <= n ; ++i) {
			while (i + 1 <= n && info[i].val == info[i + 1].val) {
				unite(i, i + 1);
				++i;
			}
		}

		priority_queue <cost_func> pq;
		for (int i = 1; i <= n ; ++i) {
			int val_left = -1, val_right = -1;
			int act = find(i);

			if (info[act].st >= 1) val_left = info[find(info[act].st)].val;

			if (info[act].dr <= n) val_right = info[find(info[act].dr)].val;

			if ((val_left == -1 || val_left > info[act].val) && (val_right == -1 || val_right > info[act].val)) {
				int le = info[act].dr - info[act].st - 1;
				bool cap = 0;
				if (val_left == -1 || val_right == -1)
					cap = 1;

				pq.push({le, act, cap});
			}

			i = info[act].dr - 1;
		}

		while (!pq.empty()) {
			int pos = pq.top().pos;
			int le = pq.top().le;
			bool cap = pq.top().cap;
			pq.pop();

			int val_left = -1, val_right = -1;
			int act = find(pos);

			if (info[act].st >= 1) val_left = info[find(info[act].st)].val;

			if (info[act].dr <= n) val_right = info[find(info[act].dr)].val;

			if (val_left == -1 && val_right == -1) break ;

			ll cnt = k / le;
			if (val_left != -1) cnt = min(cnt, 1LL * val_left - info[act].val);
			if (val_right != -1) cnt = min(cnt, 1LL * val_right - info[act].val);

			if (cnt == 0) continue ;

			k = k - cnt * le;
			if (cap) {
				ans = ans - cnt;
			} else {
				ans = ans - 2 * cnt;
			}

			if (val_left == -1) info[act].val = val_right;			
			else if (val_right == -1) info[act].val = val_left;			
			else info[act].val = min(val_left, val_right);

			if (val_left == info[act].val) 
				unite(act, info[act].st);
			
			if (val_right == info[act].val) 
				unite(act, info[act].dr);

			act = find(act);

			if (info[act].st >= 1) val_left = info[find(info[act].st)].val;
			else val_left = -1;

			if (info[act].dr <= n) val_right = info[find(info[act].dr)].val;
			else val_right = -1;

			if ((val_left == -1 || val_left > info[act].val) && (val_right == -1 || val_right > info[act].val)) {
				le = info[act].dr - info[act].st - 1;
				cap = 0;
				if (val_left == -1 || val_right == -1)
					cap = 1;

				pq.push({le, act, cap});
			}
		}

		return ans;
	}
};

long long solve(int n, long long k, int V[]) {
	DSU D(n, V);
  return D.solve(k);
}
