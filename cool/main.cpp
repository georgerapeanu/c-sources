#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
FILE *f = fopen("cool.in","r");
FILE *g = fopen("cool.out","w");
int T;
int N,K;
int V[5005];
int fr[5005];
int main()
{
    fscanf(f,"%d",&T);
    fscanf(f,"%d %d",&N,&K);
    for(int i = 1;i <= N;i++){
        fscanf(f,"%d",&V[i]);
    }
    if(T == 1){
        bool ok = 1;
        int maxi = 0,mini = 1 << 30;
        for(int i = 1;i <= K;i++){
            maxi = max(maxi,V[i]);
            mini = min(mini,V[i]);
            fr[V[i]]++;
            ok &= (fr[V[i]] <= 1);
        }
        if(ok && maxi - mini + 1== K){
            fprintf(g,"%d",maxi);
        }
        else{
            int nr = 0;
            for(int i = 1;i <= K;i++){
                nr += (fr[V[i]] == 1);
                ///fr[V[i]]--;
            }
            fprintf(g,"%d",nr);
        }
    }
    else{
        int maxlen = 0,nr = 0;
        for(int i = 1;i <= N;i++){
            memset(fr,0,sizeof(fr));
            bool ok = 1;
            int maxi = 0,mini = 1 << 30;
            for(int j = i;j <= N && ok;j++){
                fr[V[j]]++;
                maxi = max(maxi,V[j]);
                mini = min(mini,V[j]);
                ok &= (fr[V[j]] <= 1);
                if(ok && maxi - mini + 1 == j - i + 1){
                    if(maxlen < j - i + 1){
                        maxlen = j - i + 1;
                        nr = 1;
                    }
                    else if(maxlen == j - i + 1){
                        nr++;
                    }
                }
            }
        }
        fprintf(g,"%d\n%d",maxlen,nr);
    }
    fclose(f);
    fclose(g);
    return 0;
}
