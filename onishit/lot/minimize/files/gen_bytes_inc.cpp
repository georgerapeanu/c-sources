// THIS GENERATOR WON'T BEHAVE WELL WITH SMALL N
// BUT IT WORKS LMAO
#include "testlib.h"
#include <vector>
using namespace std;
 
struct interv {
  int l, len, b;
};

int main(int argc, char** argv){
  registerGen(argc, argv, 1);
  int n = opt<int>("n");
  int k = opt<int>("k");
  int qm = opt<int>("qm");
  int qi = opt<int>("qi");
  int nrb = opt<int>("nrb"); // the number of bytes, this is equivalent to vmax
  int buck_sz = opt <int> ("buck_sz"); // the size of the buckets
  int vmax = (1LL << nrb) - 1;
 
  printf("%d %d\n", n, k);

  int groups = n / (buck_sz + 1);
  if (groups == 0) {
    fprintf(stderr, "FAILED TO GENERATE TEST\n");
    exit(1);
  }

  int used_b = 0; // the number of bytes I strictly need
  for (int len = k; len >= 1 ; --len)
    ++used_b;
  int out = nrb - used_b; 

  vector <int> v(n + 1, 0);

  // place some random values with useless bytes
  if (out > 0) {
    int mx = (1 << out) - 1;
    for(int i = 1;i <= n;i++){
      v[i] = rnd.next(0, mx);
    }
  }


  vector <int> g;
  int l = 1;
  for (int i = 1; i <= groups ; ++i) {
    int rem = groups - i + 1;
    int need = rem * (buck_sz + 1);
    l = rnd.next(l, n - need + 1);
    g.push_back(l);

    l = l + buck_sz + 1;
  }

  vector <interv> I;
  for (auto it : g) {
    int st = it, dr = it + buck_sz - 1;
    for (int len = k, b = nrb; len >= 1 && b >= 0 ; len--, --b) {
      int up = dr - len + 1;
      int low = rnd.next(st, up);
      I.push_back({up, len, b});
      for (int j = low; j <= low + len - 1 ; ++j) {
        v[j] |= (1 << b);
      }
    }
  }

  for (int i = 1; i <= n ; ++i) {
    printf("%d", v[i]);
    if (i < n)
      printf(" ");
  }

  printf("\n");
  printf("%d\n", qm + qi);
 
  if (qi > 1) {
    printf("0\n");
    --qi;
  }

  vector <int> q;
  for (int i = 0; i < qm ; ++i)
    q.push_back(1);
  for (int i = 0; i < qi - 1 ; ++i)
    q.push_back(0);
 
  shuffle(q.begin(), q.end());
  q.push_back(0);
  
  for (auto it : q) {
      printf("%d", it);
      if (it == 1)
        printf(" %d %d", rnd.next(1, n), rnd.next(0, vmax));
      printf("\n");
  }

  return 0;
}

