#include "monster.h"
#include <chrono>
#include <algorithm>
#include <map>
#include <random>
#include <cassert>

namespace {

  std::map<std::pair<int, int>, int > query_results;

  int my_query(int a, int b){
    if(a > b){
      std::swap(a, b);
    }
    if(query_results.count({a, b}) == 0){
       query_results[{a, b}] = (Query(a, b) ? b:a);
    }
    printf("query %d %d loser is %d\n", a, b, query_results[{a,b}]);
    return query_results[{a, b}];
  }

  void my_sort(std::vector<int> &v, int l, int r, std::vector<int> &values){
    printf("debug %d %d\n", l, r);
    for(auto it:v)printf("%d " ,it);printf("\n");
    for(auto it:values)printf("%d " ,it);printf("\n");
    if(r - l <= 1){
      return ;
    }
    int cnt = 0;
    for(int i = l + 1;i < r;i++){
      if(my_query(v[l], v[i]) == v[i]){
         cnt++;
      }
    }
    std::swap(v[l], v[l + cnt]);
    int lst_available = l;
    for(int i = l;i < r;i++){
      if(i == l + cnt){
        continue;
      }
      if(my_query(v[l + cnt], v[i]) == v[i]){
        std::swap(v[lst_available++], v[i]);
      }
    }

    int my_value_idx = -1;
    
    for(int i = l;i < r;i++){
      int idx = i + (i + 1 < r && values[i + 1] - values[i] == 1) - (i > l && values[i] - values[i - 1] == 1);
      printf("debug %d %d %d on %d and value %d would have index %d\n", l, r, cnt, l + cnt, i, idx);
      if(idx == l + cnt){
        my_value_idx = i;
      }
    }
    assert(my_value_idx != -1);
    int which_case = -1;
    if(my_value_idx + 1 < r && values[my_value_idx + 1] - values[my_value_idx] == 1){
      if(my_value_idx > l && values[my_value_idx] - values[my_value_idx - 1] == 1){
        std::swap(values[my_value_idx - 1], values[my_value_idx + 1]);
        which_case = 0;
      }else{
        std::swap(values[my_value_idx], values[my_value_idx + 1]);
        which_case = 1;
      }
    }else{
        std::swap(values[my_value_idx - 1], values[my_value_idx]);
        which_case = 3;
    }
    
    my_sort(v, l, l + cnt, values);
    my_sort(v, l + cnt + 1, r, values);

    if(which_case == 0){
      std::swap(v[l + cnt - 1], v[l + cnt + 1]);
      std::swap(values[l + cnt - 1], values[l + cnt + 1]);
    }else if(which_case == 1){
      std::swap(v[l + cnt], v[l + cnt + 1]);
      std::swap(values[l + cnt], values[l + cnt + 1]);
    }else{
      std::swap(v[l + cnt - 1], v[l + cnt]);
      std::swap(values[l + cnt - 1], values[l + cnt]);
    }
  }
} 

std::vector<int> Solve(int n) {

  std::vector<int> ans(n, 0);
  std::vector<int> powers(n, 0);
  for(int i = 0;i < n;i++){
    ans[i] = i;
    powers[i] = i;
  }
  std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
  //shuffle(ans.begin(), ans.end(), rng);
  my_sort(ans, 0, n, powers);

  for(int i = 0;i < n;i++){
    printf("debug order is %d %d\n", i, ans[i]);
    powers[ans[i]] = i;
  }
  
  return powers;
}
