#include <iostream>

using namespace std;

int t;
int x,y;
string s;

int solve(int l,int r){
    int ans = 1e9;

    if(l == -1 || r == (int)s.size()){
        ans = 0;
    }else{
        ans = max(0,int(s[r] - s[l])) * x + max(0,int(s[l] - s[r])) * y;
    }


    if(l == -1 && r == (int)s.size()){
        int local_ans_1 = 0;
        int local_ans_2 = 0;
        for(int i = 0;i < (int)s.size();i++){
            s[i] = '0' + (i % 2);
        }
        for(int i = 0;i < (int)s.size() - 1;i++){
            local_ans_1 += max(0,int(s[i + 1] - s[i])) * x + max(0,int(s[i] - s[i + 1])) * y;
        }
        
        for(int i = 0;i < (int)s.size();i++){
            s[i] = '1' - (i % 2);
        }
        for(int i = 0;i < (int)s.size() - 1;i++){
            local_ans_2 += max(0,int(s[i + 1] - s[i])) * x + max(0,int(s[i] - s[i + 1])) * y;
        }
        ans = min(ans,local_ans_1);
        ans = min(ans,local_ans_2);
    }else if(l == -1){
        int local_ans = 0;
        for(int i = r - 1;i > l;i--){
            s[i] = '0' + 1 - (s[i + 1] - '0');
        }
        for(int i = 0;i < r;i++){
            local_ans += max(0,int(s[i + 1] - s[i])) * x + max(0,int(s[i] - s[i + 1])) * y;
        }
        ans = min(ans,local_ans); 
    }else{
        int local_ans = 0;
        for(int i = l + 1;i < r;i++){
            s[i] = '0' + 1 - (s[i - 1] - '0');
        }
        for(int i = l;i < r && i < (int)s.size() - 1;i++){
            local_ans += max(0,int(s[i + 1] - s[i])) * x + max(0,int(s[i] - s[i + 1])) * y;
        }
        ans = min(ans,local_ans); 
    }

    return ans;
}

int main(){
    cin >> t;

    for(int test = 1;test <= t;test++){
        cin >> x >> y >> s;
        int ans = 0;

        int last_id = -1;

        for(auto &it:s){
            if(it == 'C'){
                it = '0';
            }else if(it == 'J'){
                it = '1';
            }
        }


        for(int i = 0;i <= (int)s.size();i++){
            if(i == (int)s.size() || s[i] != '?'){
                ans += solve(last_id,i);
                last_id = i;
            }
        }

        cout << "Case #" << test << ": " << ans << "\n";
    }

    return 0;
}
