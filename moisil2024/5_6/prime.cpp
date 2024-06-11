#include <bits/stdc++.h>
#ifndef LOCAL
#define dbg(args) // args
#else
#define dbg(args) cerr << #args << "=" << args;
#endif

using namespace std;

const int VMAX = 10000000;

int main() {

	freopen("prime.in", "r", stdin);
	freopen("prime.out", "w", stdout);
	
	int n, x;
	
	cin >> x;
	cin >> n;

	vector<bool> is_prime(VMAX + 1, true);
	is_prime[0] = is_prime[1] = false;
	
	for(int i = 2; 1LL * i * i <= VMAX; i++) {
		if(!is_prime[i]) {
			continue;
		}
		for(int j = i * i; j <= VMAX; j += i) {
			is_prime[j] = false;
		}
	}
	
	int _next = x;
	int count = 0;
	
	for(int i = 0; i < n; i++) {
		while(!is_prime[_next]) {
			_next++;
		}
		if(i & 1) {
			x -= _next;
		} else {
			x += _next;
		}
		_next++;
		count += is_prime[abs(x)];
	}
	
	dbg(x << count);
	
	cout << x << "\n";
	cout << count;

	return 0;
}
