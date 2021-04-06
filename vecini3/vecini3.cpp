#include <cstdio>

using namespace std;

FILE *f = fopen("vecini3.in","r");
FILE *g = fopen("vecini3.out","w");

const int NMAX = 1e6;

int t;
int n,m;
int posA[NMAX + 5];
int posB[NMAX + 5];

int main(){
    fscanf(f,"%d",&t);

    while(t--){
        fscanf(f,"%d %d",&n,&m);

        for(int i = 1;i <= n || i <= m;i++){
            posA[i] = posB[i] = -1;
        }

        for(int i = 1;i <= n;i++){
            int value;
            fscanf(f,"%d",&value);
            posA[value] = (i & 1);
        }
        
        for(int i = 1;i <= m;i++){
            int value;
            fscanf(f,"%d",&value);
            posB[value] = (i & 1);
        }

        int disapear[] = {0,0};
        int transfer[] = {0,0};

        for(int i = 1;i <= n;i++){
            if(posB[i] == -1){
                disapear[posA[i]]++;
            }else if(posA[i] != posB[i]){
                transfer[posB[i]]++;
            }
        }

        if(disapear[0] <= disapear[1]){
            if(disapear[0] % 2 == 1){
                if(disapear[1] > 1){
                    disapear[0]--;
                    disapear[1]--;
                }
            }
        }else{
            if(disapear[1] % 2 == 1){
                if(disapear[0] > 1){
                    disapear[0]--;
                    disapear[1]--;
                }
            }
        }

        disapear[0] -= transfer[0] * 2;
        disapear[1] -= transfer[1] * 2;

        if(disapear[0] >= 0 && disapear[1] >= 0 && disapear[0] % 2 == 0 && disapear[0] == disapear[1]){
            fprintf(g,"1\n");
        }else{
            fprintf(g,"0\n");
        }
    }

    fclose(f);
    fclose(g);
}
