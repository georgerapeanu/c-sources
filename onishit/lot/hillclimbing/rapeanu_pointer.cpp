#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9 + 5;

struct platform_t{
  int l;
  int r;
  int increase_potential;
  int increased;


  platform_t(){
    l = r = -1;
    increase_potential = 0;
    increased = 0;
  }

  platform_t(int l, int r, int increase_potential, int increased){
    this->l = l;
    this->r = r;
    this->increase_potential = increase_potential;
    this->increased = increased;
  }

  bool valid() const {
    return l != -1;
  }

  bool full() const {
    return this->increase_potential == this->increased;
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

///Monotone manager for 1-type objects
///it assumes that objects can only be deleted, and that the allowed consumption can only increase
class OneObjectsManager{
  int n;
  vector<platform_t> prefix_platforms; 
  vector<platform_t> suffix_platforms; 
  int allowed_consumption;
  int current_consumption;
  int prefix_index;
  int suffix_index;
  int object_count;

  public:

  OneObjectsManager(int n, vector<platform_t> platforms){
  
    this->n = n;

    this->prefix_platforms = vector<platform_t>(n);
    this->suffix_platforms = vector<platform_t>(n);

    for(auto it:platforms){
      if(it.l == 0){
        this->prefix_platforms[it.r] = it;
      }else{
        this->suffix_platforms[it.l] = it;
      }
    }

    this->allowed_consumption = 0;
    this->current_consumption = 0;
    this->prefix_index = 0;
    this->suffix_index = n - 1;
    this->object_count = 0;
  }

  void set_allowed_consumption(int consumption){
    assert(this->allowed_consumption < consumption);
    this->allowed_consumption = consumption;
  }

  void remove_suffix_platform(int i){
    assert(this->suffix_platforms[i].valid());
    current_consumption -= this->suffix_platforms[i].increased * this->suffix_platforms[i].length();
    this->object_count -= this->suffix_platforms[i].increased;
    this->suffix_platforms[i] = platform_t();
  }

  void remove_prefix_platform(int i){
    assert(this->prefix_platforms[i].valid());
    current_consumption -= this->prefix_platforms[i].increased * this->prefix_platforms[i].length();
    this->object_count -= this->prefix_platforms[i].increased;
    this->prefix_platforms[i] = platform_t();
  }

  int get_count() {
    while(true) {
      while(prefix_index < n && prefix_platforms[prefix_index].full()){
        prefix_index++;
      }
      
      while(suffix_index >= 0 && suffix_platforms[suffix_index].full()){
        suffix_index--;
      }

      platform_t prefix_platform = (prefix_index == n ? platform_t(): prefix_platforms[prefix_index]);
      platform_t suffix_platform = (suffix_index == -1 ? platform_t(): suffix_platforms[suffix_index]);
      
      platform_t best_platform;

      if(prefix_platform.valid() == false){
        best_platform = prefix_platform;
      }else if(suffix_platform.valid() == false){
        best_platform = suffix_platform;
      }else{
        best_platform = (prefix_platform.length() < suffix_platform.length() ? prefix_platform:suffix_platform);
      }

      if(best_platform.valid() == false){
        break;
      }
      
      if(allowed_consumption - current_consumption < best_platform.length()){
        break;
      }else{
        int increase = min((allowed_consumption - current_consumption) / best_platform.length(), best_platform.increase_potential - best_platform.increased);
        current_consumption += increase * best_platform.length();
        object_count  += best_platform.length() * increase;
        best_platform.increased += increase;
        if(best_platform.l == 0){
          this->prefix_platforms[best_platform.r] = best_platform;
        }else{
          this->suffix_platforms[best_platform.l] = best_platform;
        }
      }
    }
    return object_count;
  }
};

int main(){
  
  int t;
  cin >> t;

  while(t--){
    int n, k;
    cin >> n >> k;

    vector<int> v(n, 0);

    for(auto &it:v){
      cin >> it;
    }

    vector<platform_t> platforms = get_platforms(v);
    vector<platform_t> objects[2];
    for(auto it:platforms){
      if(it.l == 0 || it.r == n - 1){
        objects[0].push_back(it);
      }else{
        objects[1].push_back(it);
      }
    }

    OneObjectsManager manager(objects[0]);
    sort(objects[1].begin(), objects[1].end()); /// TODO change for pure linear complexity

    int current_cost = 0;
    int object_count = 0;

    for(const auto &it:objects[1]){
      object_count += increase_potential;
    }
  }

  return 0;
}

