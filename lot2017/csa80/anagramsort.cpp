#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int ask(const vector<int> &v) {
    for(auto it:v) {
        cout << it << " ";
    }
    cout << endl;
    int ans;
    cin >> ans;
    return ans;
}

int n;
int fr[505];
int vmax = 0;
vector<int> positions[505];

int main() {

    cin >> n;

    for(int i = 1; i <= n; i++) {
        int val;
        cin >> val;
        fr[val]++;
        vmax = max(val,vmax);
    }

    vector<int> v;

    for(int i = 1; i <= vmax; i++) {
        for(int j = 1; j <= fr[i]; j++) {
            v.push_back(i);
        }
    }

    int lst_ans = ask(v);

    for(int i = 1; i <= vmax; i++) {
        int pos = fr[i] - 1;
        for(int h = 1; h <= fr[i] - (i == vmax); h++) {
            for(int j = pos; j + 1< (int)v.size() ; j++) {
                swap(v[j],v[j + 1]);
            }
            int ans = ask(v);
            int delta = (fr[i] - 1 - pos) + (ans - lst_ans) - pos;///bigger - smaller
            int cnt_smaller = ((n - 1) - delta) / 2;
            positions[i].push_back(cnt_smaller);
            lst_ans = ans;
            pos--;
        }
    }

    v = vector<int>(n,0);

    for(int i = 1; i <= vmax; i++) {
        for(auto it:positions[i]) {
            v[it] = i;
        }
    }

    for(auto &it:v) {
        if(it == 0) {
            it = vmax;
        }
    }

    ask(v);

    return 0;
}
