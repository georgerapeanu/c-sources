#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;
const int MMAX = 2e5;
const int QMAX = 1e5;
const int BUCK = 320;

int n,m;
int q;
vector<int> graph[NMAX + 5];
vector<pair<int,int> > cache[NMAX + 5];

bool banned[NMAX + 5];
vector<int> list;

int dp[NMAX + 5];

vector<pair<int,int> > tmp;

const int LEN = 1 << 14;
char buff[LEN];
int ind = LEN - 1;

int i32() {
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9') {
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }

    while(!(buff[ind] < '0' || buff[ind] > '9')) {
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }
    return ans;
}

bool used[NMAX + 5];
void merge_to(const vector<pair<int,int> > &s,vector<pair<int,int> > &t) {
    vector<pair<int,int> > tmp;
    int x = 0;
    int y = 0;

    while((int)tmp.size() < BUCK && (x < (int)s.size() || y < (int)t.size())) {
        if(x < (int)s.size() && (y == (int)t.size() || s[x].first + 1 >= t[y].first)) {
            if(used[s[x].second] == false) {
                tmp.push_back({s[x].first + 1,s[x].second});
                used[s[x].second] = true;
            }
            x++;
        }
        else {
            if(used[t[y].second] == false) {
                tmp.push_back(t[y]);
                used[t[y].second] = true;
            }
            y++;
        }
    }
    t = tmp;
    for(auto it:t) {
        used[it.second] = false;
    }
}

int main() {

    n = i32();
    m = i32();
    q = i32();

    for(int i = 1; i <= m; i++) {
        int x,y;
        x = i32();
        y = i32();
        graph[y].push_back(x);
    }

    for(int i = 1; i <= n; i++) {
        cache[i].push_back({0,i});
        for(auto it:graph[i]) {
            merge_to(cache[it],cache[i]);
        }
    }

    while(q--) {
        int town,sz;

        town = i32();
        sz = i32();

        for(int i = 1; i <= sz; i++) {
            int val;
            val = i32();
            list.push_back(val);
            banned[val] = true;
        }

        bool ok = false;

        for(auto it:cache[town]) {
            if(banned[it.second]) {
                continue;
            }
            printf("%d\n",it.first);
            ok = true;
            break;
        }

        if(ok == false) {
            for(int i = 1; i <= town; i++) {
                dp[i] = (banned[i] ? -1e9:0);
                for(auto it:graph[i]) {
                    dp[i] = max(dp[i],dp[it] + 1);
                }
            }
            printf("%d\n",(dp[town] < 0 ? -1:dp[town]));
        }

        for(auto it:list) {
            banned[it] = false;
        }
        list.clear();
    }

    return 0;
}
