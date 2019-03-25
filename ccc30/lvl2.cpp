#include <bits/stdc++.h>

using namespace std;

const int LENMAX = 3e6;

const int dy[] = {-1,0,1,0};
const int dx[] = {0,1,0,-1};

int x,y;

char c[LENMAX + 5];

struct op_t {
    bool turn;
    int steps;
}

int main() {
    int n,m;
    int dir = 1;

    scanf("%d %d\n",&n,&m);
    scanf("%d %d\n",&x,&y);

    fgets(c + 1,LENMAX + 5,stdin);

    vector<op_t> v;

    for(int x = 1;

    for(auto it:ans) {
        printf("%d %d\n",it.first,it.second);
        }

    return 0;
}
