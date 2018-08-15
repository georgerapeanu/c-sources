///O(Nlog^3N)

#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <cstring>

using namespace std;

FILE *f = fopen("bitconnect.in","r");
FILE *g1 = fopen("bitconnect_bitMode_Nlog^3N.out","w");
FILE *g2 = fopen("bitconnect_connectMode_Nlog^3N.out","w");

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

int N;

int viz[LGMAX];
int Q[LGMAX];
int stq,drq;

set<int> S[LGMAX * LGMAX];

void baga(int val){
    for(int bit = 0;bit < LGMAX;bit++){
        if(!((val >> bit) & 1)){
            continue;
        }
        for(int next_bit = bit + 1;next_bit < LGMAX;next_bit++){
            if(!((val >> next_bit) & 1)){
                continue;
            }
            S[bit * LGMAX + next_bit].insert(val);
        }
    }
}

void scoate(int val){
    for(int bit = 0;bit < LGMAX;bit++){
        if(!((val >> bit) & 1)){
            continue;
        }
        for(int next_bit = bit + 1;next_bit < LGMAX;next_bit++){
            if(!((val >> next_bit) & 1)){
                continue;
            }
            S[bit * LGMAX + next_bit].erase(val);
        }
    }
}

bool exists(int first_bit,int second_bit){
    if(first_bit > second_bit){
        swap(first_bit,second_bit);
    }
    return !S[first_bit * LGMAX + second_bit].empty();
}

int BFS(int x,int y){

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


    N = i32();
    while(N--){
        int t,x,y;
        t = i32();
        if(t == 3){
            x = i32();
            y = i32();
            int ans = BFS(x,y);
            fprintf(g1,"%d\n",ans);
            fprintf(g2,"%d\n",(ans != -1));
        }
        else{
            x = i32();
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
