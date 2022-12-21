#include <bits/stdc++.h>

using namespace std;

class BagOfHolding{
  //actual balance is balance + offset
  map<int, int> balances;
  map<int, int> suffix;
  int offset;
  long long sum;
  int bigger;
  int total;


public:

  BagOfHolding(){
    balances = map<int, int>();
    suffix = map<int, int>();
    offset = 0;
    sum = 0;
    bigger = 0;
    total = 0;
  }

  long long getSum(){
    return sum;
  }

  void add(char c){
    if(c == '(')  {
      sum += bigger + balances[-offset];
      bigger += balances[-offset];
      offset += 1;
      sum += 1;
      balances[1 - offset] += 1;
      suffix[-offset] = 0;
      suffix[1 - offset] += 1;
      bigger += 1; 
    } else {
      sum += suffix[-offset];
      sum -= bigger;
      offset -= 1;
      suffix[-offset] += suffix[-offset - 1] + 1;
      suffix[-offset - 1] = 0;
      bigger -= balances[-offset];
      sum += 1;
      balances[-1 - offset] += 1;
    }
    total += 1;
  }
};

int main(){

  int t;
  cin >> t;
  while(t--){
    int n;
    cin >> n;
    string s;
    cin >> s;

    BagOfHolding b;

    long long ans = 0;

    for(auto it:s){
      b.add(it);
      ans += b.getSum();
    }

    cout << ans << "\n";
  }

  return 0;
}
