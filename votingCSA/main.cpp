#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
int m,M;
int N,X;
int eval(vector<int> P)
{
   int rez=0;
   for(int i=2;i<=N;i++)
   {
      if(P[i]>(double)(1LL*rez*N)/(i-1))rez++;
   }
   return rez;
}
int main()
{
//    freopen("in","r",stdin);
//    freopen("out","w",stdout);
    cin>>N>>X;
    vector<int> P(N+5);
    P[0]=0;
    for(int i=1;i<=N;i++) cin>>P[i];
    sort(P.begin()+1,P.begin()+1+N);
    M=eval(P);reverse(P.begin()+1,P.begin()+N+1);
    m=eval(P);reverse(P.begin()+1,P.begin()+N+1);
    if(X<=m)for(int i=N;i;i--)cout<<P[i]<<" ";
    else if(X>=M)for(int i=1;i<=N;i++)cout<<P[i]<<" ";
    else
    {
       int st=0,dr=N+1;
       while(dr-st>1)
       {
          vector<int> test(N+5);
          int mid=(st+dr)/2;
          for(int i=mid+1;i<=N;i++)
          {
             test[i]=P[i-mid];
          }
          for(int i=1;i<=mid;i++)
          {
             test[i]=P[N-i+1];
          }
          if(eval(test)>=X)st=mid;
          else dr=mid;
       }
       int pre=st;
       st=1;dr=N-pre+1;
      vector<int> test(N+5);
       while(dr-st>1)
       {
          test.clear();test.resize(N+5);
          int mid=(st+dr)/2;
          for(int i=1;i<=pre;i++)test[i]=P[N-i+1];
          for(int i=1;i<=N-pre-mid;i++)test[pre+i]=P[i];
          test[N-mid+1]=P[N-pre-mid+1];
          for(int i=N-pre-mid+2;i<=N-pre;i++)test[i+pre]=P[i];
          if(eval(test)>=X)st=mid;
          else dr=mid;
       }
       test.clear();test.resize(N+5);
      int mid=st;
      for(int i=1;i<=pre;i++)test[i]=P[N-i+1];
      for(int i=1;i<=N-pre-mid;i++)test[pre+i]=P[i];
      test[N-mid+1]=P[N-pre-mid+1];
      for(int i=N-pre-mid+2;i<=N-pre;i++)test[i+pre]=P[i];
      for(int i=1;i<=N;i++)cout<<test[i]<<" ";
    }
    ///cerr<<m<<" "<<M;
    return 0;
}
