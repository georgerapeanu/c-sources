#include <cstdio>

using namespace std;

int n;
int v[300005];

int main() {
    scanf("%d",&n);

    int len = 0;

    long long sum = 0;

    for(int i = 1; i <= n; i++) {
        scanf("%d",&v[i]);
        sum += v[i];

        if(len > 0 && v[len] % 2 == v[i] % 2) {
            len--;
        }
        else {
            v[++len] = v[i];
        }
    }

    for(int i = 1; i <= len; i++) {
        sum -= (v[i] & 1);
    }

    printf("%lld\n",sum / 2);



    return 0;
}
