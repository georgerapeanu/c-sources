#include <cstdio>
#include <cstdlib>

using namespace std;

const int MAXN = (int) 2e6;

int v[MAXN + 1];
int pi[MAXN + 1];

int sol[MAXN + 1];

int main() {
    FILE *fi, *fout;
    int t, i, j, n, s;
    fi = fopen("pscfft.in" ,"r");
    fout = fopen("pscfft.out" ,"w");
    fscanf(fi,"%d " ,&t);
    while(t > 0) {
        t--;
        fscanf(fi,"%d %d " ,&n,&s);
        for(i = 1; i <= n; i++) {
            fscanf(fi,"%d " ,&v[i]);
        }
        int sz = 1;
        sol[sz] = 0;
        while(sz * s <= MAXN) {
            int aux = sz;
            for(j = 1; j < s; j++) {
                for(i = 1; i <= aux; i++) {
                    sol[++sz] = sol[i] + j;
                    if(sol[sz] >= s)
                        sol[sz] -= s;
                }
            }
        }
        int k = 0;
        for(i = 2; i <= n; i++) {
            while(k > 0 && v[k + 1] != v[i])
                k = pi[k];
            if(v[k + 1] == v[i])
                k++;
            pi[i] = k;
        }
        k = 0;
        bool flag = 1;
        for(i = 1; i <= sz; i++) {
            while(k > 0 && v[k + 1] != sol[i])
                k = pi[k];
            if(v[k + 1] == sol[i])
                k++;
            if(k == n) {
                fprintf(fout,"%d\n" ,i - n);
                flag = 0;
                break;
            }
        }
        if(flag == 1)
            fprintf(fout,"-1\n");
    }
    fclose(fi);
    fclose(fout);
    return 0;
}
