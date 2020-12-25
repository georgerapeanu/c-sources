#include <bits/stdc++.h>

using namespace std;

struct node_t{
    int val;
    int dp;
    int weight;

    node_t(){
        ;
    }

    node_t(int val){
        this->val = val;
        this->dp = 0;
        this->weight = 1;
    }

    node_t operator + (const node_t &other)const{
        node_t ans;
        ans.val = this->val;
        ans.dp = min(this->dp + other.weight - 1,this->weight + other.dp - 1);
        ans.weight = this->weight + other.weight;
        return ans;
    }

    bool operator < (const node_t &other)const{
        return this->val < other.val;
    }
};

int main(){

    int n;
    
    scanf("%d",&n);
    vector<node_t> v = vector<node_t>(n,node_t());

    for(auto &it:v){
        int val;
        scanf("%d",&val);
        it = node_t(val);
    }

    sort(v.begin(),v.end());

    for(int h = 30;h >= 0;h--){
        vector<node_t> new_v;

        for(auto it:v){
            it.val /= 2;
            new_v.push_back(it);
        }

        sort(new_v.begin(),new_v.end());

        v.clear();

        for(auto it:new_v){
            if((int)v.size() > 0 && v.back().val == it.val){
                v.back() = v.back() + it;
            }
            else{
                v.push_back(it);
            }
        }
    }

    printf("%d\n",v.back().dp);

    return 0;
}
