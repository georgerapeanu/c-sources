#include <cstdio>
#include <map>
#include <algorithm>

using namespace std;

map<pair<int,int>,int> green;

const int NMAX = 2e5;
const int LGMAX = 18;

int r,c,t;
int father[LGMAX][NMAX + 5];

pair<int,int> point[NMAX + 5];

int main() {

    scanf("%d %d %d",&r,&c,&t);

    for(int i = 1; i <= t; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        green[ {x,y}] = i;
        point[i] = {x,y};
    }

    for(int i = 1; i <= t; i++) {
        map<pair<int,int>,int> :: iterator it = green.lower_bound({point[i].first + 1,point[i].second});
        if(it != green.end() && it->first.first == point[i].first + 1) {
            father[0][i] = it->second;
        }
    }

    for(int h = 1; h < LGMAX; h++) {
        for(int i = 1; i <= t; i++) {
            father[h][i] = father[h - 1][father[h - 1][i]];
        }
    }

    int q;

    scanf("%d",&q);

    while(q--) {
        int i,j,l,r;
        scanf("%d %d %d %d",&i,&j,&l,&r);
        if(j > r || i > l) {
            printf("No\n");
            continue;
        }
        if(i == l) {
            printf("Yes\n");
            continue;
        }
        map<pair<int,int>,int> :: iterator it = green.lower_bound({i,j});
        if(it == green.end() || it->first.first != i) {
            printf("No\n");
            continue;
        }
        int nod = it->second;
        int dist = l - i - 1;
        for(int h = LGMAX - 1; h >= 0; h--) {
            if((dist >> h) & 1) {
                dist ^= (1 << h);
                nod = father[h][nod];
            }
        }
        if(nod == 0 || point[nod].first != l - 1 || point[nod].second > r) {
            printf("No\n");
        }
        else {
            printf("Yes\n");
        }
    }

    return 0;
}
