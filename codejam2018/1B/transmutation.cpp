#include <cstdio>
#include <cstring>
#include <queue>
#include <cassert>

using namespace std;

const long long LIM = 1e18;

long long recipe[105][105];
long long backup_recipe[105][105];

int t;
int n;

bool in_queue[105];

long long v[105];
long long backup_v[105];

long long abs(long long a) {
    return (a > 0 ? a:-a);
}

bool ok(long long val) {
    memcpy(v,backup_v,sizeof(backup_v));
    memcpy(recipe,backup_recipe,sizeof(backup_recipe));
    memset(in_queue,0,sizeof(in_queue));

    queue<int> bad_nodes;
    v[1] -= val;

    if(v[1] < 0) {
        bad_nodes.push(1);
        in_queue[1] = true;
    }

    while(bad_nodes.empty() == false) {

        long long sum = 0;

        for(int i = 1; i <= n; i++) {
            sum += v[i];
        }

        if(sum < 0) { ///Say NO to overflow
            return false;
        }

        int nod = bad_nodes.front();
        bad_nodes.pop();
        in_queue[nod] = false;

        if(recipe[nod][nod] != 0) {
            return false;
        }

        for(int i = 1; i <= n; i++) {
            assert(v[nod] == 0 || abs(recipe[nod][i]) <= abs(LIM / v[nod]));
            assert(LIM - abs(v[i]) >= abs(recipe[nod][i] * v[nod]));
            v[i] += recipe[nod][i] * v[nod];
            if(v[i] < 0 && in_queue[i] == false) {
                in_queue[i] = true;
                bad_nodes.push(i);
            }
        }
        v[nod] = 0;

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(j == nod) {
                    continue;
                }
                assert(recipe[nod][j] == 0 || recipe[i][nod] <= abs(LIM / recipe[nod][j]));
                assert(LIM - abs(recipe[i][j]) >= abs(recipe[nod][j] * recipe[i][nod]));
                recipe[i][j] += recipe[i][nod] * recipe[nod][j];
            }
            recipe[i][nod] = 0;
        }
    }

    return true;
}

int main() {

    scanf("%d",&t);

    for(int test = 1; test <= t; test++) {
        scanf("%d",&n);

        for(int i = 1; i <= n; i++) {
            int x,y;
            scanf("%d %d",&x,&y);
            for(int j = 1; j <= n; j++) {
                backup_recipe[i][j] = recipe[i][j] = (x == j) + (y == j);
            }
        }

        for(int i = 1; i <= n; i++) {
            scanf("%lld",&v[i]);
            backup_v[i] = v[i];
        }

        long long l = 0,r = 1e11 + 5;

        while(r - l > 1) {
            long long mid = (l + r) / 2;
            if(ok(mid)) {
                l = mid;
            }
            else {
                r = mid;
            }
        }

        printf("Case #%d: %lld\n",test,l);
    }

    return 0;
}
