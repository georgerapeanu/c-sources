#include <cstdio>

using namespace std;

FILE *f = fopen("invinv.in","r");
FILE *g = fopen("invinv.out","w");

int t;
int n,k;

int main() {

    fscanf(f,"%d",&t);

    while(t--) {
        fscanf(f,"%d %d",&n,&k);
        int st = 1,dr = n;
        for(int i = 1; i <= n; i++) {
            if((n - i) <= k) {
                k -= (n - i);
                fprintf(g,"%d ",dr);
                dr--;
            }
            else {
                fprintf(g,"%d ",st);
                st++;
            }
        }
        fprintf(g,"\n");
    }

    fclose(f);
    fclose(g);

    return 0;
}
