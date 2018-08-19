#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int N,M;
int V[40005];
const int rad = 0;
vector<int> AINT[160005];
void build(int nod,int st,int dr){
   if(st == dr){
      AINT[nod].push_back(V[st]);
      return ;
   }
   int mid = (st + dr) / 2;
   build(nod * 2,st,mid);
   build(nod * 2 + 1,mid + 1,dr);
   AINT[nod].resize(AINT[2*nod].size() + AINT[2 * nod + 1].size());
   merge(AINT[2 * nod].begin(),AINT[2 * nod].end(),AINT[2 * nod + 1].begin(),AINT[2 * nod + 1].end(),AINT[nod].begin());
}
int q(int nod,int st,int dr,int S,int D,int val){
   if(S > dr || D < st){
      return 0;
   }
   if(S <= st && dr <= D){
      int rez = 0;
      for(int i = val;i <= 40000;i += val){
         int st = -1,dr = (int)AINT[nod].size();
         while(dr - st > 1){
            int mid = (st + dr) / 2;
            if(AINT[nod][mid] < i){
               st = mid;
            }
            else{
               dr = mid;
            }
         }
         if(st >= 0){
            rez = max(rez,AINT[nod][st] % val);
         }
      }
      return rez;
   }
   int mid = (st + dr) / 2;
   return max(q(nod * 2,st,mid,S,D,val),q(nod * 2 + 1,mid + 1,dr,S,D,val));
}
int AINT2[rad + 1][160005];
void build2(int l,int nod,int st,int dr){
   if(st == dr){
      AINT2[l][nod] = (V[st] % l);
      return ;
   }
   int mid = (st + dr) / 2;
   build2(l,nod * 2,st,mid);
   build2(l,nod * 2 + 1,mid + 1,dr);
   AINT2[l][nod] = max(AINT2[l][nod * 2],AINT2[l][2 * nod + 1]);
}
int q2(int l,int nod,int st,int dr,int S,int D){
   if(S > dr || D < st){
      return 0;
   }
   if(S <= st && dr <= D){
      return AINT2[l][nod];
   }
   int mid = (st + dr) / 2;
   return max(q2(l,nod * 2,st,mid,S,D),q2(l,nod * 2 + 1,mid + 1,dr,S,D));
}
int Q;
int main() {
    cin >> N >> Q;
    for(int i = 1;i <= N;i++){
       cin >> V[i];
    }
    build(1,1,N);
    for(int i = 1;i <= rad;i++){
       build2(i,1,1,N);
    }
    while(Q--){
       int l,r,k;
       cin >> l >> r >> k;
       if(k > rad){
          cout << q(1,1,N,l,r,k);
       }
       else{
          cout << q2(k,1,1,N,l,r);
       }
       cout << "\n";
    }
    return 0;
}
