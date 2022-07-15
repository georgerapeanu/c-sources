#include <bits/stdc++.h>


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

long long solve(int n, long long k, int V[]){
  
    vector<int> v(n, 0);

    for(int i = 0;i < n;i++){
      v[i] = V[i];
    }

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

    sort(platforms.begin(), platforms.end());

    long long ans = 0;

    for(auto &it: platforms){
      long long increase = min(k / it.length(), it.increase_potential);
      it.increase_potential -= increase;
      k -= it.length() * increase;
      ans += increase * 2;
    }

    ans *= -1;

    for(int i = 1;i < n;i++){
      ans += abs(v[i] - v[i - 1]);
    }

  return ans;
}

