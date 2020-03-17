#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

ifstream f("cbs.in");
ofstream g("cbs.out");

int k,n;
string a[11];

int main() {

    f >> k >> n;

    for(int i = 1; i <= k; i++) {
        f >> a[i];
        a[i] = " " + a[i];
    }

    int ans = 0;
    vector<int> heights(k + 1,0);
    vector<pair<int,int> > sta[11];
    map<vector<int>,pair<int,int> > penix;
    for(int i = 1; i <= k; i++) {
        sta[i].push_back({-(1 << 28),0});
    }
    for(int j = 1; j <= n; j++) {
        int lft = 0;
        for(int i = 1; i <= k; i++) {
            heights[i] += (a[i][j] == '(' ? 1:-1);
            while(sta[i].size() > 0 && heights[i] <= sta[i].back().first) {
                sta[i].pop_back();
            }
            lft = max(lft,sta[i].back().second);
        }

        pair<int,int> &tmp = penix[heights];

        if(tmp.first > lft) {
            ans += tmp.second++;
            tmp.first = j;
        }
        else {
            tmp = make_pair(j,1);
        }

        for(int i = 1; i <= k; i++) {
            sta[i].push_back({heights[i],j});
        }
    }

    g << ans << "\n";

    f.close();
    g.close();

    return 0;
}
