#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

FILE *f = fopen("tubeyou.in","r");
FILE *g = fopen("tubeyou.ok","w");

const int NMAX = 250000;
const int QMAX = 250000;

int n,k,q;
int nxt[NMAX + 5];
int d[NMAX + 5];
bool viza[NMAX + 5];
bool vizb[NMAX + 5];
long long dista[NMAX + 5];
long long distb[NMAX + 5];

int main() {

    fscanf(f,"%d %d %d",&n,&k,&q);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d ",&nxt[i]);
    }

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d ",&d[i]);
    }

    while(q--) {
        int t;
        fscanf(f,"%d",&t);

        if(t == 0) {
            int x;
            fscanf(f,"%d",&x);
            for(int i = 1; i <= n; i++) {
                if(nxt[i] == x) {
                    nxt[i] = nxt[x];
                }
            }
        }
        else {
            int a,b;
            fscanf(f,"%d %d",&a,&b);
            memset(viza,0,sizeof(viza));
            memset(vizb,0,sizeof(vizb));
            memset(dista,0,sizeof(dista));
            memset(distb,0,sizeof(distb));
            while(viza[a] == false) {
                viza[a] = true;
                if(viza[nxt[a]] == false) {
                    dista[nxt[a]] = dista[a] + d[a] + k;
                }
                a = nxt[a];
            }
            long long ans = 1e18;
            while(vizb[b] == false) {
                vizb[b] = true;
                if(vizb[nxt[b]] == false) {
                    distb[nxt[b]] = distb[b] + d[b] + k;
                }
                if(viza[b] == true) {
                    ans = min(ans,max(dista[b],distb[b]));
                }
                b = nxt[b];
            }

            fprintf(g,"%lld\n",ans);
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
