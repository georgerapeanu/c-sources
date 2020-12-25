#include <stdio.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cassert>
#include <map>

#include "nice_lines.h"

using namespace std;

const int AMAX = 10000;
const int BMAX = 10000;
const int LEFT = -AMAX - BMAX - 5;
const int RIGHT = AMAX + BMAX + 5;

map<pair<long long,long long>,long double>memo;

long double my_query(long long x,long long y){
    if(memo.count({x,y}) == 0){
        memo[{x,y}] = query(x,y);
    }
    return memo[{x,y}];
}

long double get_derivative(long long x,long long y){
//    printf("%lld %lld %.6f\n",x,y + 1,double(query(x,y + 1)));
//    printf("%lld %lld %.6f\n",x,y,double(query(x,y)));
//    printf("%lld %lld %.6f\n",x,y,double(query(x,y + 1) - query(x,y)));
    return my_query(x,y + 1) - my_query(x,y);
}

long long find_nxt_point(long double curr_derivative,int x,long long y,long long r){
//    printf("search at %d %lld %lld for %.6f",x,y,r,(double)curr_derivative);
    for(int h = 40;h >= 0;h--){
        if(y + (1LL << h) <= r && fabs(get_derivative(x,y + (1LL << h)) - curr_derivative) < 1e-6){
            y += (1LL << h);
        }
    }
//    printf("ans is %lld\n",y + 1);
    return y + 1;
}

void divide(long long x,long long st,long long dr,long double st_deriv,long double dr_deriv,vector<pair<long long,long double> > &aux){
//    printf("deb %lld %lld %lld %.6f %.6f\n",x,st,dr,(double)st_deriv,(double)dr_deriv);fflush(stdout);
    if(dr < st){
        return ;
    }
    if(fabs(st_deriv - dr_deriv) < 1e-6){
        aux.push_back({dr + 1,dr_deriv});
        return ;
    }

    int mid = (st + dr) / 2;

    mid -= (mid == dr);

    divide(x,st,mid,st_deriv,get_derivative(x,mid),aux);
    divide(x,mid + 1,dr,get_derivative(x,mid + 1),dr_deriv,aux);
}

vector<long long > get_points(int n,int x){
    long long curr = -1LL * AMAX * abs(x) - BMAX - 5;
    
    vector<long long> ans;
    vector<pair<long long,long double> > aux;
    int lft = -1LL * AMAX * abs(x) - BMAX - 5;
    int rgt = -lft;
    divide(x,lft,rgt,get_derivative(x,lft),get_derivative(x,rgt),aux);
    sort(aux.begin(),aux.end());

    for(int i = 0;i < (int)aux.size();i++){
        if(i == (int)aux.size() - 1 || fabs(aux[i + 1].second - aux[i].second) > 1e-6){
            ans.push_back(aux[i].first);
        }
    }

    assert(ans.size() == n + 1);
    ans.pop_back();

    return ans;
    
}

void solve(int subtask_id, int n) {
    vector<long long> fst = get_points(n,LEFT);
    vector<long long> snd = get_points(n,RIGHT);
    reverse(snd.begin(),snd.end());

    vector<int> a,b;

    for(int i = 0;i < n;i++){
        a.push_back((snd[i] - fst[i]) / (RIGHT - LEFT));
        b.push_back(fst[i] - 1LL * a.back() * LEFT);
    }

    the_lines_are(a,b);
}
