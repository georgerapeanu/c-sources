#include <bits/stdc++.h>

using namespace std;

vector<pair<int,int> > op;

void solve_pow2(int l,int r){
    if(l == r){
        return ;
    }

    int mid = (l + r) / 2;
    
    solve_pow2(l,mid);
    solve_pow2(mid + 1,r);

    for(int i = l;i <= mid;i++){
        op.push_back({i,mid + i - l + 1});
    }
}

void afis(){
    printf("%d\n",(int)op.size());

    for(auto it:op){
        printf("%d %d\n",it.first,it.second);
    }
    
    exit(0);
}

vector<vector<int> > comps;

bool cmp(const vector<int> &a,const vector<int> &b){
    return a.size() > b.size();
}

int main() {

    int n;

    scanf("%d",&n);

    int pos = n;
    int big = 0;
    int big2 = 0;
    for(int shft = 1 << 20,h = 20;shft;shft >>= 1,h--){
        if(pos - shft >= 0){
            solve_pow2(pos - shft + 1,pos);
            vector<int> tmp;
            for(int i = pos - shft + 1;i <= pos;i++){
                tmp.push_back(i);
            }
            comps.push_back(tmp);
            pos -= shft;
        }
    }

    sort(comps.begin(),comps.end(),cmp);

    while((int)comps.size() > 2){
        vector<int> tmp;
        while((int)comps.back().size() > 0){
            op.push_back({comps[0].back(),comps.back().back()});
            tmp.push_back(comps[0].back());comps[0].pop_back();
            tmp.push_back(comps.back().back());comps.back().pop_back();
        }
        comps.pop_back();
        while(comps.back().size() == tmp.size()){
            vector<int> tmp2;
            while((int)comps.back().size() > 0){
                op.push_back({tmp.back(),comps.back().back()});
                tmp2.push_back(tmp.back());tmp.pop_back();
                tmp2.push_back(comps.back().back());comps.back().pop_back();
            }
            comps.pop_back();
            tmp = tmp2;
        }
        comps.push_back(tmp);
    }

    afis();

    return 0;
}
