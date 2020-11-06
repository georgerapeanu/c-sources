#include <bits/stdc++.h>

using namespace std;

string s;

vector<pair<int,int> > stuff;

int main() {

    cin >> s;

    s = " " + s;

    vector<pair<int,string> > answers;

    int len = 0;
    for(int i = s.size() - 1;i;i--){
        len++;
        if(stuff.empty() || stuff.back().first > i + 1 || s[i] != s[i + 1]){
            stuff.push_back({i,i});
        }
        else{
            stuff.back().first = i;
            if((int)stuff.size() == 1 || s[stuff[(int)stuff.size() - 2].second] < s[i]){
                len -= ((stuff.back().second - stuff.back().first + 1) / 2) * 2;
                stuff.back().second -= ((stuff.back().second - stuff.back().first + 1) / 2) * 2;
                if(stuff.back().second < stuff.back().first){
                    stuff.pop_back();
                }
            }
        }
        
        vector<int> ans;

        bool ok = false;

        for(int i = (int)stuff.size() - 1;i >= 0 && ok == false;i--){
            for(int j = stuff[i].first;j <= stuff[i].second && ok == false;j++){
                ans.push_back(j);
                if((int)ans.size() >= 9){
                    ok = true;
                }
            }
            if((int)ans.size() >= 9){
                ok = true;
            }
        }

        ok = false;
        
        for(int i = 0;i < (int)stuff.size() && ok == false;i++){
            for(int j = stuff[i].second;j >= stuff[i].first && ok == false;j--){
                ans.push_back(j);
                if((int)ans.size() >= 11){
                    ok = true;
                }
            }
            if((int)ans.size() >= 11){
                ok = true;
            }
        }

        sort(ans.begin(),ans.end());
        ans.resize(unique(ans.begin(),ans.end()) - ans.begin());

        string string_ans = "";

        if((int)ans.size() > 10){
            for(int i = 0;i < 5;i++){
                string_ans += s[ans[i]];
            }
           
            for(int i = 5;i < 8;i++){
                string_ans += ".";
            }

            for(int i = (int)ans.size() - 2;i < (int)ans.size();i++){
                string_ans += s[ans[i]];
            }
        }
        else{
            for(auto it:ans){
                string_ans += s[it];
            }
        }

        answers.push_back({len,string_ans});
    }

    reverse(answers.begin(),answers.end());

    for(auto it:answers){
        cout << it.first << " " << it.second << "\n";
    }

    return 0;
}
