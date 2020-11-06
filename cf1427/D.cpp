#include <bits/stdc++.h>

using namespace std;

int n;
int len;
int v[60];
int pos[60];
int tmp[60];

vector<vector<int> > ans;

void do_op(vector<pair<int,int> > op){
    vector<int> tmp;

    for(int i = (int)op.size() - 1;i >= 0;i--){
        for(int j = op[i].first;j <= op[i].second;j++){
            tmp.push_back(v[j]);
        }
    }

    for(int i = 1;i <= n;i++){
        v[i] = tmp[i - 1];
    }

    ans.push_back(vector<int>());

    for(auto it:op){
        if(it.second < it.first){
            continue;
        }
        ans.back().push_back(it.second - it.first + 1);
    }

    return ;
}

void init_pos(){
    for(int i = 1;i <= n;i++){
        pos[v[i]] = i;
    }
}

int main() {

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i]);
    }

    for(int l = n;l > 1;){
        init_pos();

        if(pos[l] <= pos[n]){
            if(pos[l - 1] > pos[n]){
                do_op({{1,pos[l] - 1},{pos[l],pos[n]},{pos[n] + 1,pos[l - 1]},{pos[l - 1] + 1,n}});
            }
            else{
                vector<pair<int,int> > tmp = {{1,pos[l - 1] - 1},{pos[l - 1],pos[l] - 1}};
                for(int i = l;i <= n;i++){
                    tmp.push_back({pos[i],pos[i]});
                }
                tmp.push_back({pos[n] + 1,n});
                do_op(tmp);
            }
        }
        else{
            if(pos[l - 1] > pos[l]){
                vector<pair<int,int> > tmp = {{1,pos[n] - 1}};
                for(int i = n;i >= l;i--){
                    tmp.push_back({pos[i],pos[i]});
                }
                tmp.push_back({pos[l] + 1,pos[l - 1]});
                tmp.push_back({pos[l - 1] + 1,n});
                do_op(tmp);
            }
            else{
                do_op({{1,pos[l - 1] - 1},{pos[l - 1],pos[n] - 1},{pos[n],pos[l]},{pos[l] + 1,n}});
            }
        }

        init_pos();

        if(pos[l] <= pos[n]){
            while(l > 1 && pos[l - 1] + 1 == pos[l]){
                l--;
            }
        }
        if(pos[l] >= pos[n]){
            while(l > 1 && pos[l - 1] == pos[l] + 1){
                l--;
            }
        }
    }

    init_pos();

    if(pos[1] > pos[n]){
        vector<pair<int,int>> tmp;

        for(int i = 1;i <= n;i++){
            tmp.push_back({i,i});
        }

        do_op(tmp);
    }

    printf("%d\n",(int)ans.size());

    for(auto it:ans){
        printf("%d ",(int)it.size());
        for(auto it2:it){
            printf("%d ",it2);
        }
        printf("\n");
    }

    return 0;
}
