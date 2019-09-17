#include <cstdio>

using namespace std;

const int NMAX = 1e5;

int n,q,k;
int pula[NMAX + 5];

int main() {
    scanf("%d %d %d",&n,&q,&k);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&pula[i]);
    }

    while(q--) {
        int t,a,b;
        scanf("%d %d %d",&t,&a,&b);

        if(t == 1) {
            pula[a] = b;
        }
        else if(t == 2) {
            for(int i = a; i <=b; i++)pula[i] /= k;
        }
        else {
            long long sum = 0;
            for(int i = a; i <=b; i++) {
                sum += pula[i];
            }
            printf("%lld\n",sum);
        }
    }

    return 0;
}

