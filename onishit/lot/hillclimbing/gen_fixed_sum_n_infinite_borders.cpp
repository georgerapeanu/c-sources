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
  for(int i = 1;i <= t;i++) {
      int local_n = rnd.next((i == t ? n - (t - i):1), n - (t - i));
      n -= local_n;
      long long local_k = rnd.next(1LL, k);
    	cout << local_n << " " << local_k << endl;
    
    	for (int i = 1; i <= local_n ; ++i) {
        if(i == 1 && i != local_n) cout << vmax << " ";
    		else if (i < local_n) cout << rnd.next(1, vmax) << " ";
    	    else cout << vmax << endl;
    	}
	}
	return 0;
}


