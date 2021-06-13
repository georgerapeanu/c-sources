#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int n;
pair<int,int> v[NMAX + 5];
map<int,int> left_ans;
map<int,int> right_ans;

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d %d",&v[i].first,&v[i].second);
    }

    vector<int> active;

    sort(v + 1,v + 1 + n,[&](pair<int,int> a,pair<int,int> b){
        return a > b;
    });

    active.clear();
    for(int i = 1;i <= n;i++){
        if(i == 1 || v[i].first != v[i - 1].first){
            right_ans[v[i].first] += (int)active.size();    
        }
        while(active.empty() == false && active.back() <= v[i].second){
            active.pop_back();
        }
        active.push_back(v[i].first);
    }
    
    sort(v + 1,v + 1 + n,[&](pair<int,int> a,pair<int,int> b){
        return make_pair(a.second,a.first) < make_pair(b.second,b.first);
    });

    active.clear();
    for(int i = 1;i <= n;i++){
        if(i == 1 || v[i].second != v[i - 1].second){
            left_ans[v[i].second] += (int)active.size();    
        }
        while(active.empty() == false && active.back() >= v[i].first){
            active.pop_back();
        }
        active.push_back(v[i].second);
    }

    int answer = active.size();

    for(auto it:right_ans){
        map<int,int> :: iterator tmp = left_ans.lower_bound(it.first);
        int bonus = 0;
        if(tmp != left_ans.end()){
            bonus = tmp->second;
        }
        answer = max(answer,it.second + bonus);    
    }

    for(auto it:left_ans){
        map<int,int> :: iterator tmp = right_ans.lower_bound(it.first + 1);
        int bonus = 0;
        if(tmp != right_ans.begin()){
            tmp--;
            bonus = tmp->second;
        }
        answer = max(answer,it.second + bonus);    
    }

    printf("%d\n",answer);

    return 0;
}
