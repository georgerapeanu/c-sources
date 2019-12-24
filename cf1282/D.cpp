#include <bits/stdc++.h>

using namespace std;

int ask(string s) {
    cout << s << endl;
    int ans;
    cin >> ans;
    if(ans == 0) {
        exit(0);
    }
    return ans;
}

int main() {

    string s = "";
    for(int i = 1; i <= 300; i++) {
        s += 'a';
    }

    int nr_a = 300 - ask(s);

    s = "";
    for(int i = 1; i <= 300; i++) {
        s += 'b';
    }

    int nr_b = 300 - ask(s);

    int n = nr_a + nr_b;

    s.resize(n);

    int init = nr_a;

    vector<int> pos = {};

    for(int i = 0; i < n - 1; i++) {
        s[i] = 'a';
        int tmp = ask(s);
        if(tmp < init) {
            pos.push_back(i);
        }
        s[i] = 'b';
    }

    for(auto it:pos) {
        s[it] = 'a';
        nr_a--;
    }

    s[n - 1] = (nr_a > 0 ? 'a':'b');

    ask(s);

    return 0;
}
