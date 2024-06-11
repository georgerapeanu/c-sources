#include <bits/stdc++.h>
#ifndef LOCAL
#define dbg(args) // args
#else
#define dbg(args) cerr << #args << "=" << args;
#endif

using namespace std;

int main() {
	
	int n;
	int s, d;
	int k;
	
	freopen("sub2max.in", "r", stdin);
	freopen("sub2max.out", "w", stdout);
	
	cin >> n >> s >> d >> k;
	vector<pair<long long, int> > pref_sums(n + 1);
	vector<long long> raw_pref_sums(n + 1);
	
	for(int i = 1; i <= n; i++) {
		cin >> pref_sums[i].first;
		pref_sums[i].first += pref_sums[i - 1].first;
		pref_sums[i].second = i;
		raw_pref_sums[i] = pref_sums[i].first;
	}
	
	sort(pref_sums.begin(), pref_sums.end());
	
	long long biggest_pow = k;
	
	if(k != 1) {
		while(1LL * biggest_pow * k <= 100000000000LL) {
			biggest_pow *= k;
		}
	}
	int ans_1 = -1;
	int ans_length = 1e9;
	int ans_2 = -1;
	
	while(biggest_pow > 0) {
		for(int i = 0; i < (int)pref_sums.size(); i++) {
			int left = lower_bound(pref_sums.begin(), pref_sums.end(), make_pair(pref_sums[i].first + biggest_pow, -1)) - pref_sums.begin();
			int right = lower_bound(pref_sums.begin(), pref_sums.end(), make_pair(pref_sums[i].first + biggest_pow + 1, -1)) - pref_sums.begin();
			int idx = lower_bound(pref_sums.begin() + left, pref_sums.begin() + right, make_pair(pref_sums[i].first + biggest_pow, pref_sums[i].second + s)) - pref_sums.begin();
			
			if(idx < 0 || idx >= (int)pref_sums.size() || pref_sums[idx].first - pref_sums[i].first != biggest_pow || pref_sums[idx].second - pref_sums[i].second < s || pref_sums[idx].second - pref_sums[i].second > d) {
				continue;
			}
			
			int start = pref_sums[i].second + 1;
			int end = pref_sums[idx].second;
			
			if(ans_1 < biggest_pow) {
				ans_1 = biggest_pow;
				ans_2 = start;
				ans_length = end - start + 1;
			} else if(ans_1 == biggest_pow && ans_length > end - start + 1) {
				ans_2 = start;
				ans_length = end - start + 1;
			} else if(ans_1 == biggest_pow && ans_length == end - start + 1 && ans_2 < start) {
				ans_2 = start;
			}
			
		}
		biggest_pow /= k;
		if(k == 1) {
			break;
		}
	}
	
	cout << ans_1 << " ";
	cout << ans_2;
	
	return 0;
}
