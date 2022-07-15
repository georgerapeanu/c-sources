#include "testlib.h"
#include <bits/stdc++.h>
 
using namespace std;

vector<int> generate_buckets_sqrt(int vmax, int n){
  vector<int> perm(n, 0);
  for(int i = 0;i < n;i++){
    perm[i] = rnd.next(1, vmax);
  }
  int target = sqrt(n);
  int idx = 0;

  while(idx < n){
    shuffle(perm.begin() + idx, perm.end());
    sort(perm.begin() + idx, perm.begin() + min(idx + target, n));
    if(rnd.next(0, 1)){
      reverse(perm.begin() + idx, perm.begin() + min(idx + target, n));
    }
    idx += target;
  }

  return perm;
}


int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	
	int t = opt<int>("t");
	int n = opt<int>("n");
	long long k = opt<long long>("k");
  int vmax = opt<int>("vmax");
	
	cout << t << endl;
	while (t--) {
    	cout << n << " " << k << endl;
      vector<int> v = generate_buckets_sqrt(vmax, n);
    	for (int i = 1; i <= n ; ++i) {
    		if (i < n) cout << v[i - 1] << " ";
    	    else cout << v[i - 1] << endl;
    	}
	}
	return 0;
}

