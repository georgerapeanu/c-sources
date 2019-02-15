#include <cstdio>

using namespace std;

int b,n;

int main() {
    scanf("%d %d",&b,&n);

    int ans = 0;

    for(int i = 1; i <= n; i++) {
        int val;
        scanf("%d",&val);
        if(i == n) {
            ans ^= (val & 1);
        }
        else if(b % 2 == 0) {
            ;
        }
        else {
            ans ^= ((val & 1));
        }
    }

    printf("%s",(ans == 0 ? "even" : "odd"));
}
