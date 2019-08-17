#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("supersenzor.in","r");
FILE *g = fopen("supersenzor.out","w");

const int NMAX = 50;
const int BUCK = 132908;
const int VMAX = 1e9;

int n,t;
int v[NMAX + 5];

int main() {

    fscanf(f,"%d %d",&n,&t);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&v[i]);
        v[i]--;
    }

    sort(v + 1,v + 1 + n);

    long long ans = 1LL << 62;

    for(int x = t; x <= BUCK; x++) {
        long long cost = 0;
        for(int i = 1; i <= n; i++) {
            cost += (v[i] / x + 1) * x;
        }
        ans = min(ans,cost);
    }

    vector<pair<int,int> > events;
    events.reserve(n * (VMAX / BUCK + 1) * 2);

    int start = 0;

    for(int i = 1; i <= n; i++) {
        int tmp = VMAX + 5;
        for(int weight = 1; weight <= v[i] / BUCK + 1; weight++) {
            int l = (v[i] / weight);
            int r = (weight == 1 ? VMAX + 4 : (v[i] / (weight - 1)));
            events.push_back({max(t,l + 1),+weight});
            events.push_back({max(t,r + 1),-weight});
            tmp = min(tmp,l + 1);
        }
        start = max(start,tmp);
    }

    sort(events.begin(),events.end());

    long long cost = 0;

    for(int i = 0; i < (int)events.size(); i++) {
        if(events[i].first == VMAX + 5) {
            break;
        }
        cost += events[i].second;
        if(events[i].first < start) {
            continue;
        }
        if(i == (int)events.size() - 1 || events[i].first != events[i + 1].first) {
            ans = min(ans,cost * events[i].first);
        }
    }

    fprintf(g,"%lld\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
