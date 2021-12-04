#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int add(int a,int b){
  a += b;
  if(a >= MOD){
    a -= MOD;
  }
  return a;
}

int scad(int a,int b){
  a -= b;
  if(a < 0){
    a += MOD;
  }
  return a;
}

int mult(int a,int b){
  return 1LL * a * b % MOD;
}

int lgpow(int b,int e){
  int p = 1;
  while(e){
    if(e & 1){
      p = mult(p,b);
    }
    e >>= 1;
    b = mult(b,b);
  }
  return p;
}

int inv(int a){
  return lgpow(a,MOD - 2);
}

class GaussSolver{
  int n;
  vector<vector<int> > sys;

public:
  
  GaussSolver(int n){
    this->n = n;
    sys =  vector<vector<int> >(vector<int>());
  }

  void addEq(const vector<int> &eq){
    sys.push_back(eq);
  }

  vector<int> solve(){
    int i = 0,j = 0;
    while(i < (int)sys.size() && j < n){
      bool found = false;
      for(int k = i;k < (int)sys.size();k++){
        if(sys[k][j] != 0){
          found = true;
          swap(sys[i],sys[k]);
          break;
        }
      }
      if(found == false){
        j++;
        continue;
      }
      int invCurr = inv(sys[i][j]);
      for(int k = i;k <= n;k++){
        sys[i][k] = mult(sys[i][k],invCurr);
      }
      for(int k = 0;k < (int)sys.size();k++){
        if(k == i){
          continue;
        }
        int coef = sys[k][j];
        for(int l = 0;l <= n;l++){
          sys[k][l] = scad(sys[k][l],mult(coef,sys[i][l]));
        }
      }
      i++;
      j++;
    }
    vector<int> ans(n,0);
    for(int i = 0;i < (int)sys.size();i++){
      int j = 0;
      while(j < n && sys[i][j] == 0){
        j++;
      }
      if(j == n && sys[i][j] != 0){
        assert(false);
      }
      if(j != n){
        ans[j] = sys[i][n];
      }
    }
    return ans;
  }
};

const int NMAX = 14;

int n;
int a[NMAX + 5];

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
      scanf("%d",&a[i]);
    }

    GaussSolver solver(n * n);

    for(int i = 1;i <= n;i++){
      for(int j = 1;j <= n;j++){
        if(i == j){
          continue;
        }
        vector<int> eq(n * n + 1);
        for(int k = 1;k <= n;k++){
          if(i != k && k != j){
            
          }
        }
      }
    }

    return 0;
}
