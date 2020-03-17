#include <cstdio>
#include <vector>
#include "library.h"
using namespace std;

const int NMAX = 1e3;

vector<pair<int,int> > edges;
vector<int> for_query;

int my_query(int n,int l,int r) {
    for(int i = 0; i < n; i++) {
        for_query[i] = (l - 1 <= i && i <= r - 1);
    }
    int ans = Query(for_query);
    ans = (r - l) - (ans - 1);
    for(auto it:edges) {
        ans -= (l <= it.first && it.second <= r);
    }
    return ans;
}

bool viz[NMAX + 5];
int gr[NMAX + 5];

void Solve(int n) {
    for_query = vector<int>(n,0);

    for(int t = 1; t < n; t++) {
        int l = 1,r = n;

        while(r - l > 1) {
            int mid = (l + r) / 2;
            if(my_query(n,1,mid) > 0) {
                r = mid;
            }
            else {
                l = mid;
            }
        }

        int lst = r;

        l = 1;
        r = lst;

        while(r - l > 1) {
            int mid = (l + r) / 2;
            if(my_query(n,mid,lst) > 0) {
                l = mid;
            }
            else {
                r = mid;
            }
        }

        int fst = l;

        edges.push_back({fst,lst});
        gr[fst]++;
        gr[lst]++;
    }

    vector<int> ans;

    for(int i = 1; i <= n; i++) {
        if(gr[i] <= 1) {
            ans.push_back(i);
            viz[i] = true;
            break;
        }
    }

    for(int i = 0; i < (int)ans.size(); i++) {
        for(int j = 0; j < (int)edges.size(); j++) {
            if(edges[j].first == ans[i] && viz[edges[j].second] == false) {
                ans.push_back(edges[j].second);
                viz[edges[j].second] = true;
                break;
            }
            else if(edges[j].second == ans[i] && viz[edges[j].first] == false) {
                ans.push_back(edges[j].first);
                viz[edges[j].first] = true;
                break;
            }
        }
    }

    Answer(ans);
}
