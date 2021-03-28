#include <bits/stdc++.h>

using namespace std;

int t;
int n;

int ask(const vector<int> &l,const vector<int> &r){
    cout << "? " << (int)l.size() << " " << (int)r.size() << endl;
    for(auto it:l){
        cout << it << " "; 
    }
    cout << endl;
    for(auto it:r){
        cout << it << " ";
    }
    cout << endl;
    int ans;
    cin >> ans;
    return ans;
}

void answer(const vector<int> &v){
    cout << "! " << (int)v.size() << " ";

    for(auto it:v){
        cout << it << " ";
    }
    cout << endl;
}

int main(){

    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);

        vector<int> l = {1};
        vector<int> ans;
        int where = -1;
        for(int i = 2;i <= n;i++){
            if(ask(l,{i}) != 0){
                int l = 1;
                int r = i;
                where = i;
    
                while(r - l > 1){
                    int mid = (l + r) / 2;
                    vector<int> tmp;
                    for(int j = mid;j < i;j++){
                        tmp.push_back(j);
                    }
                    if(ask(tmp,{i})){
                        l = mid;
                    }else{
                        r = mid;
                    }
                }
    
                for(int j = 1;j < l;j++){
                    ans.push_back(j);
                }
                for(int j = r;j < i;j++){
                    ans.push_back(j);
                }
                break;
            }
            l.push_back(i);
        }
    
        for(int i = where + 1;i <= n;i++){
            if(ask({where},{i}) == 0){
                ans.push_back(i);
            }
        }
    
        answer(ans);
    }
    return 0;
}
