#include <bits/stdc++.h>

using namespace std;
const int NMAX = 1e6;
const int VMAX = 1e9;
const int MOD = 666013;


ifstream f("changemin.in");
ofstream g("changemin.out");

int t, n;
int a[NMAX + 5];

int add(int a, int b){
  a += b;
  if(a >= MOD){
    a -= MOD;
  }
  return a;
}

int scad(int a, int b){
  a -= b;
  if(a < 0){
    a += MOD;
  }
  return a;
}

int mult(int a, int b){
  return 1LL * a * b % MOD;
}
 
int main(){

  f >> t >> n;
  assert(1 <= t && t <= 2);
  assert(1 <= n && n <= NMAX);

  for(int i = 1;i <= n;i++){
    f >> a[i];
    assert(1 <= a[i] && a[i] <= VMAX);
  }
  vector<int> s;

  long long cnt = 0;
  int sum_a = 0;
  int sum_all = 0;

  for(int i = n;i >= 1;i--){
    while(s.empty() == false && a[s.back()] >= a[i]){
      s.pop_back();
    }
    cnt += (int)s.size();
    sum_all = add(sum_all, mult((int)s.size(),sum_a));

    sum_a = add(sum_a, a[i]);
    s.push_back(i);
  }
  
  if(t == 1){
    g << cnt;
  }else{
    g << sum_all;
  }


  f.close();
  g.close();

  return 0;
}
