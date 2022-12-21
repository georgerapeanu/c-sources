#include <bits/stdc++.h>

using namespace std;

const int MAX_GRADE = 100;

struct candidate_t{
  int score;
  int id;
  deque<int> preferences;
};

int main(){

  int n, m;

  scanf("%d %d", &n, &m);
  vector<int> slots(m, 0);

  for(auto &it:slots){
    scanf("%d", &it);
  }


  vector<vector<candidate_t> > candidates(MAX_GRADE + 1);

  for(int i = 0;i < n;i++){
    candidate_t current;
    current.id = i;
    scanf("%d", &current.score);
    int length;
    scanf("%d", &length);

    for(int i = 0;i < length;i++){
      int course;
      scanf("%d", &course);
      course--;
      current.preferences.push_back(course);
    }
    candidates[current.score].push_back(current);
  }

  vector<int> ans(n, -2);

  for(int grade = MAX_GRADE;grade >= 0;grade--){
    while(!candidates[grade].empty()){
      vector<candidate_t> next_candidates;
      for(auto &it:candidates[grade]){
        if(it.preferences.empty()){
          continue;
        }
        if(slots[it.preferences[0]] > 0){
          slots[it.preferences[0]]--;
          ans[it.id] = it.preferences[0];
          continue;
        }
        it.preferences.pop_front();
        next_candidates.push_back(it);
      }
      candidates[grade].swap(next_candidates);
    }
  }

  for(auto it:ans){
    printf("%d\n", it + 1);
  }

  return 0;
}
