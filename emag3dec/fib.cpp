#include <bits/stdc++.h>

using namespace std;

int fib_value[1005];
int fib(int n){
  if(n <= 1){
    return 1;
  }
  if(fib_value[n] == 0){
    fib_value[n] = fib(n - 2) + fib(n - 1);
  }
  return fib_value[n];
}

int main(){
  cout << fib(1000);
  return 0;
}
