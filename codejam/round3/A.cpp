#include <bits/stdc++.h>

using namespace std;

int tests;
string s;
int fr[15];

long long a,b;

void fix(int &l,int &r){
  while(fr[l] == 0){
    l++;
  }
  while(fr[r] == 0){
    r--;
  }
}

int main(){

  cin >> tests;
  
  for(int test = 1;test <= tests;test++){
    printf("Case #%d: ",test);

    memset(fr,0,sizeof(fr));

    cin >> s;

    for(auto it:s){
      fr[it - '0']++;
    }

    a = b = 0;

    if((int)s.size() % 2){
        for(int i = 1;i < 10;i++){
          if(fr[i]){
            a = i;
            fr[i]--;
            break;
          }
        }
        int l = 0,r = 9;
        for(int i = 1;i < (int)s.size();i += 2){
          fix(l,r);
          a = a * 10 + l;fr[l]--;
          b = b * 10 + r;fr[r]--;
        }
        printf("%lld\n",abs(a - b));
    }else{
      bool ok = false;
      for(int i = 1;i < 10;i++){
        if(fr[i] > 1){
          ok = true;
        }
      }

      if(ok == true){
        for(int i = 0;i < 10;i++){
          fr[i] &= 1;
        }
      }
    }
    

  }

  return 0;
}
