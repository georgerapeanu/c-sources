#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
struct data{
    int l,r,val;
    bool operator < (const data &other)const{
        return l < other.l;
    }
};
set<data> S;
int rez;
int N,Q;
int main(){
    scanf("%d %d",&N,&Q);
    rez = N;
    S.insert({1,N,1});
    while(Q--){
        int k,x,y;
        scanf("%d %d %d",&x,&y,&k);
        vector<data> tmp;
        set<data> :: iterator it = S.lower_bound({x,0,0});
        set<data> :: iterator it2 = it;
        if(it2 != S.begin()){
            it2--;
            while(it2->r >= x){
                tmp.push_back(*it2);
                if(it2 == S.begin()){
                    break;
                }
                it2--;
            }
        }
        while(it != S.end() && it->l <= y){
            tmp.push_back(*it);
            it++;
        }
        for(auto it:tmp){
            S.erase(it);
            if(x > it.l){
                S.insert({it.l,x - 1,it.val});
            }
            if(it.r > y){
                S.insert({y + 1,it.r,it.val});
            }
            S.insert({max(x,it.l),min(y,it.r),k - 1});
            rez = rez + (k == 2 ? 1 : 0) * (-max(x,it.l) + min(y,it.r) + 1) + (it.val == 1 ? -1:0) * (-max(x,it.l) + min(y,it.r) + 1);
        }
        printf("%d\n",rez);
    }
    return 0;
}
