#include <cstdio>
#include <algorithm>

using namespace std;

int main() {

    int q;

    scanf("%d\n",&q);

    int mx = 0,my = 0;

    for(int t = 0; t < q; t++) {
        char c;
        int x,y;
        scanf("%c %d %d\n",&c,&x,&y);
        if(x > y) {
            swap(x,y);
        }

        if(c == '+') {
            mx = max(mx,x);
            my = max(my,y);
        }
        else {
            printf(mx <= x && my <= y ? "YES\n":"NO\n");
        }
    }

    return 0;
}
