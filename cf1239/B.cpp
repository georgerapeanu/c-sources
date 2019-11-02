#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e5;

int n;
string s;
int pref[NMAX + 5];

int cnt = 0;
vector<int> v1;
vector<int> v2;

int cnt_1[NMAX + 5];
int cnt_2[NMAX + 5];

int fst_o[NMAX + 5];
int lst_c[NMAX + 5];

int main() {

    cin.sync_with_stdio(false);
    cin.tie(0);
    cout.sync_with_stdio(false);
    cout.tie(0);

    cin >> n;
    cin >> s;

    s = " " + s;

    for(int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + (s[i] == '(' ? 1 : -1);
    }

    if(pref[n] != 0) {
        printf("0\n1 1\n");
        return 0;
    }

    int pos = 0;

    for(int i = 1; i <= n; i++) {
        if(pref[i] < pref[pos]) {
            pos = i;
        }
    }

    string t = " ";

    for(int i = pos + 1; i <= n; i++) {
        t += s[i];
    }

    for(int i = 1; i <= pos; i++) {
        t += s[i];
    }

    s = t;
    cnt = 0;
    v1 = {0};
    v2 = {0};
    for(int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + (s[i] == '(' ? 1 : -1);
        cnt += (pref[i] == 0);
        cnt_1[i] = cnt_1[i - 1] + (pref[i] == 1);
        cnt_2[i] = cnt_2[i - 1] + (pref[i] == 2);
        lst_c[i] = (s[i] == ')' ? i:lst_c[i - 1]);

        if(pref[i] < 1) {
            v1.push_back(i);
        }
        if(pref[i] < 2) {
            v2.push_back(i);
        }
    }

    fst_o[n + 1] = n + 1;

    for(int i = n; i >= 0; i--) {
        fst_o[i] = (s[i] == '(' ? i:fst_o[i + 1]);
    }


    int best_ans = cnt;
    int x = 1,y = 1;

    for(int i = 0; i < (int)v1.size() - 1; i++) {
        int tmp_x = fst_o[v1[i] + 1];
        int tmp_y = lst_c[v1[i + 1]];


        if(tmp_x > tmp_y) {
            continue;
        }

        if(best_ans < cnt_1[tmp_y - 1] - cnt_1[tmp_x - 1]) {
            best_ans = cnt_1[tmp_y - 1] - cnt_1[tmp_x - 1];
            x = tmp_x;
            y = tmp_y;
        }
    }

    for(int i = 0; i < (int)v2.size() - 1; i++) {
        int tmp_x = fst_o[v2[i] + 1];
        int tmp_y = lst_c[v2[i + 1]];

        if(tmp_x > tmp_y) {
            continue;
        }

        if(best_ans < cnt + cnt_2[tmp_y - 1] - cnt_2[tmp_x - 1]) {
            best_ans = cnt + cnt_2[tmp_y - 1] - cnt_2[tmp_x - 1];
            x = tmp_x;
            y = tmp_y;
        }
    }

    x = (x + pos - 1) % n + 1;
    y = (y + pos - 1) % n + 1;

    printf("%d\n%d %d\n",best_ans,x,y);

    return 0;
}
