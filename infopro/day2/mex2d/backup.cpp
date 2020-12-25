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

void solve(int N,int M,int **a,int **b){
    vector<pair<int,pair<int,int> > > values;

    n = N;
    m = M;

    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            values.push_back({a[i][j],{i + 1,j + 1}});
        }
    }

    sort(values.begin(),values.end());
    reverse(values.begin(),values.end());

    vector<int> borderline = vector<int>(n + 1,1);

    for(int val = 0;;val++){
        if(values.empty() || values.back().first != val){
            break;
        }

        for(int j = (int)values.size() - 1;j >= 0 && values[j].first == val;j--){
            update(values[j].second.first,values[j].second.second,1);
        }    

        for(int j = (int)values.size() - 1;j >= 0 && values[j].first == val;j--){
            update(values[j].second.first,values[j].second.second,-1);
            values.pop_back();
        }
    }
}
