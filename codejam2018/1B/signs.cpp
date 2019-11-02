#include <cstdio>
#include <algorithm>

using namespace std;

int t;
int n;
pair<int,int> stuff[int(1e6+6)];

int main() {

    scanf("%d",&t);

    for(int test = 1; test <= t; test++) {
        scanf("%d",&n);

        for(int i = 1; i <= n; i++) {
            int a,b,c;
            scanf("%d %d %d",&a,&b,&c);
            stuff[i] = {a + b,a - c};
        }

        int ans = 0;
        int lst_col = 0;
        int lst_lin = 0;

        for(int i = 1; i <= n; i++) {
            lst_lin = ((i == 0 || stuff[i - 1].first != stuff[i].first) ? i - 1:lst_lin);
            lst_col = ((i == 0 || stuff[i - 1].second != stuff[i].second) ? i - 1:lst_col);
        }
        printf("Case #%d: %d\n",test,ans);
    }

    return 0;
}
