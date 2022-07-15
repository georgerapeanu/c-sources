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
    assert(t <= n);
	cout << t << endl;
  for(int i = 1;i <= t;i++) {
      int local_n = rnd.next((i == t ? n - (t - i):1), n - (t - i));
      n -= local_n;
      long long local_k = rnd.next(1LL, k);
    	cout << local_n << " " << local_k << endl;
    
      int a = rnd.next(0, local_n);
      vector<int> v = generate_buckets_sqrt(vmax, local_n);
    	for (int i = 1; i <= local_n ; ++i) {
    		if (i < local_n) cout << v[i - 1] << " ";
    	    else cout << v[i - 1] << endl;
    	}
	}
	return 0;
}

