#include <bits/stdc++.h>

using namespace std;

vector<int> getSolution(const vector<string> &words, int height, int w){
  vector<int> dp((int)words.size(), -1);
  vector<int> ant(dp.size(), -1);
  int max_width = 0;
  for(int i = 0;i < height;i++){
    max_width = max(max_width, (int)words[i].size());
    dp[i] = w - max_width;
  }

  for(int i = 0;i < (int)dp.size();i++){
    if(dp[i] < 0){
      continue;
    }
    int max_width = 0;
    for(int j = i + 1;j < (int)dp.size() && j <= i + height;j++){
      max_width = max(max_width, (int)words[j].size());
      if(dp[j] < dp[i] - max_width - 1){
        dp[j] = dp[i] - max_width - 1;
        ant[j] = i;
      }
    }
  }

  if(dp.back() == -1){
    return {};
  }
  vector<int> answer = {(int)dp.size() - 1};
  while(true){
    if(ant[answer.back()] < 0){
      break;
    }
    answer.push_back(ant[answer.back()]);
  }
  reverse(answer.begin(), answer.end());
  return answer;
}

string pad(string s, int w){
  string answer = s;
  while((int)answer.size() < w){
    answer += " ";
  }
  return answer;
}

int main(){

  int n, w;
  cin >> n >> w;

  vector<string> v(n);

  for(auto &it:v){
    cin >> it;
  }

  sort(v.begin(), v.end());
  
  int low = -1;
  int high = n + 1;

  
  while(high - low > 1){
    int mid = (low + high) / 2;
    if(getSolution(v, mid, w).size() > 0){
      high = mid;
    } else {
      low = mid;
    }
  }

  vector<int> indexes = getSolution(v, high, w);

  vector<string> answer(high, "");
  int last_index = -1;;
  vector<int> widths;
  for(auto it:indexes){
    int max_width = 0;
    for(int j = last_index + 1;j <= it;j++){
      max_width = max(max_width, (int)v[j].size());
    }
    widths.push_back(max_width);
    if(it < n - 1){
      max_width++;
    }
    for(int j = 0;j < high;j++){
      answer[j] += pad((last_index + 1 + j <= it ? v[last_index + 1 + j]:""), max_width);
    }
    last_index = it;
  }
  
  cout << answer.size() << " " << widths.size() << "\n";
  for(auto it:widths){
    cout << it << " ";
  }
  cout << "\n";
  for(auto it:answer){
    cout << it << "\n";
  }

  return 0;
}
