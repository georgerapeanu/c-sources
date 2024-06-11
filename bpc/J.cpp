#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;

  vector<int> a(n, 0);
  vector<int> b(n, 0);

  for(auto &it: a) {
    cin >> it;
  }
  
  for(auto &it: b) {
    cin >> it;
  }

  
  vector<int> ord;
  for(int i = 0; i < n; i++) {
    ord.push_back(i);
  }

  sort(ord.begin(), ord.end(), [&](int i, int j) { return a[i] + b[i] > a[j] + b[j]; });

  long long sumA = 0;
  long long sumB = 0;
  for(int i = 0; i < n; i++) {
    if(!(i & 1)) {
      sumA += a[ord[i]];
    } else {
      sumB += b[ord[i]];
    }
  }

  if(sumA < sumB) {
    cout << "Bogdan";
  } else if(sumA > sumB) {
    cout << "Andrei";
  } else {
    cout << "amandoi";
  }

  return 0;
}
