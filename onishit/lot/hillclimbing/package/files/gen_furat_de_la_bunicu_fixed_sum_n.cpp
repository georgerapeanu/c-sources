#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

vector<int> generate_special(int vmax, int n,int a,int b, int x, int y, int z){
  
  assert(n == a + b);

  vector<int> perm(n, 0);
  for(int i = 0;i < n;i++){
    perm[i] = i + 1;
  }
  shuffle(perm.begin(),perm.end());

  vector<vector<int> > asc_sequences(x, vector<int>());
  vector<vector<int> > desc_sequences(y, vector<int>());

  for(int i = 0;i < n;i++){
    if(i < a){
      asc_sequences[rnd.next((int)asc_sequences.size())].push_back(perm[i]);
    }else{
      desc_sequences[rnd.next((int)desc_sequences.size())].push_back(perm[i]);
    }
  }

  vector<int> asc_sequence;
  vector<int> desc_sequence;

  for(auto &sequence:asc_sequences){
    sort(sequence.begin(), sequence.end());
    for(auto it:sequence){
      asc_sequence.push_back(it);
    }
  }
  
  for(auto &sequence:desc_sequences){
    sort(sequence.begin(), sequence.end());
    reverse(sequence.begin(), sequence.end());
    for(auto it:sequence){
      desc_sequence.push_back(it);
    }
  }

  vector<int> merge_types;

  for(int i = 0;i < n;i++){
    merge_types.push_back(i < a);
  }

  shuffle(merge_types.begin(), merge_types.end());

  vector<int> merge_order;

  int nxt_a = 0;
  int nxt_b = 0;

  for(int i = 0;i < n;i++){
    if(merge_types[i]){
       merge_order.push_back(asc_sequence[nxt_a++]);
    }else{
       merge_order.push_back(desc_sequence[nxt_b++]);
    }
  }

  for(int i = 0;i < n;i++){
    if(rnd.next(100) < z){
      merge_order[i] = rnd.next(1, vmax);
    }
  }

  return merge_order;
}

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
      

      int a = rnd.next(0, local_n);
      vector<int> v = generate_special(vmax, local_n, a, local_n - a, rnd.next(2, 10), rnd.next(2, 10), rnd.next(10, 20));
        int mx = 0;
        for (int i = 0; i < local_n ; ++i)
            mx = max(mx, v[i]);
        long long tot = 0;
        for (int i = 0; i < local_n ; ++i)
            tot = tot + abs(mx - v[i]);
        if (tot <= local_k) {
            ++bad;
            if (bad >= 100) {
                local_k = tot / 2;
            } else {
                ++t; n += local_n;
                continue;
            }        
        }
        cout << local_n << " " << local_k << endl;
      assert(v.size() == local_n);
    	for (int i = 1; i <= local_n ; ++i) {
    		if (i < local_n) cout << v[i - 1] << " ";
    	    else cout << v[i - 1] << endl;
    	}
	}
	return 0;
}

