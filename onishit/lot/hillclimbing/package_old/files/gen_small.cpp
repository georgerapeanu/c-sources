#include "testlib.h"
#include <iostream>

using namespace std;

const int DIM = 2e5 + 5;

int a[DIM];

void back(int &nr, const int &t, const int &n, int i) {
	if (i == n) {
		for (int k = 0; k <= 1LL * n * (n - 1) ; ++k) {
			++nr;
			if (nr > t) exit(0);

			cout << n << " " << k << endl;
			for (int i = 1; i <= n ; ++i) {
				if (i < n) cout << a[i] << " ";
				else cout << a[i] << endl;
			}
		}

		return ;
	}

	for (int val = 1; val <= n ; ++val) {
		a[i + 1] = val;
		back(nr, t, n, i + 1);
		a[i + 1] = 0;
	}
}

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	int t = opt<int>("t"); 
	int n = opt<int>("n");

	cout << t << endl;

	int nr = 0;
	back(nr, t, n, 0);
	return 0;
}
