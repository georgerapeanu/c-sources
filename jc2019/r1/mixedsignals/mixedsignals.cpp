#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

int n;
int t;
int tp[305];

int ask(const vector<int> &v) {
    cout << "1 " << v.size() << " ";
    for(auto it:v) {
        cout << it << " ";
    }
    cout << endl;
    int ans;
    cin >> ans;
    if(ans == -1) {
        exit(0);
    }
    return ans;
}

void answer() {
    cout << "0 ";
    for(int i = 1; i <= n; i++) {
        cout << tp[i] << " ";
    }
    cout << endl;
}

void solve() {

    mt19937 gen(0);

    cin >> n;

    vector<pair<int,int> > tmp;

    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            tmp.push_back({i,j});
        }
    }

    int u = -1,v = -1,ans = -1;
    while(true) {
        int id = gen() % (int)tmp.size();
        int ans_id = ask({tmp[id].first,tmp[id].second});

        if(ans_id != 2) {
            u = tmp[id].first;
            v = tmp[id].second;
            ans = ans_id;
            break;
        }
        else {
            swap(tmp[id],tmp.back());
            tmp.pop_back();
        }
    }

    int x = -1;

    for(int i = 1; i <= n; i++) {
        if(i == u || i == v) {
            continue;
        }
        tp[i] = ask({u,v,i});
        if(tp[i] != 2) {
            tp[i] ^= ans;
            if(x == -1) {
                x = i;
            }
        }
    }

    tp[u] = ask({x,u}) ^ tp[x];
    tp[v] = ans ^ tp[u];

    answer();
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
