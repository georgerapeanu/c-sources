#include <bits/stdc++.h>

using namespace std;

int n,m;

vector<pair<int,int> > points;
vector<pair<int,int> > stair;

int main() {

    scanf("%d %d",&n,&m);

    for(int i = 1;i <= n;i++){
        pair<int,int> tmp;
        scanf("%d %d",&tmp.first,&tmp.second);
        points.push_back(tmp);
    }

    for(int i = 1;i <= m;i++){
        pair<int,int> tmp;
        scanf("%d %d",&tmp.first,&tmp.second);
        stair.push_back(tmp);
    }

    stair.push_back({-1,1e9});
    stair.push_back({1e9,-1});
    sort(stair.begin(),stair.end());


    vector<pair<int,int> > real_stair;

    for(auto it:stair){
        while(real_stair.empty() == false && real_stair.back().second <= it.second){
            real_stair.pop_back();
        }
        real_stair.push_back(it);
    }

    stair = real_stair;


    
    vector<pair<int,int> > v;

    for(auto it:points){
        int deltax = 0,lst_x = it.first;
        vector<pair<int,int> > power_points;
        power_points.push_back({-1,1e9});
        for(auto it2:stair){
            if(it2.first >= it.first){
                power_points.push_back({deltax,max(0,it2.second - it.second + 1)});
                deltax += (it2.first + 1 - lst_x);
                lst_x = it2.first + 1;
            }
        }
        power_points.push_back({1e9,-1});
        
        for(int i = 1;i < (int)power_points.size();i++){
            v.push_back({power_points[i - 1].first,power_points[i - 1].second});
            v.push_back({power_points[i].first,-power_points[i - 1].second});
        }
    }

    sort(v.begin(),v.end());

    map<int,int> vals;
    int ans = 2e9;

    for(int i = 0;i < (int)v.size();i++){
        if(v[i].second < 0){
            vals[-v[i].second]--;
            if(vals[-v[i].second] == 0){
                vals.erase(-v[i].second);
            }
        }
        else{
            vals[v[i].second]++;
        }
        if(i == (int)v.size() || v[i + 1].first != v[i].first){
            ans = min(ans,v[i].first + vals.rbegin()->first);
        }
    }

    printf("%d\n",ans);

    return 0;
}
