#include <bits/stdc++.h>

using namespace std;

FILE *f = fopen("countperm.in", "r");
FILE *g = fopen("countperm.out", "w");

const int MOD = 1e9 + 7;

int add(int a, int b){
  a += b;
  if(a >= MOD){
    a -= MOD;
  }
  return a;
}

int mult(int a, int b){
  return 1LL * a * b % MOD;
}

void normalize(vector<int> &v, int st, int dr){
  vector<int> order;
  for(int i = st;i <= dr;i++){
    order.push_back(i);
  }
  sort(order.begin(), order.end(), [=](int a, int b){
    return v[a] < v[b];
  });

  for(int i = 0;i < (int)order.size();i++){
    v[order[i]] = i + 1;
  }
}

int solve22(vector<int> &v, int st, int mid, int dr){
  vector<vector<int> > prefix_sum(dr - st + 2, vector<int>(dr - st + 2, 0));

  for(int i = mid + 1;i <= dr;i++){
    for(int j = i + 1;j <= dr;j++){
      if(v[i] < v[j]){
        prefix_sum[v[i]][v[j]] += 1;
      }
    }
  }

  for(int i = 1;i <= dr - st + 1;i++){
    for(int j = 1;j <= dr - st + 1;j++){
      prefix_sum[i][j] += prefix_sum[i - 1][j] + prefix_sum[i][j - 1] - prefix_sum[i - 1][j - 1];
    }
  }

  int ans = 0;

  for(int i = st;i <= mid;i++){
    for(int j = i + 1;j <= mid;j++){
      if(v[i] < v[j]){
        ///(0, v[i]), (v[i], v[j]) -> sum[v[i]][v[j]] - sum[v[i]][v[i] - 1]
        ans = add(ans, prefix_sum[v[i]][v[j]] - prefix_sum[v[i]][v[i] - 1]);
      }
    }
  }
  prefix_sum.clear();
  return ans;
}


int solve31(vector<int> &v, int st, int mid, int dr){
  vector<int> prefix_sum(dr - st + 2);

  for(int i = mid + 1;i <= dr;i++){
    prefix_sum[v[i]]++;
  }

  for(int i = 1;i <= dr - st + 1;i++){
    prefix_sum[i] += prefix_sum[i - 1];
  }

  int ans = 0;
  for(int i = st;i <= mid;i++){
    int cnt_min = 0;
    for(int j = mid;j > i;j--){
      if(v[i] < v[j]){
        ans = add(ans, mult(cnt_min, prefix_sum[v[j]] - prefix_sum[v[i]]));
      }else{
        cnt_min++;
      }
    }
  }
  prefix_sum.clear();
  return ans;
}


int solve(vector<int> &v, int st, int dr){
  if(dr - st + 1 < 4){
    return 0;
  }

  int mid = (st + dr) / 2;
  int ans = 0;
  ans = add(ans, solve22(v, st , mid,  dr));
//  fprintf(stderr, "%d %d is %d so far\n", st, dr, ans);
  ans = add(ans, solve31(v, st, mid, dr));
//  fprintf(stderr, "%d %d is %d so far\n", st, dr, ans);
  reverse(v.begin() + st, v.begin() + dr + 1);
  for(int i = st;i <= dr;i++){
    v[i] = (dr - st + 1) - v[i] + 1;
  }
  ans = add(ans, solve31(v, st, st + (dr - mid - 1), dr));
  reverse(v.begin() + st, v.begin() + dr + 1);
  for(int i = st;i <= dr;i++){
    v[i] = (dr - st + 1) - v[i] + 1;
  }
//  fprintf(stderr, "%d %d is %d so far\n", st, dr, ans);

  normalize(v, st, mid);
  normalize(v, mid + 1, dr);

  ans = add(ans, solve(v, st, mid));
//  fprintf(stderr, "%d %d is %d so far\n", st, dr, ans);
  ans = add(ans, solve(v, mid + 1, dr));
//  fprintf(stderr, "%d %d is %d so far\n", st, dr, ans);
  return ans;
}

int main(){
  int n;

  fscanf(f, "%d", &n);

  vector<int> perm(n + 1, 0);

  for(int i = 1;i <= n;i++){
    fscanf(f, "%d", &perm[i]);
  }

  fprintf(g,"%d\n", solve(perm, 1, n));
  
  fclose(f);
  fclose(g);

  return 0;
}
