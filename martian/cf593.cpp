#include <bits/stdc++.h>

using namespace std;

string to_str(int x){
  if(x == 0){
    return "0";
  }
  string ans = "";

  while(x){
    ans += (x % 10) + '0';
    x /= 10;
  }

  reverse(ans.begin(),ans.end());
  return ans;
}

string solve(vector<int> &x){
  for(auto &it:x){
    if(it & 1){
      it++;
    }
  }

  string ans = to_str(x[0]);

  for(int i = 1;i < (int)x.size();i++){
    int coef = (x[i] - x[i - 1]) / 2;
    if(coef == 0){
      continue;
    }
    string str_coef;
    if(coef > 0){
      str_coef = to_str(coef);
    }else{
      str_coef = "(0-" + to_str(-coef)+")";
    }
    string fst_poly = "(t-" + to_str(i - 1) + ")";
    string snd_poly = "(t-" + to_str(i) + ")";
    string fst_half = "(" + fst_poly + "+" + "abs(" + fst_poly + ")" + ")";
    string snd_half = "(" + snd_poly + "+" + "abs(" + snd_poly + ")" + ")";
    string poly = "(" + fst_half + "-" + snd_half + ")";
    string coef_poly = "(" + str_coef + "*" + poly + ")";
    ans = "(" + ans + "+" + coef_poly + ")";
  }
  return ans;
}

int main(){
  int n;

  cin >> n;
  vector<int> x(n,0),y(n,0),r(n,0);

  for(int i = 0;i < n;i++){
    cin >> x[i] >> y[i] >> r[i];
  }

  cout << solve(x) << endl;
  cout << solve(y) << endl;

  return 0;
}
