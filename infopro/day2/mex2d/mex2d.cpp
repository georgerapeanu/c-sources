#include "mex2d.h"
#include <algorithm>
#include <vector>

using namespace std;

const int VMAX = 4e6;

int n,m;

bool cmp(const pair<int,int> &a,const pair<int,int> &b){
    if(a.second != b.second){
        return a.second < b.second;
    }
    return a.first > b.first;
}

vector<pair<int,int> > get_staircase(vector<pair<int,int> > points){
    sort(points.begin(),points.end(),cmp);

    vector<pair<int,int> > ans;

    for(auto &it:points){
        if(ans.empty() == false && ans.back().first <= it.first){
            continue;
        }
        ans.push_back(it);
    }

    return ans;
}

vector<pair<int,int> > staircases[VMAX + 1];

bool has_value(int val,int i,int j){
    int st = -1,dr = staircases[val].size();

    while(dr - st > 1){
        int mid = (st + dr) / 2;

        if(staircases[val][mid].second <= j){
            st = mid;
        }
        else{
            dr = mid;
        }
    }

    if(st == -1 || staircases[val][st].first > i){
        return false;
    }
    return true;
}

void solve(int N,int M,int **a,int **b){
    n = N;
    m = M;

    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            staircases[a[i][j]].push_back({i,j});
        }
    }

    for(int i = 0;i <= VMAX;i++){
        if(staircases[i].empty()){
            break;
        }
        staircases[i] = get_staircase(staircases[i]);
    }

    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            b[i][j] = 0;
            if(i){
                b[i][j] = max(b[i][j],b[i - 1][j]);
            }
            if(j){
                b[i][j] = max(b[i][j],b[i][j - 1]);
            }
            while(has_value(b[i][j],i,j)){
                b[i][j]++;
            }
        }
    }
}
