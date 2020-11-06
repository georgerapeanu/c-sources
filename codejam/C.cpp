#include <bits/stdc++.h>

using namespace std;

int t;

struct data_t {
    int l,r,id;
    bool operator < (const data_t &other)const {
        if(r != other.r) {
            return r < other.r;
        }
        if(l != other.l) {
            return l < other.l;
        }
        return id < other.id;
    }
};

int main() {

    scanf("%d",&t);

    for(int x = 1; x <= t; x++) {
        int n;
        vector<data_t> v;
        scanf("%d",&n);

        for(int i = 1; i <= n; i++) {
            int l,r;
            scanf("%d %d",&l,&r);
            v.push_back({l,r,i - 1});
        }

        string ans(n,' ');

        sort(v.begin(),v.end());

        int lst_a = -1e9;
        int lst_b = -1e9;
        char a = 'C',b = 'J';

        for(auto it:v) {
            if(lst_a > lst_b) {
                swap(lst_a,lst_b);
                swap(a,b);
            }
            if(it.l < lst_a) {
                ans = "IMPOSSIBLE";
                break;
            }
            if(it.l >= lst_b) {
                lst_b = it.r;
                ans[it.id] = b;
            }
            else {
                lst_a = it.r;
                ans[it.id] = a;
            }
        }

        cout << "Case #" << x << ": " + ans << "\n";
    }

    return 0;
}
