#include <cstdio>
#include <algorithm>

using namespace std;

int n;
int a[int(1e6) + 5];
int b[int(1e6) + 5];

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
    }
    for(int j = 1; j <= n; j++) {
        scanf("%d",&b[j]);
    }

    if(a[1] != b[1] || a[n] != b[n]) {
        printf("No\n");
        return 0;
    }

    for(int i = 1; i < n; i++) {
        a[i] = a[i + 1] - a[i];
        b[i] = b[i + 1] - b[i];
    }

    sort(a + 1,a + n);
    sort(b + 1,b + n);

    for(int i = 1; i < n; i++) {
        if(a[i] != b[i]) {
            printf("No\n");
            return 0;
        }
    }

    printf("Yes\n");

    return 0;
}
