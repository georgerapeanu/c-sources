#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("nane.in","r");
FILE *g = fopen("nane.out","w");

const int NMAX = 1e5;
const int LGMAX = 30;

int n,k;
int active = 0;
int fr[LGMAX + 5];
int v[NMAX + 5];
long long ans = 0;

int main() {

    fscanf(f,"%d %d",&n,&k);

    int l = 1;

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&v[i]);
        for(int h = 0; h <= LGMAX; h++) {
            if((v[i] >> h) & 1) {
                if(fr[h] == 0) {
                    active++;
                }
                fr[h]++;
            }
        }
        while(active > k) {
            for(int h = 0; h <= LGMAX; h++) {
                if((v[l] >> h) & 1) {
                    fr[h]--;
                    if(fr[h] == 0) {
                        active--;
                    }
                }
            }
            l++;
        }
        ans += i - l + 1;
    }

    fprintf(g,"%lld\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
