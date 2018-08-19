#include<set>
#include<cassert>
#include<cmath>
#include<iostream>
using namespace std;
int N,K;
long long dp[105][10005];
long long A[10005];
const long long isQ = -(1LL << 62);
struct Line{
   long long m,b;
   mutable long long nxtm,nxtb;
   bool operator < (const Line &other)const{
      assert(b != isQ);
      if(other.b != isQ){
         if(m != other.m){
            return m > other.m;
         }
         return b > other.b;
      }
      if(nxtm == -isQ && nxtb == -isQ){
         return 0;
      }
      return nxtb - b <= other.m * (m - nxtm);
   }
};
struct convex_hull{
   set<Line> S;
   bool bad(set<Line> :: iterator a){
      if(S.size() == 1){
         return 0;
      }
      if(a == S.begin()){
         if(next(a)->m == a->m && next(a)->b <= a->b){
            return 1;
         }
         return 0;
      }
      else{
         if(prev(a)->m == a->m && prev(a)->b <= a->b){
            return 1;
         }
      }
      if(a == prev(S.end())){
         if(prev(a)->m == a->m && prev(a)->b <= a->b){
            return 1;
         }
         return 0;
      }
      else{
         if(next(a)->m == a->m && next(a)->b <= a->b){
            return 1;
         }
      }
      return (a->b - prev(a)->b) * (prev(a)->m - next(a)->m)  >= (next(a)->b - prev(a)->b) * (prev(a)->m - a->m);
   }
   void del(set<Line> :: iterator a){
      if(a != S.begin()){
         prev(a)->nxtm = a->nxtm;
         prev(a)->nxtb = a->nxtb;
      }
      S.erase(a);
   }
   void add(long long m,long long b){
      Line a;
      a.m = m;
      a.b = b;
      a.nxtm = a.nxtb = 0;
      if(S.count(a)){
         return ;
      }
      set<Line> :: iterator it = S.insert(a).first;
      if(it != S.begin()){
         prev(it)->nxtb = it->b;
         prev(it)->nxtm = it->m;
      }
      if(it != prev(S.end())){
         it->nxtb = next(it)->b;
         it->nxtm = next(it)->m;
      }
      else{
         it->nxtm = -isQ;
         it->nxtb = -isQ;
      }
      if(bad(it)){
         del(it);
         return ;
      }
      while(it != prev(S.end()) && bad(next(it))){
         del(next(it));
      }
      while(it != S.begin() && bad(prev(it))){
         del(prev(it));
      }
   }
   long long query(long long x){
      set<Line> :: iterator it = S.lower_bound({x,isQ,0,0});
      return it->m * x + it->b;
   }
}a;
int main() {
    a.add(1,2);
    for(auto it:a.S)cout<<it.m<<" "<<it.b<<" "<<it.nxtm<<" "<<it.nxtb<<"\n";cout<<"\n";
    a.add(2,3);
    for(auto it:a.S)cout<<it.m<<" "<<it.b<<" "<<it.nxtm<<" "<<it.nxtb<<"\n";cout<<"\n";
    a.add(-1,2);
    for(auto it:a.S)cout<<it.m<<" "<<it.b<<" "<<it.nxtm<<" "<<it.nxtb<<"\n";cout<<"\n";
    a.add(2,-1);
    for(auto it:a.S)cout<<it.m<<" "<<it.b<<" "<<it.nxtm<<" "<<it.nxtb<<"\n";cout<<"\n";
    a.add(-2,-1);
    for(auto it:a.S)cout<<it.m<<" "<<it.b<<" "<<it.nxtm<<" "<<it.nxtb<<"\n";cout<<"\n";
    cout<<a.query(5)<<"\n";
    return 0;
}
