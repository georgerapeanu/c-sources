#include <cstdio>
#include <vector>

using namespace std;

const int BITS = 16;

int main(){

  freopen("magic4.out", "w", stdout);

  vector<int> solution = {1};
  
  for(int i = 1;(1 << i) <= BITS;i++){
    vector<int> new_solution;
    for(auto it:solution){
      new_solution.push_back((it << (1 << (i - 1))) | it);
    }
    
    for(auto it:solution){
      new_solution.push_back(it);
      for(auto it2:solution){
        new_solution.push_back((it2 << (1 << (i - 1))) | it2);
      }
    }
    solution.swap(new_solution);
  }

  for(auto it:solution){
    printf("%d\n", it);
  }

  return 0;
}
