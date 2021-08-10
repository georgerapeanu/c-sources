#include <bits/stdc++.h>

using namespace std;

FILE *f = fopen("petreceri.in","r");
FILE *g = fopen("petreceri.out","w");

const int NMAX = 1e6;
int n,t;
int a[NMAX + 5];
int c[NMAX + 5];
int smallRight[NMAX + 5];
int st[NMAX + 5],len;

const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;
int i32(){
  int ans = 0;

  while(buff[ind] < '0' || buff[ind] > '9'){
    if(++ind >= LEN){
      ind = 0;
      fread(buff,1,LEN,f);
    }
  }

  while(buff[ind] >= '0' && buff[ind] <= '9'){
    ans = ans * 10 + buff[ind] - '0';
    if(++ind >= LEN){
      ind = 0;
      fread(buff,1,LEN,f);
    }
  }

  return ans;
}

int main(){

  n = i32();
  t = i32();

  for(int i = 1;i <= n;i++){
    a[i] = i32();
  }
  
  for(int i = 1;i <= n;i++){
    c[i] = i32();
  }
  
  st[len = 0] = n + 1;
  for(int i = n;i;i--){
    while(c[st[len]] >= c[i]){
      len--;
    }
    smallRight[i] = st[len];
    st[++len] = i;
  }

  int reachIdx = 0;
  int currentLevel = 0;
  int sumReachWindow = 0;

  long long ans = 0;

  for(int i = 1;i <= n;i++){
    if(reachIdx < i){
      reachIdx = i;
      sumReachWindow = a[i];
    }

    if(currentLevel < a[i]){
      ans += 1LL * c[i] * (a[i] - currentLevel);
      //printf("taken %d on %d with cost %lld\n",a[i] - currentLevel,i,1LL * c[i] * (a[i] - currentLevel));
      currentLevel = a[i];
    }

    currentLevel -= a[i];
    sumReachWindow -= a[i];

    while(reachIdx < smallRight[i] && sumReachWindow <= t){
      reachIdx++;
      sumReachWindow += a[reachIdx];
    }
    ans += 1LL * c[i] * max(0,sumReachWindow - a[reachIdx] - currentLevel);
    currentLevel += max(0,sumReachWindow - a[reachIdx] - currentLevel);
    //printf("taken %d on %d with cost %lld\n",max(0,sumReachWindow - a[reachIdx] - currentLevel),i,1LL * c[i] * max(0,sumReachWindow - a[reachIdx] - currentLevel));
    if(reachIdx < smallRight[i]){
      ans += 1LL * (t - currentLevel) * c[i];
      currentLevel += t - currentLevel;
    }

  }

  fprintf(g,"%lld\n",ans);

  fclose(f);
  fclose(g);

  return 0;
}
