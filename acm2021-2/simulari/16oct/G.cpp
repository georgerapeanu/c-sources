#include <bits/stdc++.h>

using namespace std;

int gcd(int x,int y){
  if(y == 0)return x < 0 ? -x:x;
  return gcd(y,x % y);
}

long long det(pair<int,int> a,pair<int,int> b,pair<int,int> c){
  return 1LL * a.first * (b.second - c.second) + 1LL * b.first * (c.second - a.second) + 1LL * c.first * (a.second - b.second);
}

int main(){

  int t = 1;
  
  
  while(t--){
    int n;
    int x,y;
    int xx,yy;
    scanf("%d",&n);
    scanf("%d %d",&x,&y);
    scanf("%d %d",&xx,&yy);

    long long area = (1LL * x * yy - 1LL * xx * y);
    if(area == 0){
      printf("NO\n");
      continue;
    }

    if(area < 0){
      area *= -1;
      swap(x,xx);
      swap(y,yy);
    }
    long long boundry = 0;
    boundry += gcd(x,y);
    boundry += gcd(xx,yy);
    int cnt_points = area - boundry + 1;
    cnt_points += boundry - 1;
    if(cnt_points != n){
      printf("NO\n");
    }else{
      printf("YES\n");
      pair<int,int> rangeX;

      if(x < xx){
        rangeX = {x,xx};
      }else{
        rangeX = {xx,x};
      }

      pair<int,int> d1 = {x,y};
      pair<int,int> d2 = {xx,yy};
  
      for(int i = rangeX.first + 1;i <= rangeX.second;i++){
        while(inside(i,rangeY.second,d1,d2) >= 0){
          rangeY.second++;
        }
        while(inside(i,rangeY.second,d1,d2) < 0){
          rangeY.second--;
        }
        while(inside(i,rangeY.first,d1,d2) >= 0){
          rangeY.first--;
        }
        while(inside(i,rangeY.first,d1,d2) < 0){
          rangeY.first++;
        }
        printf("debug %d %d\n",rangeY.first,rangeY.second);
        for(int j = rangeY.first;j < rangeY.second;j++){
          printf("%d %d\n",i,j);
        }
      }
    }
  }

  return 0;
}
