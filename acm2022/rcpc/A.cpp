#include <bits/stdc++.h>

using namespace std;

int main(){

  int l, d, n;

  cin >> l >> d >> n;

  vector<int> rocks(n, 0);

  for(auto &it:rocks){
    cin >> it;
  }
  rocks.push_back(0);
  rocks.push_back(l);

  sort(rocks.begin(), rocks.end());

  int ans = 0;

  for(int i = 0;i + 1 < (int)rocks.size();i++){
    if(i != 0 && i + 1 != (int)rocks.size() - 1){
      ans += max((rocks[i + 1] - rocks[i]) / d - 1, 0);
    } else if (i != 0 || i + 1 != (int)rocks.size() - 1){
      ans += max((rocks[i + 1] - rocks[i] - 6) / d, 0);
    } else {
      ans += max((rocks[i + 1] - rocks[i] - 12) / d + 1, 0);
    }
  }

  cout << ans << "\n";

  return 0;
}
