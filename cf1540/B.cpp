#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;
const int NMAX = 200;

int fact[NMAX + 5];
int ifact[NMAX + 5];
int pw2[NMAX + 5];
int ipw2[NMAX + 5];
int dp[NMAX + 5][NMAX + 5];

int add(int a,int b){
  a += b;
  if(a >= MOD){
    a -= MOD;
  }
  return a;
}

int mult(int a,int b){
  return 1LL * a * b % MOD;
}

int comb(int n,int k){
  return mult(fact[n],mult(ifact[n - k],ifact[k]));
}

int lgpow(int base,int exp){
  int answer = 1;

  while(exp){
    if(exp & 1){
      answer = mult(answer,base);
    }
    base = mult(base,base);
    exp >>= 1;
  }

  return answer;
}

int n;
int weight[NMAX + 5];
vector<int> graph[NMAX + 5];
vector<int> dfs_stack;

void predfs(int nod,int tata){
  weight[nod] = 1;

  for(auto it:graph[nod]){
    if(it == tata){
      continue;
    }
    predfs(it,nod);
    weight[nod] += weight[it];
  }
}

int invN;
int global_answer = 0;

void dfs(int nod,int tata){
  dfs_stack.push_back(nod);

  if(nod != dfs_stack[0]){
    int ans = mult(weight[dfs_stack[0]] - weight[dfs_stack[1]],invN);
    for(int i = 1;i < (int)dfs_stack.size() - 1;i++){
      int coef = mult(weight[dfs_stack[i]] - weight[dfs_stack[i + 1]],invN);
      ans = add(ans,mult(coef,dp[i][(int)dfs_stack.size() - 1 - i]));
    }
    if(dfs_stack[0] > nod){
      global_answer = add(global_answer,ans);
    }
  }

  for(auto it:graph[nod]){
    if(it != tata){
      dfs(it,nod);
    }
  }
  dfs_stack.pop_back();
}


int main(){

    fact[0] = 1;
    pw2[0] = 1;
    for(int i = 1;i <= NMAX;i++){
      fact[i] = mult(i,fact[i - 1]);
      pw2[i] = add(pw2[i - 1],pw2[i - 1]);
    }
    ifact[NMAX] = lgpow(fact[NMAX],MOD - 2);
    ipw2[NMAX] = lgpow(pw2[NMAX],MOD - 2);
    for(int i = NMAX - 1;i >= 0;i--){
      ifact[i] = mult(ifact[i + 1],i + 1);
      ipw2[i] = mult(2,ipw2[i + 1]);
    }

    scanf("%d",&n);

    invN = lgpow(n,MOD - 2);

    for(int i = 1;i < n;i++){
      int x,y;
      scanf("%d %d",&x,&y);
      graph[x].push_back(y);
      graph[y].push_back(x);
    }

    for(int i = 1;i <= n;i++){
      dp[0][i] = 1;
    }

    for(int i = 1;i <= n;i++){
      for(int j = 1;j <= n;j++){
        dp[i][j] = mult(add(dp[i][j - 1],dp[i - 1][j]),ipw2[1]);
      }
    }


    for(int i = 1;i <= n;i++){
      predfs(i,0);
      dfs(i,0);
    }

    printf("%d\n",global_answer);

    return 0;
}
