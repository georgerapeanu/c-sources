#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;

pair<pair<int,int>,int> segm[NMAX + 5];
int ans[NMAX + 5];

int main() {

    int t;

    scanf("%d",&t);

    while(t--) {
        int n;
        scanf("%d",&n);
        for(int i = 0; i < n; i++) {
            scanf("%d %d",&segm[i].first.first,&segm[i].first.second);
            segm[i].second = i;
        }

        sort(segm,segm + n);

        int maxr = 0;
        bool found = false;

        for(int i = 0; i < n; i++) {
            if(i && maxr < segm[i].first.first) {
                for(int j = 0; j < i; j++) {
                    ans[segm[j].second] = 1;
                }
                for(int j = i; j < n; j++) {
                    ans[segm[j].second] = 2;
                }
                found = true;
            }
            maxr = max(maxr,segm[i].first.second);
        }

        if(!found) {
            printf("-1\n");
            continue;
        }

        for(int i = 0; i < n; i++) {
            printf("%d ",ans[i]);
        }
        printf("\n");
    }

    return 0;
}
