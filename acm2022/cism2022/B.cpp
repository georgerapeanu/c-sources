#include <bits/stdc++.h>

using namespace std;

const long long inf = 1e11;

struct bucket_t{
  long long left;
  long long right;
  long long original_left;
  long long original_right;
  char what;

  bool operator == (const bucket_t &other) const {
    if((what == 0x0) != (other.what == 0x0)){
      return false;
    }
    if(what == 0x0 || other.what == 0x0){
      return left == other.left && right == other.right && original_left == other.original_left && original_right == other.original_right;
    }
    return this->what == other.what && this->left == other.left && this->right == other.right;
  }
  
  void debug(){
    cerr << "bucket " << left << " " << right << " " << original_left << " " << original_right << " " << what << "\n";
  }

};

class Program {
  vector<bucket_t> buckets;
 
public:  

  Program(){
    buckets = vector<bucket_t>(1, {0, inf, 0, inf, 0x0});
  }

  void remove(long long pos) {
    vector<bucket_t> next_buckets;
    
    for(const auto &it:buckets){
      if(it.left <= pos && pos <= it.right){
        if(it.left < pos){
          next_buckets.push_back({it.left, pos - 1, it.original_left, it.original_left + (pos - 1 - it.left), it.what});
        }
        if(pos < it.right){
          next_buckets.push_back({pos, it.right - 1, it.original_right + (pos - (it.right - 1)), it.original_right, it.what});
        }
      }else if(pos < it.left){
        next_buckets.push_back({it.left - 1, it.right - 1, it.original_left, it.original_right, it.what});
      }else{
        next_buckets.push_back(it);
      }
    }
    this->buckets.swap(next_buckets);
    //this->debug();
  }

  void insert(long long pos, char value){
    vector<bucket_t> next_buckets;
    
    for(const auto &it:buckets){
      if(it.left <= pos && pos <= it.right){
        if(it.left < pos){
          next_buckets.push_back({it.left, pos - 1, it.original_left, it.original_left + (pos - 1 - it.left), it.what});
        }
        next_buckets.push_back({pos, pos, -1, -1, value});
        next_buckets.push_back({pos + 1, it.right + 1, it.original_right + (pos - it.right), it.original_right,it.what});
      }else if(pos < it.left){
        next_buckets.push_back({it.left + 1, it.right + 1, it.original_left, it.original_right, it.what});
      }else{
        next_buckets.push_back(it);
      }
    }
    this->buckets.swap(next_buckets);
    //this->debug();
  }

  bool operator == (Program& other) {
    long long length = 0;
    int pos_this = 0;
    int pos_other = 0;

    while(true){
      if(pos_this < (int)this->buckets.size() && this->buckets[pos_this].right < length){
        pos_this++;
        continue;
      }
      if(pos_other < (int)other.buckets.size() && other.buckets[pos_other].right < length){
        pos_other++;
        continue;
      }
      if(pos_this >= (int)this->buckets.size()){
        break;
      }
      if(pos_other >= (int)other.buckets.size()){
        break;
      }
      long long delta_length = min(this->buckets[pos_this].right - length + 1, other.buckets[pos_other].right - length + 1);
      bucket_t first, second;
      
      first.what = this->buckets[pos_this].what;
      first.left = length;
      first.right = length + delta_length - 1;
      first.original_left = this->buckets[pos_this].original_left + (first.left - this->buckets[pos_this].left);
      first.original_right = this->buckets[pos_this].original_left + (first.right - this->buckets[pos_this].left);

      second.what = other.buckets[pos_other].what;
      second.left = length;
      second.right = length + delta_length - 1;
      second.original_left = other.buckets[pos_other].original_left + (second.left - other.buckets[pos_other].left);
      second.original_right = other.buckets[pos_other].original_left + (second.right - other.buckets[pos_other].left);

      //first.debug();
      //second.debug();

      if(!(first == second)){
        return false; 
      }

      length += delta_length;
    }
    return (pos_this >= (int)this->buckets.size() && pos_other >= (int)other.buckets.size());
  }

  void debug(){
    cerr << this << "\n";
    for(auto it:buckets){
      cerr << it.left << " " << it.right << " " << it.original_left << " " << it.original_right << " " << it.what << "\n";
    }
    cerr << "\n";
  }
};

int main(){
  
  char op;

  vector<Program> programs(2, Program());
  int current = 0;

  while(cin >> op){
    if(op == 'D'){
      long long value;
      cin >> value;
      programs[current].remove(value); 
    } else if(op == 'I'){
      long long pos;
      char value;
      cin >> pos >> value;
      programs[current].insert(pos, value);
    } else {
      current++;
    }
  }

  cout << !(programs[0] == programs[1]);

  //programs[0].debug();
  //programs[1].debug();

  return 0;
}
