#include "testlib.h"
#include <iostream>
#include <cassert>

using namespace std;
 
int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	
	int t = opt<int>("t");
	int n = opt<int>("n");
	long long k = opt<long long>("k");
    int vmax = opt<int>("vmax");
    assert(t <= n);
	cout << t << endl;
	int bad = 0;
    for(int i = 1;i <= t;i++) {
      int local_n = rnd.next((i == t ? n - (t - i):1), n - (t - i));
      n -= local_n;
      long long local_k = rnd.next(1LL, k);
      vector <int> v(local_n + 1, 0);
        long long tot = 0, mx = 0;
        for (int i = 1; i <= local_n ; ++i) {
    		v[i] = rnd.next(1, vmax);
    		mx = max(mx, 1LL * v[i]);
    	}
        for (int i = 1; i <= local_n ; ++i)
            tot = tot + abs(mx - v[i]);
        if (tot <= local_k) {
            ++bad;
            if (bad >= 100) {
                local_k = 0;
            } else {
                ++t; n += local_n;
                continue;
            }
        }
    	cout << local_n << " " << 0 << endl;
    
    	for (int i = 1; i <= local_n ; ++i) {
    		if (i < local_n) cout << v[i] << " ";
    	    else cout << v[i] << endl;
    	}
	}
	return 0;
}


