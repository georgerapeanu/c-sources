#include <bits/stdc++.h>

using namespace std;

map< vector<int>,vector<vector<int>> > classes;

int eval(vector<int> &p,vector<int> &v){
    int ans = 0;
    for(int i = 0;i < (int)v.size() - 1;i++){
        ans += abs(p[v[i] - 1] - p[v[i + 1] - 1]);
    }
    return ans;
}

int main(){
    int n;

    scanf("%d",&n);

    vector<int> perm;

    for(int i = 1;i <= n;i++){
        perm.push_back(i);
    }

    vector<vector<int>> all = {perm};

    while(next_permutation(perm.begin(),perm.end())){
        all.push_back(perm);
    }

    for(auto it:all){
        vector<int> ans;
        for(auto it2:all){
            ans.push_back(eval(it,it2));
        }
        classes[ans].push_back(it);
    }

    int lst = 0;

    for(auto it:classes){
        lst++;
        printf("class %d\n",lst);
        for(auto it2:it.second){
            for(auto it3:it2)printf("%d ",it3);printf("\n");
        }
    }

    return 0;
}
