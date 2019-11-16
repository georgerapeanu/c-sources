#include <bits/stdc++.h>

using namespace std;

string s;
int a[int(5e5) + 5];

int main() {
    cin >> s;

    a[0] = 0;

    int cnt_lst = 0;

    for(int i = 0; i < (int)s.size(); i++) {
        if(s[i] == '<') {
            cnt_lst++;
        }
        else {
            cnt_lst = 0;
        }
        a[i + 1] = cnt_lst;
    }

    cnt_lst = 0;

    for(int i = (int)s.size() - 1; i >= 0; i--) {
        if(s[i] == '>') {
            cnt_lst++;
        }
        else {
            cnt_lst = 0;
        }
        a[i] = max(a[i],cnt_lst);
    }

    long long sum = 0;

    for(int i = 0; i <= (int)s.size(); i++) {
        sum += a[i];
    }

    cout << sum << "\n";

    return 0;
}
