#include <bits/stdc++.h>
#include "ghinion.h"

#define MaxN 105

using namespace std;

long long ans = 0;
const char *symbols = "01^=";
char s[MaxN] = {};
int n = 6;

bool is_valid() {
    int prev_ans = -1;
    bool has_eq = false;
    int curr_ans = 0;
    int curr_num = 0;
    if (s[0] == '=' || s[n - 1] == '=' || s[0] == '^' || s[n - 1] == '^') {
        return false;
    }
    for (int i = 0; i < n; i++) {
        if (s[i] == '=') {
            if (i > 0 && (s[i - 1] == '=' || s[i - 1] == '^')) {
                return false;
            }
            has_eq = true;
            curr_ans ^= curr_num;
            curr_num = 0;
            if (prev_ans != -1 && prev_ans != curr_ans) {
                return false;
            }
            prev_ans = curr_ans;
            curr_ans = 0;
        } else if (s[i] == '^') {
            if (i > 0 && (s[i - 1] == '=' || s[i - 1] == '^')) {
                return false;
            }
            curr_ans ^= curr_num;
            curr_num = 0;
        } else {
            curr_num = curr_num * 2 + s[i] - '0';
        }
    }
    curr_ans ^= curr_num;
    curr_num = 0;
    if (prev_ans != -1 && prev_ans != curr_ans) {
        return false;
    }

    return has_eq;
}

void back(int lvl) {
    if (lvl == -1) {
        if (is_valid()) {
            // printf("%s\n", s);
            ans++;
        }
        return;
    }
    for (int i = 0; i < 4; i++) {
        s[lvl] = symbols[i];
        back(lvl - 1);
    }
}

int solve(int N, int M){
  ans = 0;
  n = N;
  back(n - 1);
  return ans % M;
}
