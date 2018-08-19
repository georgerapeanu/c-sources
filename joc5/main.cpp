#include <cstdio>
using namespace std;
FILE *f = fopen("joc5.in","r");
FILE *g = fopen("joc5.out","w");
int T;
int N;
int main()
{
    while(1){
        fscanf(f,"%d",&N);
        if(!N){
            break;
        }
        int xo = 0;
        for(int i = 1;i <= N;i++){
            for(int j = 1;j <= N;j++){
                int val;
                fscanf(f,"%d",&val);
                if(i == j){
                    xo ^= val;
                }
            }
        }
        if(!xo){
            fprintf(g,"2\n");
        }
        else {
            fprintf(g,"1\n");
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
