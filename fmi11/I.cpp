#include <bits/stdc++.h>

using namespace std;

int main(){

  int n;
  scanf("%d", &n);

  vector<pair<int, int> > v(n);

  for(auto &it:v){
    scanf("%d %d", &it.first, &it.second);
    if(it.first > it.second){
      swap(it.first, it.second);
    }
  }

  sort(v.begin(), v.end());

  int maximum = 0;
  int minimum = 1e9;

  for(auto &it:v){
    maximum = max(maximum, it.first);
  }

  int answer = 1e9;

  for(int i = 0;i < (int)v.size();i++){
    answer = min(answer, maximum - min(minimum, v[i].first)); 
    minimum = min(minimum, v[i].second);
    maximum = max(maximum, v[i].second);
  }

  answer = min(answer, maximum - minimum);

  printf("%d\n", answer);

  return 0;
}
