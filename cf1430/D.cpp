#include <bits/stdc++.h>

using namespace std;

void rem(string &s){
    char tmp = s.back();

    while((int)s.size() > 0 && s.back() == tmp){
        s.pop_back();
    }
}

int main() {

    int t;
    string s;

    cin >> t;


    while(t--){
        int n;
        int ans = 0;
        cin >> n;
        cin >> s;
        reverse(s.begin(),s.end());
        vector<pair<int,char> > v;

        for(auto it:s){
            if(v.empty() || v.back().second != it){
                v.push_back({0,it});
            }
            v.back().first++;
        }

        int j = (int)v.size() - 1;
        
        while(v.size()){
            ans++;
            if(v.back().first > 1){
                v.pop_back();
            }
            else{
                j = min(j,(int)v.size() - 1);
                while(j >= 0 && v[j].first == 1){
                    j--;
                }
                if(j >= 0){
                    v[j].first--;
                }
                else{
                    v.pop_back();
                }
                if(v.size()){
                    v.pop_back();
                }
            }
        }

        printf("%d\n",ans);
    }

    return 0;
}
