#include <bits/stdc++.h>

using namespace std;

int n,q;
int t,x;

const int LGMAX = 20;

int rmqRow[LGMAX + 1][1 << LGMAX];
int rmqCol[LGMAX + 1][1 << LGMAX];
int cntRow[LGMAX + 1];
int cntCol[LGMAX + 1];

int main(){

  scanf("%d %d",&n,&q);

  long long totalCount = 0;
  long long goodCount = 0;

  for(int h = 0;h <= n;h++){
    cntRow[h] = cntCol[h] = (1 << (n - h));
    totalCount += ((1LL << ((n - h) << 1)));
    goodCount += ((1LL << ((n - h) << 1)));
  }

  while(q--){
    scanf("%d %d",&t,&x);
    x--;
    if(t == 0){
      int sgn = (rmqRow[0][x] == 1 ? -1:+1);
      for(int h = 0;h <= n;h++){
        if(rmqRow[h][x] == (1 << h) || rmqRow[h][x] == 0){
          cntRow[h]--;
          goodCount -= cntCol[h];
        }
        rmqRow[h][x] += sgn;
        if(rmqRow[h][x] == (1 << h) || rmqRow[h][x] == 0){
          cntRow[h]++;
          goodCount += cntCol[h];
        }
        x &= (((1 << n) - 1) - (1 << h));
      } 
    }else{
      int sgn = (rmqCol[0][x] == 1 ? -1:+1);
      for(int h = 0;h <= n;h++){
        if(rmqCol[h][x] == (1 << h) || rmqCol[h][x] == 0){
          cntCol[h]--;
          goodCount -= cntRow[h];
        }
        rmqCol[h][x] += sgn;
        if(rmqCol[h][x] == (1 << h) || rmqCol[h][x] == 0){
          cntCol[h]++;
          goodCount += cntRow[h];
        }
        x &= (((1 << n) - 1) - (1 << h));
      } 
    }
    printf("%lld\n",((totalCount - goodCount) << 2) | 1);
  }

  return 0;
}
