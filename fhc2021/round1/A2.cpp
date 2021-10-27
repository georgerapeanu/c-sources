#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int t;
int n;
string s;

int add(int a,int b){
  a += b;
  if(a >= MOD){
    a -= MOD;
  }
  return a;
}

int scad(int a,int b){
  a -= b;

  if(a < 0){
    a += MOD;
  }

  return a;
}

int mult(int a,int b){
  return 1LL * a * b % MOD;
}

int main(){

  cin >> t;
  
  for(int h = 1;h <= t;h++){
    cin >> n;
    cin >> s;

    int ans = 0;
    int sum = 0;
    int len = 0;
    int highValue = 0;

    int firstNonF = 0;

    int lastNonF = 0;
    int lastNonFPos = 0;
    int startFCnt = 0;
    int cntFBetweenDifferent = 0;

    for(auto it:s){
      if(it == 'F'){
        ans = add(ans,sum);
        if(startFCnt == len){
          startFCnt = add(startFCnt,1);
        }
        len = add(len,1);
      }else if(it == 'X' || it == 'O'){
      
        int endFCnt = scad(len,lastNonFPos);
        
        if(lastNonF == 0 || lastNonF == it){
          ans = add(ans,sum);
        }else{
          cntFBetweenDifferent = add(cntFBetweenDifferent,endFCnt);
          highValue = add(highValue,1);
          sum = add(sum,scad(len,endFCnt));
          ans = add(ans,sum);
        }

        if(firstNonF == 0){
          firstNonF = it;
        }

        len = add(len,1);
        lastNonF = it;
        lastNonFPos = len;
      }else{
        ans = add(ans,ans);///individual halves
        int endFCnt = scad(len,lastNonFPos);

        int leftSum = sum;

        leftSum = add(leftSum,mult(len,highValue));
        highValue = add(highValue,highValue);

        int cntRightFBetweenDifferent = cntFBetweenDifferent;

        if(lastNonF != firstNonF){
          cntRightFBetweenDifferent = add(cntRightFBetweenDifferent,startFCnt);
          leftSum = add(leftSum,scad(len,endFCnt));
          highValue = add(highValue,1);
          ans = add(ans,mult(endFCnt,startFCnt));///because discrapancy on F only
        }

        

        ans = add(ans,scad(mult(len,leftSum),mult(len,add(sum,cntRightFBetweenDifferent))));
        sum = add(sum,leftSum);

        if(lastNonF != 0){
          lastNonFPos = add(lastNonFPos,len);
        }else{
          startFCnt = add(startFCnt,startFCnt);
        }


        len = add(len,len);
        
        cntFBetweenDifferent = add(cntFBetweenDifferent,cntFBetweenDifferent);

        if(lastNonF != firstNonF){
          cntFBetweenDifferent = add(cntFBetweenDifferent,add(startFCnt,endFCnt));
        }

      }
    }

    printf("Case #%d: %d\n",h, ans);
  }

  return 0;
}
