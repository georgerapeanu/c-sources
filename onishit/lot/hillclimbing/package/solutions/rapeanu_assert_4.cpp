#include <bits/stdc++.h>
#include "cetatuie.h"

using namespace std;

const int DEBUG = 0;

struct platform_t{
  int l;
  int r;
  long long increase_potential;


  platform_t(){
    l = r = -1;
    increase_potential = 0;
  }

  platform_t(int l, int r, long long increase_potential){
    this->l = l;
    this->r = r;
    this->increase_potential = increase_potential;
  }

  bool full() const {
    return this->increase_potential == 0;
  }

  int length() const {
    return this->r - this->l + 1;
  }

  bool operator < (const platform_t &other) const {
    if(this->length() != other.length()) {
      return this->length() < other.length();
    }
    if(this->l != other.l) {
      return this->l < other.l;
    }
    if(this->r != other.r) {
      return this->r < other.r;
    }
    return this->increase_potential < other.increase_potential;
  }
};

///0 indexed
vector<platform_t> get_platforms(const vector<int> &v){
  vector<int> st;

  vector<platform_t> ans;

  for(int i = 0;i < (int)v.size();i++){
    while(st.empty() == false && v[i] >= v[st.back()]){
      if(v[st.back()] != v[i]){
        if((int)st.size() > 1){
          ans.push_back(platform_t(st[(int)st.size() - 2] + 1, i - 1, min(v[i], v[st[(int)st.size() - 2]]) - v[st.back()]));
        }else{
          ans.push_back(platform_t(0, i - 1, v[i] - v[st.back()]));
        }
      }
      st.pop_back();
    }
    st.push_back(i);
  }

  while(st.empty() == false){
    if((int)st.size() > 1){
      ans.push_back(platform_t(st[(int)st.size() - 2] + 1, (int)v.size() - 1, v[st[(int)st.size() - 2]] - v[st.back()]));
    }
    st.pop_back();
  }

  return ans;
}

void length_sort(int n, vector<platform_t> &v){
  vector<vector<platform_t>> tmp(n, vector<platform_t>());
  for(auto &it:v){
    tmp[it.length() - 1].push_back(it);
  }
  v.clear();

  for(auto it:tmp){
    for(auto it2:it){
      v.push_back(it2);
    }
  }
}

int sum_n = 0;

long long solve(int n, long long k, int V[]){
    assert(1 <= n && n <= 1000000);
    assert(0 <= k && k <= 1000000000000000000LL);
    sum_n += n;
    assert(sum_n <= 1000000);

    vector<int> v(n, 0);
    for(int i = 0;i < n;i++){
      v[i] = V[i];
      assert(1 <= v[i] && v[i] <= 1000000000);
    }
    assert(v[0] == 1000000000 && v[n - 1] == 1000000000);

    vector<platform_t> platforms = get_platforms(v);
    vector<platform_t> objects[2];

    for(auto it:platforms){
      if(it.l == 0 || it.r == n - 1){
        objects[1].push_back(it);
      }else{
        objects[0].push_back(it);
      }
      if(DEBUG){
        cerr << it.l << " ";
        cerr << it.r << " ";
        cerr << it.increase_potential << endl;
      }
    }

    length_sort(n, objects[0]);
    length_sort(n, objects[1]);
    
    int indexes[2] = {0, 0};
    long long ans = 0;

    while(true){
      while(indexes[0] < (int)objects[0].size() && objects[0][indexes[0]].full()){
        indexes[0]++;
      }
      while(indexes[1] < (int)objects[1].size() && objects[1][indexes[1]].full()){
        indexes[1]++;
      }
      if(DEBUG)cerr << "debug " << indexes[0] << " " << indexes[1] << " " << ans << " " << k << endl;
      if(indexes[0] == (int)objects[0].size()){
        if(indexes[1] == (int)objects[1].size()){
          if(DEBUG) cerr << 1 << endl;
          break;
        }else{
          if(DEBUG) cerr << 2 << endl;
          long long increase = min((k / objects[1][indexes[1]].length()), objects[1][indexes[1]].increase_potential);
          k -= increase * objects[1][indexes[1]].length();
          objects[1][indexes[1]].increase_potential -= increase;
          ans += increase;
          if(increase == 0){
            break;
          }
        }
      }else{
        if(indexes[1] == (int)objects[1].size()){
          if(DEBUG) cerr << 3 << endl;
          long long increase = min((k / objects[0][indexes[0]].length()), objects[0][indexes[0]].increase_potential);
          k -= increase * objects[0][indexes[0]].length();
          objects[0][indexes[0]].increase_potential -= increase;
          ans += increase * 2;
          if(increase == 0){
            break;
          }
        }else{
          if(objects[1][indexes[1]].increase_potential > 1){
            if(objects[0][indexes[0]].length() <= objects[1][indexes[1]].length() * 2) {
              if(DEBUG) cerr << 4 << endl;
              long long increase = min((k / objects[0][indexes[0]].length()), objects[0][indexes[0]].increase_potential);
              k -= increase * objects[0][indexes[0]].length();
              objects[0][indexes[0]].increase_potential -= increase;
              ans += increase * 2;
              if(increase == 0){
                break;
              }
            }else{
              if(DEBUG) cerr << 5 << endl;
              long long increase = min(min((k / (objects[1][indexes[1]].length() * 2)), objects[1][indexes[1]].increase_potential / 2) * 2, objects[1][indexes[1]].increase_potential - 1);
              k -= increase * objects[1][indexes[1]].length();
              objects[1][indexes[1]].increase_potential -= increase;
              ans += increase;
              if(increase == 0){
                break;
              }
            }
          }else{
            if(indexes[1] + 1 >= (int)objects[1].size()) {
              if(DEBUG) cerr << 6 << endl;
              long long increase = min((k / objects[0][indexes[0]].length()), objects[0][indexes[0]].increase_potential);
              k -= increase * objects[0][indexes[0]].length();
              objects[0][indexes[0]].increase_potential -= increase;
              ans += increase * 2;
              if(increase == 0){
                break;
              }
            } else if(objects[1][indexes[1]].length() + objects[1][indexes[1] + 1].length() >= objects[0][indexes[0]].length()) {
              if(DEBUG) cerr << 7 << endl;
              long long increase = min((k / objects[0][indexes[0]].length()), objects[0][indexes[0]].increase_potential);
              k -= increase * objects[0][indexes[0]].length();
              objects[0][indexes[0]].increase_potential -= increase;
              ans += increase * 2;
              if(increase == 0){
                break;
              }
            } else {
              if(DEBUG) cerr << 8 << endl;
              long long increase = min(k / objects[1][indexes[1]].length(), objects[1][indexes[1]].increase_potential);
              k -= increase * (objects[1][indexes[1]].length());
              objects[1][indexes[1]].increase_potential -= increase;
              ans += increase;
              if(increase == 0){
                break;
              }
            }
          }
        }
      }
    }

    while(indexes[1] < (int)objects[1].size()){
      if(objects[1][indexes[1]].full()){
        indexes[1]++;
        continue;
      }
      long long increase = min((k / objects[1][indexes[1]].length()), objects[1][indexes[1]].increase_potential);
      k -= increase * objects[1][indexes[1]].length();
      objects[1][indexes[1]].increase_potential -= increase;
      ans += increase;
      if(increase == 0){
        break;
      }
    }

    ans *= -1;

    for(int i = 1;i < n;i++){
      ans += abs(v[i] - v[i - 1]);
    }

  return ans;
}

