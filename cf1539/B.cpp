#include <bits/stdc++.h>

using namespace std;

const int SIGMA = 'z' - 'a' + 1;
const int NMAX = 1e5;

int n;
int q;
string s;
int fr[NMAX + 5][SIGMA];

int main(){

  cin >> n >> q;
  cin >> s;

  s = " " + s;

  for(int i = 1;i <= n;i++){
    for(int j = 0;j < SIGMA;j++){
      fr[i][j] = fr[i - 1][j];
    }
    fr[i][s[i] - 'a']++;
  }

  while(q--){
    int l,r;
    scanf("%d %d",&l,&r);
    int ans = 0;
    for(int i = 0;i < SIGMA;i++){
      ans += (i + 1) * (fr[r][i] - fr[l - 1][i]);
    }
    printf("%d\n",ans);
  }

  return 0;
}
