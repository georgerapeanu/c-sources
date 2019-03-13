#include <cstdio>
#include <map>

using namespace std;

FILE *f1 = fopen("in","r");
FILE *f2 = fopen("out","r");
FILE *f3 = fopen("ok","r");


const int NMAX = 1e5;

int n,nn,nnn;
int remap[NMAX + 5];
map<int,int> inv;

int main(){
    fscanf(f1,"%d",&n);
    fscanf(f2,"%d",&nn);
    fscanf(f3,"%d",&nnn);


    if(nnn == -1){
        if(nn != -1){
            printf("WA solution found when there is none\n");
            while(1);
        }
        else{
            printf("OK\n");
            return 0;
        }
    }
    else if(nn == -1){
        if(nnn != -1){
            printf("WA solution not found when there is one\n");
            while(1);
        }
        else{
            printf("OK\n");
            return 0;
        }
    }

    if(n != nn){
        printf("WA node count differs\n");
        while(1);
    }

    for(int i = 1;i <= n;i++){
        int val;
        fscanf(f1,"%d",&val);
        if(val == 0){
            remap[i] = i;
            inv[i] = i;
        }
    }

    int xo = n;

    for(int i = 1;i < n;i++){
        int x,y;
        int xx,yy;
        fscanf(f1,"%d %d",&x,&y);
        fscanf(f2,"%d %d",&xx,&yy);
        if(remap[x] == 0){
            remap[x] = xx;
            if(inv[xx]){
                printf("WA invalid remap1\n");
                while(1);
            }
            inv[xx] = x;
        }
        if(remap[y] == 0){
            remap[y] = yy;
            if(inv[yy]){
                printf("WA invalid remap2\n");
                while(1);
            }
            inv[yy] = y;
        }

        if(remap[x] != xx || remap[y] != yy){
            printf("WA invalid remap3\n");
            while(1);
        }

        xo ^= xx;
        xo ^= yy;
    }

    if(xo != 0){
        printf("WA xor not 0\n");
        while(1);
    }
    
    printf("OK\n");

    fclose(f1);
    fclose(f2);
    fclose(f3);

    return 0;
}
