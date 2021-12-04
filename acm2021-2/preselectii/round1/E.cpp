#include <bits/stdc++.h>

using namespace std;


const int NMAX = 1e5;
const int LGMAX = 17;

const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;
const int BASE = 31;
const int INV1 = 129032259;
const int INV2 = 838709685;

int pw1[NMAX + 5];
int pw2[NMAX + 5];

struct hash_t{
  int len;
  int h1,h2;

  hash_t(){
    len = h1 = h2 = 0;
  }

  hash_t(char c){
    len = 1;
    h1 = h2 = c - 'a' + 1;
  }

  bool operator < (const hash_t &other)const{
    if(h1 != other.h1){
      return h1 < other.h1;
    }
    if(h2 != other.h2){
      return h2 < other.h2;
    }
    return len < other.len;
  }

  hash_t operator + (const hash_t &other)const{
    hash_t ans;

    ans.len = this->len + other.len;
    ans.h1 = (1LL * this->h1 * pw1[other.len] + other.h1) % MOD1;
    ans.h2 = (1LL * this->h2 * pw2[other.len] + other.h2) % MOD2;

    return ans;
  }

  bool operator == (const hash_t &other)const{
    return  this->h1 == other.h1 &&
            this->h2 == other.h2 &&
            this->len == other.len;
  }

};

int n;
string s;
int fstPos[NMAX + 5];
int skip[LGMAX + 1][NMAX + 5];  
hash_t hashes[LGMAX + 1][NMAX + 5];  
string last2[NMAX + 5];
int len[NMAX + 5];

int better(int a,int b){
  for(int h = LGMAX;h >= 0;h--){
    if(hashes[h][a] == hashes[h][b]){
      a = skip[h][a];
      b = skip[h][b];
    }
  }
  if(a == 0 || b == 0){
    if(a == 0 && b == 0){
      return 0;
    }
    if(a == 0){
      return -1;
    }
    return 1;
  }
  return (s[a] < s[b] ? -1:1);
}

int main(){

    pw1[0] = pw2[0] = 1;
    
    for(int i = 1;i <= NMAX;i++){
      pw1[i] = 1LL * pw1[i - 1] * BASE % MOD1;
      pw2[i] = 1LL * pw2[i - 1] * BASE % MOD2;
    }

    cin >> s;
    n = s.size();
    s = " " + s;
    vector<pair<int,string >> ans;

    for(int i = n ;i;i--){
      fstPos[i] = i;
      skip[0][i] = fstPos[i + 1];
      hashes[0][i] = hash_t(s[i]);
      for(int h = 1;h <= LGMAX;h++){
        skip[h][i] = skip[h - 1][skip[h - 1][i]];
        hashes[h][i] = hashes[h - 1][i] + hashes[h - 1][i + (1 << (h - 1))];
      }
      len[i] = 1 + len[i + 1];
      last2[i] = last2[i + 1];
      if(last2[i].size() < 2){
        last2[i] = s[i] + last2[i];
      }
      if(i + 1 <= n && s[i] == s[i + 1] && better(fstPos[i],fstPos[i + 2]) >= 0){
        fstPos[i] = fstPos[i + 2];
        for(int h = 0;h <= LGMAX;h++){
          skip[h][i] = skip[h][i + 2];
          hashes[h][i] = hashes[h][i + 2];
        }
        len[i] = len[i + 2];
        last2[i] = last2[i + 2];
      }
      string tmp = "";
      if(len[i] <= 10){
        int pos = fstPos[i];
        for(int j = 1;j <= len[i];j++){
          tmp += s[pos];
          pos = skip[0][pos];
        }
      }else{
        int pos = fstPos[i];
        for(int j = 1;j <= 5;j++){
          tmp += s[pos];
          pos = skip[0][pos];
        }
        tmp += "..." + last2[i];
      }
      ans.push_back({len[i],tmp});
    }

    reverse(ans.begin(),ans.end());

    for(auto it:ans){
      cout << it.first << " " << it.second << "\n";
    }
    
    return 0;
}
