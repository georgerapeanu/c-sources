#include <bits/stdc++.h>

using namespace std;

int n,m;
string s[105];

int get(int x,int y) {
    if(s[x][y] == '.' || s[x][y] == 'x' || s[x][y] == 'o') {
        return (s[x][y] != 'x') * 1e9;
    }
    if(s[x][y] == '<') return 1 + get(x,y - 1);
    if(s[x][y] == '>') return 1 + get(x,y + 1);
    if(s[x][y] == '^') return 1 + get(x - 1,y);
    if(s[x][y] == 'v') return 1 + get(x + 1,y);
}


int main() {

    cin >> n >> m;

    int x,y;

    for(int i = 1; i <= n; i++) {
        cin >> s[i];
        s[i] = " " + s[i];
        for(int j = 1; j <= m; j++) {
            if(s[i][j] == 'o') {
                x = i;
                y = j;
            }
        }
    }

    pair<int,char> best_ans = {1e9,'Z'};

    best_ans = min(best_ans,make_pair(get(x - 1,y),'N'));
    best_ans = min(best_ans,make_pair(get(x + 1,y),'S'));
    best_ans = min(best_ans,make_pair(get(x,y + 1),'E'));
    best_ans = min(best_ans,make_pair(get(x,y - 1),'W'));

    if(best_ans.first < 1e9) {
        cout << ":)\n" << best_ans.second;
    }
    else {
        cout << ":(";
    }

    return 0;
}


