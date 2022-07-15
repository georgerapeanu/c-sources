#include "testlib.h"
#include <iostream>
 
using namespace std;
 
int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	
	int t = opt<int>("t");
	int n = opt<int>("n");
	long long k = opt<long long>("k");
  int vmax = opt<int>("vmax");
	
	cout << t << endl;
	while (t--) {
    	cout << n << " " << k << endl;
    
    	for (int i = 1; i <= n ; ++i) {
        if(i == 1 && i < n)cout << vmax << " ";
    		else if (i < n) cout << rnd.next(1, vmax) << " ";
    	  else cout << vmax << endl;
    	}
	}
	return 0;
}

