#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
map<long long,vector<int> > L,R,rez;
int N,M;
long long OP[30];
void up(map<long long,vector<int> > &M,long long conf,vector<int> &WUT){
    if(!M.count(conf)){
        M[conf] = WUT;
    }
    else{
        vector<int> tmp = M[conf];
        if(tmp.size() > WUT.size()){
            M[conf] = WUT;
        }
        else if(tmp.size() == WUT.size()){
            int ind = 0;
            while(ind < (int)tmp.size() && tmp[ind] == WUT[ind]){
                ind++;
            }
            if(ind < (int)tmp.size() && tmp[ind] > WUT[ind]){
                M[conf] = WUT;
            }
        }
    }
}
void gen(map<long long,vector<int> > &M,int st,int dr){
    for(int conf = 0;conf < (1 << (dr - st + 1));conf++){
        long long realConf = 0;
        vector<int> WUT;
        for(int i = st;i <= dr;i++){
            if((conf >> (i - st)) & 1){
                realConf ^= OP[i];
                WUT.push_back(i);
            }
        }
        up(M,realConf,WUT);
    }
}
int main(){
    cin >> N >> M;
    for(int i = 1;i <= M;i++){
        int k;
        cin >> k;
        while(k--){
            int val;
            cin >> val;
            OP[i] ^= (1LL << (val - 1));
        }
    }
    gen(L,1,M / 2);
    gen(R,M / 2 + 1,M);
    for(auto it:L){
        if(R.count(((1LL << N) - 1) ^ it.first)){
            vector<int> tmp;
            for(auto it2:it.second){
                tmp.push_back(it2);
            }
            for(auto it2:R[((1LL << N) - 1) ^ it.first]){
                tmp.push_back(it2);
            }
            sort(tmp.begin(),tmp.end());
            up(rez,-1,tmp);
        }
    }
    cout << rez[-1].size() << "\n";
    for(auto it:rez[-1]){
        cout << it << " ";
    }
    return 0;
}
