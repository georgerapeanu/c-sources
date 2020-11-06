#include <bits/stdc++.h>

using namespace std;

vector<string> vec_splitter(string s) {
    s += ',';
    vector<string> res;
    while(!s.empty()) {
        res.push_back(s.substr(0, s.find(',')));
        s = s.substr(s.find(',') + 1);
    }
    return res;
}
void debug_out(
    vector<string> __attribute__ ((unused)) args,
    __attribute__ ((unused)) int idx,
    __attribute__ ((unused)) int LINE_NUM) {
    cerr << endl;
}
template <typename Head, typename... Tail>
void debug_out(vector<string> args, int idx, int LINE_NUM, Head H, Tail... T) {
    if(idx > 0) cerr << ", ";
    else cerr << "Line(" << LINE_NUM << ") ";
    stringstream ss;
    ss << H;
    cerr << args[idx] << " = " << ss.str();
    debug_out(args, idx + 1, LINE_NUM, T...);
}
#ifdef XOX
#define debug(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#else
#define debug(...) 42
#endif

///at each operation you can either split the current stack in 2, sort them and merge them, or take the suits, separe them and sort them
int t;
int r,s;
int dp[50][50];
pair<int,int> bst[50][50];

const int NMAX = 40;

void solve(int r,int s) {
    if(s == 1 || r == 1) {
        return ;
    }
    if(bst[r][s].second == 0) {
        solve(r,bst[r][s].first);
        if(dp[r][s - bst[r][s].first]) {
            cout << r * bst[r][s].first << " " << r * (s - bst[r][s].first) << "\n";
            solve(r,s - bst[r][s].first);
        }

        int a = bst[r][s].first;
        int b = s - bst[r][s].first;

        for(int i = r - 1; i; i--) {
            cout << (i + 1) * a << " " << i * b << "\n";
            swap(a,b);
        }
    }
    else {

        int a = bst[r][s].first;
        int b = r - a;

        int n = r * s;


        for(int i = 1; i < s; i++) {
            cout << n - a - b << " " << b << "\n";
            n -= a;
        }

        solve(bst[r][s].first,s);

        if(dp[r - bst[r][s].first][s]) {
            cout << bst[r][s].first * s << " " << (r - bst[r][s].first) * s << "\n";
            solve(r - bst[r][s].first,s);
        }
    }
}

int main() {

    for(int i = 2; i <= NMAX; i++) {
        for(int j = 2; j <= NMAX; j++) {
            dp[i][j] = 1e9;
            for(int k = 1; k < j; k++) {
                int cst = (dp[i][k] + dp[i][j - k] + (dp[i][j - k] != 0) + (i - 1));
                if(cst < dp[i][j]) {
                    dp[i][j] = cst;
                    bst[i][j] = {k,0};
                }
            }
            for(int k = 1; k < i; k++) {
                int cst = (dp[k][j] + dp[i - k][j] + (dp[i - k][j] != 0) + (j - 1));
                if(cst < dp[i][j]) {
                    dp[i][j] = cst;
                    bst[i][j] = {k,1};
                }
            }
        }
    }

    cin >> t;

    for(int i = 1; i <= t; i++) {
        cin >> r >> s;

        cout << "Case #" << i << ": " << dp[r][s] << "\n";
        solve(r,s);
    }

    return 0;
}
