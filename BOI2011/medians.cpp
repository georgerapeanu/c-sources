#include <cstdio>
#include <set>

using namespace std;

int n;
int a[200005];
int b[100005];
set<int> s;

int main() {

    scanf("%d",&n);

    for(int i = 1; i < 2 * n; i++) {
        s.insert(i);
    }

    for(int i = 1; i <= n; i++) {
        scanf("%d",&b[i]);
    }

    a[1] = b[1];
    s.erase(a[1]);

    for(int i = 2; i <= n; i++) {
        if(b[i - 1] > b[i]) {
            if(s.count(b[i])) {
                a[i * 2 - 2] = b[i];
                s.erase(a[i * 2 - 2]);
                a[i * 2 - 1] = *s.begin();
                s.erase(a[i * 2 - 1]);
            }
            else {
                a[i * 2 - 2] = *s.begin();
                s.erase(a[i * 2 - 2]);
                a[i * 2 - 1] = *s.begin();
                s.erase(a[i * 2 - 1]);
            }
        }
        else if(b[i - 1] == b[i]) {
            a[i * 2 - 2] = *s.begin();
            s.erase(a[i * 2 - 2]);
            a[i * 2 - 1] = *s.rbegin();
            s.erase(a[i * 2 - 1]);
        }
        else {
            if(s.count(b[i])) {
                a[i * 2 - 2] = b[i];
                s.erase(a[i * 2 - 2]);
                a[i * 2 - 1] = *s.rbegin();
                s.erase(a[i * 2 - 1]);
            }
            else {
                a[i * 2 - 2] = *s.rbegin();
                s.erase(a[i * 2 - 2]);
                a[i * 2 - 1] = *s.rbegin();
                s.erase(a[i * 2 - 1]);
            }
        }
    }

    for(int i = 1; i < 2 * n; i++) {
        printf("%d ",a[i]);
    }

    return 0;
}
