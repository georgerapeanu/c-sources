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

int mod(int a,int b) {
    a %= b;
    if(a < 0) {
        a += b;
    }

    return a;
}

int main() {

    int t;

    cin >> t;

    for(int i = 1; i <= t; i++) {
        int x,y;
        cin >> x >> y;

        string ans = "";

        for(int h = 0; h <= 30 && (x != 0 || y != 0); h++) {
            if(mod(x,2) + mod(y,2) != 1) {
                ans = "IMPOSSIBLE";
                break;
            }
            if(mod(x,2) == 1) {
                int ny = y / 2;
                int nx = (x - 1) / 2;
                int nx2 = (x + 1) / 2;
                if((nx2 != 0 || ny != 0) && ((nx == 0 && ny == 0) || mod(nx , 2) + mod(ny , 2) == 1)) {
                    ans += "E";
                    x = nx;
                    y = ny;
                }
                else {
                    ans += "W";
                    x = nx2;
                    y = ny;
                }
            }
            else {
                int nx = x / 2;
                int ny = (y - 1) / 2;
                int ny2 = (y + 1) / 2;

                if((nx != 0 || ny2 != 0) && ((nx == 0 && ny == 0) || mod(nx , 2) + mod(ny , 2) == 1)) {
                    ans += "N";
                    x = nx;
                    y = ny;
                }
                else {
                    ans += "S";
                    x = nx;
                    y = ny2;
                }
            }
        }
        if(x != 0 || y != 0) {
            ans = "IMPOSSIBLE";
        }

        cout << "Case #" << i << ": " << ans << "\n";
    }

    return 0;
}
