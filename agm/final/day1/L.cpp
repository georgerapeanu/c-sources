#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;
const int KMAX = 1e5;

int n,k;
int fr[KMAX + 5];

int main(){

  scanf("%d %d",&n,&k);

  vector<int> stuff;

  for(int i = 1;i <= n;i++){
    int val;
    scanf("%d",&val);
    fr[val]++;
    stuff.push_back(fr[val]);
  }

  sort(stuff.begin(),stuff.end());
  reverse(stuff.begin(),stuff.end());

  long double ans = 0;

  for(int i = 0;i < n;i++){
    ans += ((long double)(n - i)) / stuff[i];
  }

  printf("%.10f\n",(double)ans);

  return 0;
}
