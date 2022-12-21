#include <bits/stdc++.h>

using namespace std;

bool morph(const string &a, const string &b, int pos_a, int pos_b, string &result){
  if(pos_a >= (int)a.size() || pos_b >= (int)b.size()){
    if(pos_a >= (int)a.size()){
      return true;
    }
    return false;
  }
  if(a[pos_a] < b[pos_b]) {
    while(pos_b < (int)b.size()){
      result += b[pos_b++];
    }
    return true;
  }
  if(a[pos_a] == b[pos_b]){
    result.push_back(a[pos_a]);
    if(morph(a, b, pos_a + 1, pos_b + 1, result)){
      return true;
    }
    result.pop_back();
  }
  if(pos_b + 1 < (int)b.size() && b[pos_b] == 'a' && b[pos_b + 1] == 'a'){
    result.push_back('z' + 1);
    if(a[pos_a] < 'z' + 1){
      pos_b += 2;
      while(pos_b < (int)b.size()){
        result += b[pos_b++];
      }
      return true;
    }else if(a[pos_a] == 'z' + 1){
      if(morph(a, b, pos_a + 1, pos_b + 2, result)){
        return true;
      }
    }
    result.pop_back();
  }
  return false;
}

int main(){

  int n;
  cin >> n;
  vector<string> stuff(n);

  for(auto &it:stuff){
    cin >> it;
  }

  for(int i = 0;i + 1 < n;i++){
    string result;
    if(!morph(stuff[i], stuff[i + 1], 0, 0, result)){
      printf("no\n");
      return 0;  
    }
    stuff[i + 1] = result;
  }
//  for(auto it:stuff){  
//    for(auto it2:it){
//      cout << (int)it2 << " ";
//    }
//    cout << "\n";
//  }
 
  printf("yes\n");

  return 0;
}
