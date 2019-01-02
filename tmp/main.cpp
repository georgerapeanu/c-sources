#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;
const int QMAX = 1e5;

pair<long long,int> aib[NMAX + 5];

void update(int pos,int val){
   for(;pos <= NMAX;pos += (-pos) & pos){
      aib[pos].first += val;
      aib[pos].second += (val < 0 ? -1 : 1);
   }
}

pair<long long,int> query(int pos){
   pair<long long,int> ans;
   for(;pos;pos -= (-pos) & pos){
      ans.first += aib[pos].first;
      ans.second += aib[pos].second;
   }
   return ans;
}

const int BUCK = 314;
struct query_t{
   int l,r,id;
   bool operator < (const query_t &other)const{
      if(l / BUCK != other.l / BUCK){
         return l < other.l;
      }
      return r < other.r;
   }
};

int n,q;
query_t queries[QMAX + 5];
int v[NMAX + 5];
double ans[QMAX + 5];

void ins(int val,long long &ans){
   long long sum = query(NMAX).first - query(val).first;
   ans += 2 * sum;
   update(val,val);
   ans += 1LL * (2 * query(val).second - 1) * val;
}

void del(int val,long long &ans){
   long long sum = query(NMAX).first - query(val).first;
   ans -= 2 * sum;
   ans -= 1LL * (2 * query(val).second - 1) * val;
   update(val,-val);
}

int main() {
   
    cin >> n >> q;
    for(int i = 1;i <= n;i++){
       cin >> v[i];
    }
    
    for(int i = 1;i <= q;i++){
       cin >> queries[i].l >> queries[i].r;
       queries[i].id = i;
    }
    
    sort(queries + 1,queries + 1 + q);
    
    int l = 1,r = 0;
    long long sum = 0;

    for(int i = 1;i <= q;i++){
       while(r < queries[i].r){
         ins(v[++r],sum);     
       }
       while(l > queries[i].l){
         ins(v[--l],sum);
       }
       while(r > queries[i].r){
         del(v[r--],sum); 
       }
       while(l < queries[i].l){
          del(v[l++],sum);
       }
       ans[queries[i].id] = (double)sum / (double(r - l + 1) * double(r - l + 1));
    }
   
    for(int i = 1;i <= q;i++){
       cout << fixed << setprecision(10) << ans[i] << "\n";
    }
   
    return 0;
}