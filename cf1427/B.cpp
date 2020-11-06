#include <bits/stdc++.h>

using namespace std;

int main() {

    int t;
    int n,k;
    string s;

    cin >> t;

    while(t--){
        cin >> n >> k;
        cin >> s;
        
        int cst = 0;
        int cnt_lost = 0;
        bool is_w = false;
        vector<int> sz;

        int len = 0;

        for(int i = 0;i < (int)s.size();i++){
            cst += (s[i] == 'W') + (i > 0 && s[i] == 'W' && s[i - 1] == 'W');
            cnt_lost += (s[i] == 'L');
            is_w |= (s[i] == 'W');

            if(s[i] == 'L'){
                len++;
            }
            else{
                sz.push_back(len);
                len = 0;
            }
        }
        sz.push_back(len);

        if((int)sz.size() > 0){
            sz.pop_back();
        }
        reverse(sz.begin(),sz.end());
        if((int)sz.size() > 0){
            sz.pop_back();
        }

        sort(sz.begin(),sz.end());

        for(auto it:sz){
            if(it == 0){
                continue;
            }
            if(k >= it){
                k -= it;
                cnt_lost -= it;
                cst += 2 * it + 1;
            }
            else{
                break;
            }
        }

        if(is_w){
            cst += min(k,cnt_lost) * 2;
        }
        else{
            cst += max(0,min(k,cnt_lost) * 2 - 1);
        }

        printf("%d\n",cst);
    }

    return 0;
}
