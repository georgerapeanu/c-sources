#include "jelly.h"
#include <vector>
#include <algorithm>

using namespace std;

const int VMAX = 1e4;

class MyContainer{
private:

    vector<pair<int,int> > aint;

    void update(int nod,int st,int dr,int pos,int val){
        if(dr < pos || st > pos){
            return ;
        }
        if(st == dr){
             aint[nod].first += val;
             aint[nod].second += val * pos;
             return ;
        }

        int mid = (st + dr) / 2;

        update(nod * 2,st,mid,pos,val);
        update(nod * 2 + 1,mid + 1,dr,pos,val);

        aint[nod].first = aint[nod * 2].first + aint[nod * 2 + 1].first;
        aint[nod].second = aint[nod * 2].second + aint[nod * 2 + 1].second;
    }

    int query(int nod,int st,int dr,int val){
        if(st == dr){
            return min(aint[nod].first,(val / st));
        }
        
        int mid = (st + dr) / 2;

        if(aint[nod * 2].second <= val){
            return aint[nod * 2].first + query(nod * 2 + 1,mid + 1,dr,val - aint[nod * 2].second);
        }
        else{
            return query(nod * 2,st,mid,val);
        }
    }

public:

    MyContainer(const vector<int> &v){
        aint = vector<pair<int,int> >(4 * (VMAX + 1) + 5,{0,0});
        for(auto it:v){
            update(1,0,VMAX,it,1);
        }
    }

    void del(int val){
        update(1,0,VMAX,val,-1);
    }

    int query(int val){
        return query(1,0,VMAX,val); 
    }
};

int find_maximum_unique(int x, int y, vector<int> a, vector<int> b) {
	int n = a.size();
    
    vector<pair<int,int> > sorted_a;

    for(int i = 0;i < n;i++){
        sorted_a.push_back({a[i],i});
    }

    sort(sorted_a.begin(),sorted_a.end());

    MyContainer stuff(b);

    vector<int> dp(VMAX + 1,0);

    int ans = 0;

    for(int i = -1;i < (int)sorted_a.size();i++){
        if(i >= 0){
            for(int j = VMAX;j >= 0;j--){
                if(j + sorted_a[i].first <= VMAX){
                    dp[j + sorted_a[i].first] = min(dp[j + sorted_a[i].first],dp[j]);
                }
                dp[j] += b[sorted_a[i].second];
            }
            stuff.del(b[sorted_a[i].second]);
        }
        
        if(dp[x] <= y){
            ans = max(ans,(i + 1) + stuff.query(y - dp[x]));
        }
    }

	return ans;
}
