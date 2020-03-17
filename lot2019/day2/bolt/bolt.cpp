#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void fix(pair<int,int> &a,int mod) {
    if(a.first < 0) {
        a.first += mod;
    }
    if(a.first >= mod) {
        a.first -= mod;
    }
}

int gcd(int a,int b) {
    if(b == 0) {
        return a;
    }
    return gcd(b,a % b);
}

int play_bolt(int n,string k,vector<int> s) {

    int lcm = 1;

    for(auto it:s) {
        lcm = lcm * it / gcd(lcm,it);
    }

    vector<bool> bolt(10,false);
    vector<bool> reminder_bolt(lcm,false);
    vector<vector<pair<int,int> > > dp((int)k.size() + 1,vector<pair<int,int> >(lcm,make_pair(0,0)));
    vector<int> pw(k.size() + 1,1);

    for(int i = 1; i < (int)k.size(); i++) {
        pw[i] = 10 * pw[i - 1] % lcm;
    }

    for(auto it:s) {
        bolt[it] = true;
        for(int val = 0; val < lcm; val += it) {
            reminder_bolt[val] = true;
        }
    }

    for(int r = 0; r < lcm; r++) {
        dp[0][r] = {0,(reminder_bolt[r] == true ? -1:1)};
    }

    for(int i = 1; i <= (int)k.size(); i++) {
        for(int r = 0; r < lcm; r++) {
            dp[i][r] = {-1,1};
            fix(dp[i][r],n);
            for(int cf = 0; cf < 10; cf++) {
                if(bolt[cf]) {
                    dp[i][r].first += dp[i][r].second * (1 + (i == 1 ? 0:-1));
                    dp[i][r].second *= (i == 1 ? -1:1);
                    fix(dp[i][r],n);
                    continue;
                }
                dp[i][r].first += dp[i][r].second * (1 + dp[i - 1][(r + pw[i - 1] * cf) % lcm].first) % n;
                dp[i][r].second *= dp[i - 1][(r + pw[i - 1] * cf) % lcm].second;
                fix(dp[i][r],n);
            }
        }
    }

    int r = 0;
    pair<int,int> ans = {-1,1};

    for(int i = (int)k.size(); i; i--) {
        for(int cf = 0; cf < k[(int)k.size() - i] - '0'; cf++) {
            if(bolt[cf]) {
                ans.first += ans.second * (1 + (i == 1 ? 0:-1));
                ans.second *= (i == 1 ? -1:1);
                fix(ans,n);
                continue;
            }
            ans.first += ans.second * (1 + dp[i - 1][(r + pw[i - 1] * cf) % lcm].first) % n;
            ans.second *= dp[i - 1][(r + pw[i - 1] * cf) % lcm].second;
            fix(ans,n);
        }
        int cf = k[(int)k.size() - i] - '0';
        if(i == 1) {
            ans.first += ans.second;
            fix(ans,n);
            ///dont care about ans.second anymore
            break;
        }
        else if(bolt[cf]) {
            int par = 1 - (k.back() % 2);
            ans.first += (par == 1 ? ans.second:0);
            ans.second *= (par == 1 ? -1:1);
            fix(ans,n);
            break;
        }
        else {
            r = (r + pw[i - 1] * cf) % lcm;
        }
    }

    ans.first = ans.first * (-1) - 1;
    fix(ans,n);

    ans.first ++;

    return ans.first;
}

int n;
string k;
vector<int> s;

int main() {

    cin >> n >> k;
    int tmp;
    cin >> tmp;

    while(tmp--) {
        int cf;
        cin >> cf;
        s.push_back(cf);
    }

    cout << play_bolt(n,k,s);

    return 0;
}
