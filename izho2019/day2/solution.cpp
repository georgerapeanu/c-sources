#include "interactive.h"
#include <map>
#include <algorithm>

using namespace std;

vector<int> intersect(const vector<int> &a,const vector<int> &b){
    vector<int> ans;

    map<int,int> fr;

    for(auto it:a){
        fr[it]++;
    }
    
    for(auto it:b){
        fr[it]++;
    }

    for(auto it:fr){
        if(it.second > 1){
            ans.push_back(it.first);
        }
    }

    return ans;
}

vector<int> diff(const vector<int> &a,const vector<int> &b){

    vector<int> ans;
    map<int,int> fr;

    for(auto it:a){
        fr[it]++;
    }
    
    for(auto it:b){
        fr[it]--;
    }

    for(auto it:fr){
        if(it.first && it.second > 0){
            ans.push_back(it.first);
        }
    }

    return ans;
}

vector<int> uni(const vector<int> &a,const vector<int> &b){
    vector<int> ans;

    for(auto it:a){
        ans.push_back(it);
    }

    for(auto it:b){
        ans.push_back(it);
    }

    sort(ans.begin(),ans.end());

    ans.resize(unique(ans.begin(),ans.end()) - ans.begin());

    return ans;
}

vector<int> query(vector<int> v){
    vector<int> a = get_pairwise_xor(v);
    v.push_back(1);
    vector<int> b = get_pairwise_xor(v);

    return diff(b,a);
}

vector<int> guess(int n) {
	vector <int> bit[7];
    vector <int> all;

    for(int i = 0;i < 7;i++){
        for(int j = 1;j < n;j++){
            if((j >> i) & 1){
                bit[i].push_back(j + 1);
            }
        }
        if(bit[i].empty() == false){
            bit[i] = query(bit[i]);
        }
        else{
            bit[i] = vector<int>();
        }
        all = uni(all,bit[i]);
    }
    
    int fst = ask(1);

    vector<int> ans = {fst};

    for(int i = 1;i < n;i++){
        vector<int> num = all;
        for(int h = 0;h < 7;h++){
            if((i >> h) & 1){
                num = intersect(num,bit[h]);
            }else{
                num = intersect(num,diff(all,bit[h]));
            }
        }
        ans.push_back(num[0] ^ fst);
    }

    return ans;
}
