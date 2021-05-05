#include <cstdio>
#include <cassert>

using namespace std;

FILE *f = fopen("fiboxor.in","r");
FILE *f1 = fopen("fiboxor.ok","r");
FILE *f2 = fopen("fiboxor.out","r");

int main() {

    int q;

    assert(fscanf(f,"%d",&q) == 1);

    while(q--) {
        int ans1,ans2;
        assert(fscanf(f1,"%d",&ans1) == 1);
        assert(fscanf(f2,"%d",&ans2) == 1);

        if(ans1 != ans2) {
            printf("WA\n");
            while(true);
        }
    }
    printf("OK\n");

    return 0;
}
