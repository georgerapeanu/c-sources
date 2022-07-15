#include <bits/stdc++.h>

using namespace std;

bool ok(int l){
  cout << "? " << l << endl;
  int ans;
  cin >> ans;
  return (ans == 1);
}

void answer(int x){
  cout << "! " << x << endl;
  exit(0);
}

int main(){
  int n;

  cin >> n;

  int l = -1;
  int r = 4e6 + 1;

  while(r - l > 1){
    int mid = (l + r) / 2;
    if(ok(mid)){
      r = mid;
    }else{
      l = mid;
    }
  }

  answer(r);
  return 0;
}
