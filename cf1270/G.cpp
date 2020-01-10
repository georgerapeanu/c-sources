#include <bits/stdc++.h>

using namespace std;

int t;
int n;
int a[1000005];

int viz[1000005];

int main() {

    scanf("%d",&t);

    while(t--) {
        scanf("%d",&n);

        for(int i = 1; i <= n; i++) {
            scanf("%d",&a[i]);
            viz[i] = 0;
        }

        int node = 1;

        viz[node] = 1;
        vector<int> tmp;
        vector<int> ans;

        while(true) {
            tmp.push_back(node);
            if(viz[node - a[node]] == 0) {
                viz[node - a[node]] = 1 + viz[node];
                node = node - a[node];
            }
            else {
                for(int i = viz[node - a[node]] - 1; i < (int)tmp.size(); i++) {
                    ans.push_back(tmp[i]);
                }
                break;
            }
        }

        printf("%d\n",(int)ans.size());

        for(auto it:ans) {
            printf("%d ",it);
        }
        printf("\n");
    }

    return 0;
}
