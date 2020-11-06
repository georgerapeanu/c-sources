#include "routers.h"
#include <vector>
#include <algorithm>
#include <map>


using namespace std;

map<int,int> memo;

int my_detector(int pos){
    if(memo.count(pos) == 0){
        memo[pos] = use_detector(pos);
    }

    return memo[pos];
}

void solve(int l,int r,int l_val,int r_val,vector<int> &lst_pos){
    if(l_val > r_val){
        return ;
    }
    if(l == r){
        lst_pos[l_val] = r;
        return ;
    }
    
    int m = (l + r) / 2;
    int tmp = my_detector(m + 1);

    solve(l,m,l_val,tmp - 1,lst_pos);
    solve(m + 1,r,tmp,r_val,lst_pos);
}

vector<int> find_routers(int l, int n, int q) {
	vector<int> ans(n,0);
    vector<int> lst_pos(n,0);
    
    solve(0,l,0,n - 2,lst_pos);

    vector<pair<int,int> > tmp;

    for(int i = 0;i < (int)lst_pos.size();i++){
        tmp.push_back({lst_pos[i],i});
    }

    ans[0] = 0;

    for(int i = 0;i < (int)tmp.size() - 1;i++){
        if(tmp[i].second < tmp[i + 1].second){
            ans[tmp[i + 1].second] = 2 * tmp[i].first - ans[tmp[i].second];
        }
        else{
            ans[tmp[i + 1].second] = 2 * tmp[i].first - ans[tmp[i].second] + 1;
        }
    }

    return ans;
}
