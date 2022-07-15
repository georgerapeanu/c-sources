#include "testlib.h"
#include <iostream>
#include <vector>
using namespace std;
 
int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	
	int t = opt<int>("t");
	int n = opt<int>("n");
	long long k = opt<long long>("k");
  int vmax = opt<int>("vmax");
	
	cout << t << endl;
	int bad = 0;
	while (t--) {
	    
        vector <int> v(n + 1, 0);
        long long tot = 0, mx = 0;
        for (int i = 1; i <= n ; ++i) {
    		v[i] = rnd.next(1, vmax);
    		mx = max(mx, 1LL * v[i]);
    	}
    	for (int i = 1; i <= n ; ++i) 
    	    tot = tot + abs(mx - v[i]);
    	
    	if (tot <= k) {
    	    ++bad;
    	    if (bad >= 100) {
    	       k = tot / 2; 
    	    } else {
    	        ++t;
    	        continue;
    	    }
    	        
    	 }
    	cout << n << " " << k << endl;
    
    	for (int i = 1; i <= n ; ++i) {
    		if (i < n) cout << v[i] << " ";
    	    else cout << v[i] << endl;
    	}
	}
	return 0;
}

