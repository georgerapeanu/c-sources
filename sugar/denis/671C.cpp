#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int NMAX = 2e5;
const int VMAX = 2e5;

int n;
int v[NMAX + 5];
vector<int> pos_with_val[VMAX + 5];

long long total_area;

set< pair<int,int> > points;

void add_point(int x,int y) {

    if(x < 1 || x > n || y < 1 || y > n) {
        return ;
    }

    if(points.empty()) {
        points.insert({x,y});
        total_area += 1LL * y * (n - x + 1);
        return ;
    }

    set< pair<int,int> > :: iterator it = points.lower_bound({x + 1,0});

    if(it != points.begin() && prev(it)->second >= y) {
        return ;
    }

    it = points.lower_bound({x,0});

    while(it != points.end() && it->second <= y) {
        set< pair<int,int> > :: iterator nit = next(it);

        int left = 0;
        int right = n + 1;

        if(it != points.begin()) {
            left = prev(it)->second;
        }
        if(next(it) != points.end()) {
            right = next(it)->first;
        }

        total_area -= 1LL * (it->second - left) * (right - it->first);

        points.erase(it);
        it = nit;
    }

    it = points.lower_bound({x,0});

    int left = 0;
    int right = n + 1;

    if(it != points.begin()) {
        left = prev(it)->second;
    }
    if(it != points.end()) {
        right = it->first;
    }

    total_area += 1LL * (y - left) * (right - x);
    points.insert({x,y});
}

long long add_val(int val) {
    vector<int> pos;

    for(int i = val; i <= VMAX; i += val) {
        for(auto it:pos_with_val[i]) {
            pos.push_back(it);
        }
    }

    sort(pos.begin(),pos.end());

    if((int)pos.size() < 2) {
        return 0;
    }

    long long initial_area = total_area;

    add_point(1,pos[(int)pos.size() - 2] - 1);
    add_point(pos[0] + 1,pos[(int)pos.size() - 1] - 1);
    add_point(pos[1] + 1,n);

    return (total_area - initial_area) * val;
}

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&v[i]);
        pos_with_val[v[i]].push_back(i);
    }

    long long ans = 0;

    for(int i = 2; i <= n; i++) {
        add_point(i,i - 1);
    }

    for(int i = VMAX; i >= 1; i--) {
        ans += add_val(i);
    }

    printf("%lld\n",ans);

    return 0;
}
