#include <bits/stdc++.h>

using namespace std;

const int BASE = 1e6;

string tmp;
vector<int> n;

vector<int> mult(vector<int> n,int coef){
  for(auto &it:n){
    it *= coef;
  }
  int carry = 0;
  for(int i = 0;i < (int)n.size() || carry;i++){
    if(i >= (int)n.size()){
      n.push_back(0);
    }
    n[i] += carry;
    carry = n[i] / BASE;
    n[i] -= BASE * carry;
  }
  return n;
}

void selfMult(vector<int> &n,int coef){
  for(auto &it:n){
    it *= coef;
  }
  int carry = 0;
  for(int i = 0;i < (int)n.size() || carry;i++){
    if(i >= (int)n.size()){
      n.push_back(0);
    }
    n[i] += carry;
    carry = n[i] / BASE;
    n[i] -= BASE * carry;
  }
}

int cmp(const vector<int> &a,const vector<int> &b){
  if(a.size() != b.size()){
    return (a.size() < b.size() ? -1:1);
  }
  for(int i = (int)a.size() - 1;i >= 0;i--){
    if(a[i] != b[i]){
      return (a[i] < b[i] ? -1:1);
    }
  }
  return 0;
}

int main(){
    
    
    /*
    dp[1] = 1;

    printf("1,");
    for(int i = 2;i <= 30;i++){
      dp[i] = i;
      for(int j = 1;j < i;j++){
        dp[i] = max(dp[i],dp[j] * (i - j));
      }
      printf("%d,",dp[i]);
    }
    */

    cin >> tmp;
    for(auto &it:tmp){
      n.push_back(it - '0');
    }
    reverse(n.begin(), n.end());
    vector<int> backup = n;
    
    int exp = 0;

    while(true){
      if(n.size() <= 1 && n[0] < 3){
        break;
      }
      for(int i = (int)n.size() - 1;i >= 0;i--){
        if(i > 0){
          n[i - 1] += 10 * (n[i] % 3);
        }
        n[i] /= 3;
      }
      while(n.back() == 0){
        n.pop_back();
      }
      exp++;
    }


    n = backup;

    if(tmp == "1" || tmp == "2"){
        cout << tmp << "\n";
        return 0;
    }

    vector<int> tmp = {1};

    for(int i = 1;i < exp;i++){
      selfMult(tmp,3);
    }
  
    if(cmp(mult(tmp,3),n) >= 0){
      printf("%d\n",3 * exp);
    }else if(cmp(mult(tmp,4),n) >= 0){
      printf("%d\n",3 * exp + 1);
    }else if(cmp(mult(tmp,6),n) >= 0){
      printf("%d\n",3 * exp + 2);
    }else{
      printf("%d\n",3 * exp + 3);
    }

    return 0;
}
