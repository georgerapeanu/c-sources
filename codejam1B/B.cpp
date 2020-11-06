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

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine gen (seed);

std::uniform_int_distribution<int> dist(-1e9,1e9);

int ask(long long x,long long y) {
    if(x < -1e9 || x > 1e9 || y < -1e9 || y > 1e9) {
        return 0;
    }
    cout << x << " " << y << endl;
    cout.flush();
    string ans;
    cin >> ans;

    //static int lst = 0;

    //lst++;

    //cerr << lst << " asking " << x << " " << y << " " << ans << endl;

    if(ans[0] == 'H') {
        return 1;
    }
    if(ans[0] == 'M') {
        return 0;
    }
    return 2;
}

void solve(int a,int b) {
    int x,y;

    int lx,ly,rx,ry;
    while(true) {
        x = dist(gen);
        y = dist(gen);

        int tmp = ask(x,y);

        if(tmp == 2) {
            return ;
        }
        if(tmp == 1) {
            break;
        }
    }

    long long l,r;

    l = x + 1e9;
    r = 2e9 + 1;

    while(r - l > 1) {
        int mid = (l + r) / 2;

        int tmp = ask(mid - 1e9,y);
        if(tmp == 2) {
            return ;
        }
        if(tmp == 1) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    rx = r - 1e9;

    l = -1;
    r = x + 1e9;

    while(r - l > 1) {
        int mid = (l + r) / 2;

        int tmp = ask(mid - 1e9,y);
        if(tmp == 2) {
            return ;
        }
        if(tmp == 0) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    lx = l - 1e9;


    l = y + 1e9;
    r = 2e9 + 1;

    while(r - l > 1) {
        int mid = (l + r) / 2;

        int tmp = ask(x,mid - 1e9);
        if(tmp == 2) {
            return ;
        }
        if(tmp == 1) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    ry = r - 1e9;


    l = 0;
    r = y + 1e9;

    while(r - l > 1) {
        int mid = (l + r) / 2;

        int tmp = ask(x,mid - 1e9);
        if(tmp == 2) {
            return ;
        }
        if(tmp == 0) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    ly = l - 1e9;

    vector<int> xs;
    vector<int> ys;

    const int delta = 3;

    int mx = (((long long)lx) + rx) / 2;
    int my = (((long long)ly) + ry) / 2;

    //cerr << "segments are " << " " << lx << " " << ly << " " << rx << " " << ry << endl;

    for(int i = mx - delta; i <= mx + delta; i++) {
        for(int j = my - delta; j <= my + delta; j++) {
            if(ask(i,j) == 2) {
                return ;
            }
        }
    }
}

int main() {


    int t;
    int a,b;


    cin >> t;

    cin >> a >> b;

    for(int i = 1; i <= t; i++) {

        solve(a,b);

    }

    return 0;
}
