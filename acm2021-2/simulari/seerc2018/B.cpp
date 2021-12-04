#include <bits/stdc++.h>

using namespace std;

unsigned long long a,b,c,n;
int fr[15005];

int main(){

    scanf("%llu %llu %llu %llu",&a,&b,&c,&n);
    fr[a]++;
    fr[b]++;
    fr[c]++;

    unsigned long long ways = 6;

    for(int i = 1000;i <= 15000;i++){
      if(fr[i] > 0){
        for(int k = 2;k <= fr[i];k++){
          ways /= k;
        }
      }
    }
    

    unsigned long long ans = 0;
  
    ans = (((n + 1) / 2 - 2) * ((n + 1) / 2 - 1) / 2) * n;
    

    a = n - 2;
    b = n - 1;
    c = n;

    if(a % 3 == 0){
      a /= 3;
    }else if(b % 3 == 0){
      b /= 3;
    }else{
      c /= 3;
    }

    if(a % 2 == 0){
      a /= 2;
    }else if(b % 2 == 0){
      b /= 2;
    }else{
      c /= 2;
    }

    ans = a * b * c - ans;

    ans *= ways;
    
    printf("%llu\n",ans);


    return 0;
}
