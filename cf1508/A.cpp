#include <bits/stdc++.h>

using namespace std;

int t;
int n;
string s[3];

string solve(const string &a,const string &b,char c){
    int i = 0;
    int j = 0;

    string ans;

    while(i < (int)a.size() || j < (int)b.size()){
        if(i >= (int)a.size()){
            ans += b[j++];
        }else if(j >= (int)b.size()){
            ans += a[i++];
        }else if(a[i] == c && b[j] == c){
            ans += a[i];
            i++;j++;
        }else if(a[i] == c){
            ans += b[j++];
        }else{
            ans += a[i++];
        }
    }

    return ans;
}

int main(){

    cin >> t;

    while(t--){
        cin >> n;
        string ans = "";
        for(int i = 0;i < 3;i++){
            cin >> s[i];
        }

        for(auto c:{'0','1'}){
            for(int i = 0;i < 2;i++){
                for(int j = i + 1;j < 3;j++){
                    string tmp = solve(s[i],s[j],c);
                    if((int)ans.size() == 0 || (int)ans.size() > (int)tmp.size()){
                        ans = tmp;
                    }
                }
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
