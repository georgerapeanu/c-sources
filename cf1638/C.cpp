#include <bits/stdc++.h>

using namespace std;

int main(){
  
  int t;
  scanf("%d", &t);

  while(t--){
    int n;
    scanf("%d", &n);
    
    vector<int> v(n, 0);

    vector<int> max_stack;
    for(auto &it:v){
      scanf("%d", &it);
      int __max = it;

      while(max_stack.empty() == false && max_stack.back() > it){
        __max = max(__max, max_stack.back());
        max_stack.pop_back();
      }
      max_stack.push_back(__max);
    }

    printf("%d\n", (int)max_stack.size());
  }

  return 0;
}
