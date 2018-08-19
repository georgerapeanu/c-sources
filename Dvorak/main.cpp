#include <cstdio>
#include <cstring>
using namespace std;
FILE *f = fopen("dvorak.in","r");
FILE *g = fopen("dvorak.out","w");
int N,Q,M;
char perm[30];
char pass[505];
char SIR[505];
bool same(int pos){
    for(int i = pos;i < pos + M;i++){
        if(SIR[i - pos] != pass[i]){
            return 0;
        }
    }
    return 1;
}
int main()
{
    fscanf(f,"%d\n",&Q);
    fgets(perm,30,f);
    fgets(pass + 1,505,f);
    N = strlen(pass + 1);
    N -= (pass[N] == '\n');
    while(Q--){
        int tip;
        fscanf(f,"%d ",&tip);
        if(tip == 1){
            int x,y;
            fscanf(f,"%d %d\n",&x,&y);
            for(int i = x;i <= y;i++){
                pass[i] = perm[pass[i] - 'a'];
            }
        }
        else{
            fscanf(f,"%s\n",SIR);
            M = strlen(SIR);
            M -= (SIR[M] == '\n');
            bool ok = 0;
            for(int i = 1;i <= N - M + 1;i++){
                if(same(i)){
                    fputs("Da\n",g);
                    ok = 1;
                    break;
                }
            }
            if(!ok){
                fputs("Nu\n",g);
            }
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
