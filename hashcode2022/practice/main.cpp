#include <bits/stdc++.h>

using namespace std;

const int ITERATIONS = 10000;
const long double eps = 1e-10;
const long double rate = 1e-5;

long double eval(const vector<long double> &guess, const vector<vector<int> > &like, const vector<vector<int> > &dislike){
  long double ans = 0;

  for(int i = 0;i < (int)like.size();i++){
    long double customer_score = 1;
    for(auto &it:like[i]){
      customer_score *= guess[it];
    }
    for(auto &it:dislike[i]){
      customer_score *= 1 - guess[it];
    }
    ans += customer_score;
  }
  return ans;
}

void get_gradient(const vector<long double> &guess, const vector<vector<int> > &like, const vector<vector<int> > &dislike, vector<long double> &gradient){
  for(auto &it:gradient){
    it = 0;
  }
  for(int i = 0;i < (int)like.size();i++){
    long double customer_score = 1;
    int cnt_0 = 0;
    for(auto &it:like[i]){
      if(guess[it] < eps){
        cnt_0++;
      }else{
        customer_score *= guess[it];
      }
    }
    for(auto &it:dislike[i]){
      if(1 - guess[it] < eps){
        cnt_0++;
      }else{
        customer_score *= 1 - guess[it];
      }
    }

    for(auto &it:like[i]){
      if(guess[it] > eps){
        if(cnt_0 == 0){
          gradient[it] += customer_score / guess[it];
        }
      }else if(cnt_0 == 1){
          gradient[it] += customer_score;
      }
    }
    for(auto &it:dislike[i]){
      if(1 - guess[it] > eps){
        if(cnt_0 == 0){
          gradient[it] -= customer_score / (1 - guess[it]);
        }
      }else if(cnt_0 == 1){
          gradient[it] -= customer_score / (1 - guess[it]);
      }
    }
  }
}

int run_guess(vector<long double> &guess, const vector<vector<int> > like, const vector<vector<int> > &dislike){
  cerr << "running new guess\n";
  long double curr = eval(guess, like, dislike);
  vector<long double> gradient(guess.size(), 0);
  int print_cnt = 0;
  while(true){
    print_cnt++;
    print_cnt = (print_cnt == 50000 ? 0:print_cnt);
    if(print_cnt == 0){
      cerr << "For current guess score is " << curr << "\n";
    }
    get_gradient(guess, like, dislike, gradient);
    for(int i = 0;i < (int)guess.size();i++){
      guess[i] += gradient[i] * rate;
      guess[i] = min(guess[i], (long double)1);
      guess[i] = max(guess[i], (long double)0);
    }
    long double new_score = eval(guess, like, dislike);
    if(new_score - curr < eps){
      break;
    }
    curr = new_score;
  }
  cerr << "rounding guess to point\n";
  for(auto &it:guess){
    if(it > 0.5){
      it = 1;
    }else{
      it = 0;
    }
  }
  cerr << "got a guess with real score " << round(eval(guess, like, dislike)) << "\n";
  return round(eval(guess, like, dislike));
}

int main(){
  
  unordered_map<string, int> to_norm;
  int n;
  cin >> n;

  vector<vector<int>> like;
  vector<vector<int>> dislike;

  for(int i = 1;i <= n;i++){
    int l, d;
    cin >> l;
    like.push_back(vector<int>(l, -1));
    for(auto &it:like.back()){
      string name;
      cin >> name;
      if(to_norm.count(name) == 0){
        to_norm[name] = to_norm.size();
      }
      it = to_norm[name];
    }
    cin >> d;
    dislike.push_back(vector<int>(d, -1));
    for(auto &it:dislike.back()){
      string name;
      cin >> name;
      if(to_norm.count(name) == 0){
        to_norm[name] = to_norm.size();
      }
      it = to_norm[name];
    }
  }

  vector<string> inv_norm(to_norm.size());
  for(auto &it:to_norm){
    inv_norm[it.second] = it.first;
  }


  mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
  uniform_real_distribution<long double> unif(0, 1);


  vector<int> best(to_norm.size(), 0);
  int best_score = 0;
  for(int i = 0;i < ITERATIONS;i++){
    vector<long double> guess(to_norm.size(), 0);

    for(auto &it:guess){
      it = unif(gen);
    }

    int curr = run_guess(guess, like, dislike);
    if(curr > best_score){
      best_score = curr;
      for(int i = 0;i < (int)guess.size();i++){
        best[i] = round(guess[i]);
      }
    }
  }

  cerr << "Final guess has score " << best_score << "\n"; 

  vector<string> ingredients;
  for(int i = 0;i < (int)best.size();i++){
    if(best[i]){
      ingredients.push_back(inv_norm[i]);
    }
  }
  
  cout << ingredients.size() << " ";
  for(auto it:ingredients)cout << it << " ";

  return 0;
}
