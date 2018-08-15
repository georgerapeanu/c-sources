#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define sz 2
using namespace std;
int N,Q;
struct bucket
{
   int l,r;
   int mn[sz+2][sz+2];
   int mx[sz+2][sz+2];
   int diff[sz+2][sz+2];
   int primaimare[sz+2];
   int primaimica[sz+2];
   bucket()
   {
      l=r=0;
      memset(mn,0,sizeof(mn));
      memset(mx,0,sizeof(mx));
      memset(diff,0,sizeof(diff));
      memset(primaimica,0,sizeof(primaimica));
      memset(primaimare,0,sizeof(primaimare));
   }
   bucket(vector<pair<int,int> > V)
   {
      sort(V.begin(),V.end(),[](pair<int,int> a,pair<int,int> b){return a.second<b.second;});
      int ind=0;
      for(int i=1;i<=N;i++)
      {
         while(ind<(int)V.size()&&V[ind].second<i)ind++;
         if(ind<(int)V.size())
         {
            primaimare[i]=ind;
         }
         else
            primaimare[i]=-1;
      }
//      ind=((int)V.size())-1;
//      for(int i=N;i;i--)
//      {
//         while(ind>=0&&V[ind].second>i)
//            ind--;
//         if(ind>=0)
//         {
//            primaimica[i]=ind;
//         }
//         else primaimica[i]=-1;
//      }
      for(int i=0;i<(int)V.size();i++)
      {
         mn[i][i]=mx[i][i]=V[i].first;
         diff[i][i]=1<<28;
      }
      for(int d=1;d<(int)V.size();d++)
      {
         for(int i=0;i<(int)V.size()-d;i++)
         {
            mn[i][i+d]=min(mn[i+1][i+d],mn[i][i+d-1]);
            mx[i][i+d]=max(mx[i][i+d-1],mx[i+1][i+d]);
            diff[i][i+d]=min(min(diff[i+1][i+d],diff[i][i+d-1]),abs(V[i+d].first-V[i].first));
         }
      }
   }
   int getmin(int l,int r)
   {
      l=primaimare[l];
      r=primaimica[r];
      if(l>r||l==-1||r==-1)return -1;
      return mn[l][r];
   }
   int getmax(int l,int r)
   {
      l=primaimare[l];
      r=primaimica[r];
      if(l>r||l==-1||r==-1)return -1;
      return mx[l][r];
   }
   int getdiff(int l,int r)
   {
      l=primaimare[l];
      r=primaimica[r];
      if(l>r||l==-1||r==-1)return -1;
      return diff[l][r];
   }
};
vector<bucket> V;
int main() {
    cin>>N>>Q;
    vector<pair<int,int> > A(N+5);
    for(int i=1;i<=N;i++)
    {
         cin>>A[i].first;
         A[i].second=i;
    }
    sort(A.begin()+1,A.begin()+1+N);
    for(int i=1;i<=N;i+=sz)
    {
       vector<pair<int,int> >tmp;tmp.clear();
       for(int j=i;j<i+sz&&j<=N;j++)
       {
          tmp.push_back(A[j]);
       }
       V.push_back(bucket(tmp));
    }
    int l,r,last=0;
    while(Q--)
    {
      cin>>l>>r;
      l=1+(l+last)%N;
      r=1+(r+last)%N;
      if(l>r)swap(l,r);
      ///cerr<<l<<" "<<r<<"\n";
      int rez=1<<30;
      for(int i=0;i<V.size();i++)
      {
         int tmp=V[i].getdiff(l,r);
         if(tmp!=-1)rez=min(rez,tmp);
      }
      for(int i=1;i<V.size();i++)
      {
         int a=V[i-1].getmax(l,r);
         int b=V[i].getmin(l,r);
         if(a!=-1&&b!=-1)rez=min(rez,abs(b-a));
      }
      cout<<rez<<"\n";
      last=rez;
    }
    return 0;
}
