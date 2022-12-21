#include <bits/stdc++.h>

using namespace std;

int main(){

  string n;
  cin >> n;

  if(n.size() < 10){
    long long d_n = 0;

    for(auto &it:n){
      d_n = d_n * 10LL + it - '0';
    }
    long long fact = 1;

    for(int i = 1;fact <= d_n;i++){
      fact *= i;
      if(fact == d_n){
        cout << i;
        return 0;
      }
    }
  }

  long double target = ((long double)n.size()) - 1;
  long double answer = 0;

  int last_i = 0;

  for(int i = 1;answer < target;i++){
    last_i = i;
    answer += log10((long double)i);
  }

  long double before_answer = answer - log10(last_i);
  int before_i = last_i - 1;
  
  long double before_a = (long double)n.size() - before_answer;
  long double last_a = answer - (long double)n.size();

  // n / before = 10 ^ (lgn-before_answer) = x
  // last / n = 10^(last_answer-lgn) = 10 * beofre / n = 10 * 10^(before_answer-lgn) = 10^(before_answer-lgn+1) = 10 / x
  // i want to check if x <= 5
  // lgn - before_answer=before_a <= log10(5)
  
  if(false && before_a <= log10(5)){
    cout << before_i;
    return 0;
  }

  cout << last_i;


  return 0;
}
