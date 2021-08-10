#include <bits/stdc++.h>

using namespace std;

const int NMAX = 4100;

int n,m,k;
string s[NMAX + 5];
int __map[256];

int main(){

  cin >> n >> m >> k;

  for(int i = 1;i <= n;i++){
    cin >> s[i];
    s[i] = " " + s[i];
  }

  vector<int> is_candidate(n + 1,true);
  vector<int> weight(n + 1,0);
  
  int cnt_cand = n;

  __map['A'] = 0;
  __map['C'] = 1;
  __map['G'] = 2;
  __map['T'] = 3;

  srand(time(NULL));

  while(cnt_cand > 1){
    vector<vector<long long> > cost(4,vector<long long>(m + 1,0));
    long long total_weight = 0;

    for(int i = 1;i <= n;i++){
      weight[i] = (rand() & 0x7fffffff);
      total_weight += weight[i];
      for(int j = 1;j <= m;j++){
        assert(s[i][j] == 'A' || s[i][j] == 'C' || s[i][j] == 'G' || s[i][j] == 'T');
        cost[__map[s[i][j]]][j] += weight[i];
      }
    }

    for(int i = 1;i <= n;i++){
      if(is_candidate[i] == false){
        continue;
      }

      long long current_weight = 0;

      for(int j = 1;j <= m;j++){
        current_weight += total_weight - cost[__map[s[i][j]]][j];
      }

      if(current_weight != k * (total_weight - weight[i])){
        cnt_cand--;
        is_candidate[i] = false;
      }
    }
  }

  for(int i = 1;i <= n;i++){
    if(is_candidate[i]){
      cout << i << endl;
    }
  }
 


  return 0;
}
