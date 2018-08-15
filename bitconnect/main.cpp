///O(Nlog^2N)
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

FILE *f = fopen("bitconnect.in","r");
FILE *g1 = fopen("bitconnect_bitMode.out","w");
FILE *g2 = fopen("bitconnect_connectMode.out","w");

const int NMAX = 1e5;
const int LGMAX = 62;///bitii sunt de la 0 la LGMAX -1
const int LEN = 1e4;

char buff[LEN];
int ind = LEN - 1;

long long i64(){
    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    long long rez = 0;

    while(buff[ind] >= '0' && buff[ind] <= '9'){
        rez = rez * 10 + (buff[ind] - '0');
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    return rez;
}

int N;

int viz[LGMAX + 5];
long long Q[LGMAX + 5];
int stq,drq;

int how_many[LGMAX * LGMAX + 5];

void baga(long long val){
    for(int bit = 0;bit < LGMAX;bit++){
        if(!((val >> bit) & 1)){
            continue;
        }
        for(int next_bit = bit + 1;next_bit < LGMAX;next_bit++){
            if(!((val >> next_bit) & 1)){
                continue;
            }
            how_many[bit * LGMAX + next_bit]++;
        }
    }
}

void scoate(long long val){
    for(int bit = 0;bit < LGMAX;bit++){
        if(!((val >> bit) & 1)){
            continue;
        }
        for(int next_bit = bit + 1;next_bit < LGMAX;next_bit++){
            if(!((val >> next_bit) & 1)){
                continue;
            }
            how_many[bit * LGMAX + next_bit]--;
        }
    }
}

bool exists(int first_bit,int second_bit){
    if(first_bit > second_bit){
        swap(first_bit,second_bit);
    }
    return how_many[first_bit * LGMAX + second_bit] > 0;
}

int BFS(long long x,long long y){

    if(x == y){
        return 0;
    }

    stq = 1;drq = 0;
    memset(viz,0,sizeof(viz));

    for(int bit = 0;bit < LGMAX;bit++){
        if((x >> bit) & 1){
            viz[bit] = 1;
            Q[++drq] = bit;
            if((y >> bit) & 1){
                return 1;
            }
        }
    }

    while(stq <= drq){
        int bit = Q[stq++];
        for(int next_bit = 0;next_bit < LGMAX;next_bit++){
            if(!viz[next_bit] && exists(bit,next_bit)){
                viz[next_bit] = 1 + viz[bit];
                Q[++drq] = next_bit;
                if((y >> next_bit) & 1){
                    return viz[next_bit];
                }
            }
        }
    }
    return -1;
}

int main(){

    fprintf(g1,"bit\n");
    fprintf(g2,"connect\n");


    N = i64();
    while(N--){
        int t;
		long long x,y;
        t = i64();
        if(t == 3){
            x = i64();
            y = i64();
            int ans = BFS(x,y);
            fprintf(g1,"%d\n",ans);
            fprintf(g2,"%d\n",(ans != -1));
        }
        else{
            x = i64();
            if(t == 1){
                baga(x);
            }
            else{
                scoate(x);
            }
        }
    }

    fclose(f);
    fclose(g1);
    fclose(g2);

    return 0;
}
