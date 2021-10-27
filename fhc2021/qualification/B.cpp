#include <bits/stdc++.h>

using namespace std;

const int NMAX = 50;

int t;
int n;
string s[NMAX + 5];

int lineCnt[NMAX + 5][2];
int colCnt[NMAX + 5][2];

int main(){

  cin >> t;

  for(int h = 1;h <= t;h++){
    cin >> n;

    for(int i = 1;i <= n;i++){
      cin >> s[i];
      s[i] = " " + s[i];
      lineCnt[i][0] = 0;
      lineCnt[i][1] = 0;
      colCnt[i][0] = 0;
      colCnt[i][1] = 0;
    }

    pair<int,int> ans = {1e9,0};

    for(int i = 1;i <= n;i++){
      for(int j = 1;j <= n;j++){
        lineCnt[i][0] += (s[i][j] == 'X');
        lineCnt[i][1] += (s[i][j] == 'O');
        colCnt[j][0] += (s[i][j] == 'X');
        colCnt[j][1] += (s[i][j] == 'O');
      }
    }

    for(int i = 1;i <= n;i++){
      if(lineCnt[i][1] == 0){
        pair<int,int> local_ans = {n - lineCnt[i][0],1};
        if(ans.first > local_ans.first){
          ans.first = local_ans.first;
          ans.second = 0;
        }
        if(ans.first >= local_ans.first){
          ans.second += local_ans.second;
        }
      }
      if(colCnt[i][1] == 0){
        pair<int,int> local_ans = {n - colCnt[i][0],1};
        if(ans.first > local_ans.first){
          ans.first = local_ans.first;
          ans.second = 0;
        }
        if(ans.first >= local_ans.first){
          ans.second += local_ans.second;
        }
      }
    }

    if(ans.first == 1){
      ans.second = 0;
      for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
          if(s[i][j] == '.' && (lineCnt[i][0] == n - 1 || colCnt[j][0] == n - 1)){
            ans.second++;
          }
        }
      }
    }
    if(ans.first == 1e9){
      printf("Case #%d: Impossible\n",h);
    }else{
      printf("Case #%d: %d %d\n",h,ans.first,ans.second);
    }
  }
  

  return 0;
}
