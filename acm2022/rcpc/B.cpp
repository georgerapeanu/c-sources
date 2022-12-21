#include <bits/stdc++.h>

using namespace std;

int main(){

  int k;
  int n;
  cin >> k >> n;

  vector<long double> probabilities((1 << k), 0);
  probabilities[0] = 1;

  for(int i = 1;i < n;i++){
    double p;
    int v;
    cin >> p >> v;

    vector<long double> new_probabilities((1 << k), 0);
    for(int sum = 0;sum < (1 << k);sum++){
      new_probabilities[(sum + v) & ((1 << k) - 1)] += probabilities[sum] * p;
      new_probabilities[sum] += probabilities[sum] * (1 - p);
    }
    probabilities.swap(new_probabilities);
  }

  vector<vector<long double> > preferences(k + 1);

  for(int i = 0;i < (int)preferences.size();i++){
    preferences[i] = vector<long double>((1 << i));
  }

  for(int conf = 0;conf < (1 << k);conf++){
    for(int i = 0;i < k;i++){
      int mask = (conf & ((1 << (i + 1)) - 1));
      int start = ((1 << i) - mask);
      if(start < 0){
        start += (1 << (i + 1));
      }
      int end = ((1 << (i + 1)) - mask);
      if(end >= ((1 << (i + 1)))){
        end -= ((1 << (i + 1)));    
      }
     
      if(start <= end){
        preferences[i + 1][start] += probabilities[conf];
        preferences[i + 1][end] -= probabilities[conf];
      } else {
        preferences[i + 1][0] += probabilities[conf];
        preferences[i + 1][end] -= probabilities[conf];
        preferences[i + 1][start] += probabilities[conf];
      }
      
    }
  }
  for(int i = 1;i <= k;i++){
    for(int conf = 1;conf < (1 << i);conf++){
      preferences[i][conf] += preferences[i][conf - 1];
    }
  }

  for(int i = 1;i < k;i++){
    for(int conf = 0;conf < (1 << i);conf++){
      preferences[i + 1][conf] += preferences[i][conf];
      preferences[i + 1][conf ^ (1 << i)] += preferences[i][conf];
    }
  }

  long double best = 0;
  int best_conf = 0;

  for(int conf = 0;conf < (1 << k);conf++){
    if(best < preferences[k][conf]){
      best = preferences[k][conf];
      best_conf = conf;
    }
  }

  cout << best_conf << "\n";

  return 0;
}
