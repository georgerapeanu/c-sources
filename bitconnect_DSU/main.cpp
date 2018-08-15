///connect only

#include <cstdio>

using namespace std;

FILE *f = fopen("bitconnect.in","r");
FILE *g = fopen("bitconnect_connectMode_DSU.out","w");

const int NMAX = 1e5;
const int LGMAX = 30;///bitii sunt de la 0 la LGMAX -1
const int LEN = 1e4;

char buff[LEN];
int ind = LEN - 1;

int i32(){
    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    int rez = 0;

    while(buff[ind] >= '0' && buff[ind] <= '9'){
        rez = rez * 10 + (buff[ind] - '0');
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    return rez;
}

int DSU[NMAX + 5];

void init(){
    for(int i = 0;i < NMAX + 5;i++){
        DSU[i] = -1;
    }
}

int fi(int x){
    if(DSU[x] < 0){
        return x;
    }
    return DSU[x] = fi(DSU[x]);
}

void u(int x,int y){
    x = fi(x);
    y = fi(y);
    if(x == y){
        return ;
    }
    if(DSU[x] < DSU[y]){
        DSU[x] += DSU[y];
        DSU[y] = x;
    }
    else{
        DSU[y] += DSU[x];
        DSU[x] = y;
    }
}

int N;

int is_there_numbere_with_bit[LGMAX];

void baga(int x){
    for(int bit = 0;bit < LGMAX;bit++){
        if(!((x >> bit) & 1)){
            continue;
        }
        if(is_there_numbere_with_bit[bit]){
            u(is_there_numbere_with_bit[bit],x);
        }
        else{
            is_there_numbere_with_bit[bit] = x;
        }
    }
}

int main(){

    fprintf(g,"connect\n");
    N = i32();
    init();

    while(N--){
        int t,x,y;
        t = i32();
        if(t == 3){
            x = i32();
            y = i32();
            fprintf(g,"%d\n",fi(x) == fi(y));
        }
        else{
            x = i32();
            baga(x);
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
