#include <bits/stdc++.h>

using namespace std;




int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;

  vector<int> v(n);

  for(auto &it: v) {
    cin >> it;
  }

  vector<vector<int>> dp(n, vector<int>(n, -1));

  auto reset_dp = [&]() {
    for(auto &it: dp) {
      for(auto &it2: it) {
        it2 = -1;
      }
    }
  };

  function<int(int, int, int)> get_answer = [&](int st, int dr, int sum) {
    if(dr - st < 1) {
      return 0;
    }

    if(dp[st][dr] == -1) {
      if(v[st] + v[st + 1] == sum) {
        dp[st][dr] = max(dp[st][dr], get_answer(st + 2, dr, sum) + 1);
      }
      if(v[dr] + v[dr - 1] == sum) {
        dp[st][dr] = max(dp[st][dr], get_answer(st, dr - 2, sum) + 1);
      }
      if(v[st] + v[dr] == sum) {
        dp[st][dr] = max(dp[st][dr], get_answer(st + 1, dr - 1, sum) + 1);
      }
      dp[st][dr] = max(dp[st][dr], 0);
    }
    return dp[st][dr];
  };
  
  int answer = 0;
  reset_dp();answer = max(answer, get_answer(2, n - 1, v[0] + v[1]));
  reset_dp();answer = max(answer, get_answer(0, n - 3, v[n - 2] + v[n - 1]));
  reset_dp();answer = max(answer, get_answer(1, n - 2, v[0] + v[n - 1]));
  answer += 1;
  answer *= 2;
  cout << answer << "\n";
  return 0;
}
