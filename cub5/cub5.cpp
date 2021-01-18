#include <cstdio>

using namespace std;

FILE *f = fopen("cub5.in","r");
FILE *g = fopen("cub5.out","w");

const int primes[] = {2,3,5,7};
const int pw3[] = {1,3,9,27};

int n;
int fr[81];
int pref_conf[4];

int main(){
    
    fscanf(f,"%d",&n);

    fr[0]++;

    long long ans = 0;

    for(int i = 1;i <= n;i++){
        int val;
        fscanf(f,"%d",&val);
        for(int k = 0;k < 4;k++){
            while(val % primes[k] == 0){
                val /= primes[k];
                pref_conf[k]++;
                if(pref_conf[k] == 3){
                    pref_conf[k] = 0;
                }
            }
        }
        int conf = 0;
        for(int k = 0;k < 4;k++){
            conf += pref_conf[k] * pw3[k];
        }
        ans += fr[conf];
        fr[conf]++;
    }

    fprintf(g,"%lld\n",ans);
    
    fclose(f);
    fclose(g);

    return 0;
}
