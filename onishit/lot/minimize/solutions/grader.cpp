#include "minimize.h"
#include <iostream>
#include <vector>

int main() {
  std::cin.tie(NULL);
  std::ios_base::sync_with_stdio(false);

  // Note that every vector is 1 indexed
  
  int n, k;
  std::cin >> n >> k;
  std::vector <int> a(n + 1, 0);
  for (int i = 1; i <= n ; ++i)
    std::cin >> a[i];

  initialize(n, k, a);

  int q;
  std::cin >> q;

  /* 
    0 - query
    1 - update 

    update structure:
    1 pos val
  */

  std::vector <long long> ans;
  for (; q > 0 ; --q) {
    int type;
    std::cin >> type;
    if (type == 1) {
      // update nr positions
      int pos, val;
      std::cin >> pos >> val;

      if (pos < 0 || pos > n) {
        std::cerr << "BAD UPDATE INDEX" << std::endl;
        exit(1);
      }

      modify(pos, val);
    } else if (type == 0) {
      // query
      ans.push_back(calculate());
    } else {
      // bad operation type
      std::cerr << "BAD OPERATION TYPE" << std::endl;
      exit(1);
    }
  }

  for (auto it : ans) {
    std::cout << it << " ";
  
    if (it < 0) {
        std::cerr << "FOUND NEGATIVE ANSWER\n";
        exit(1);
    }
  }

  std::cout << "\n";
  
  return 0;
}
