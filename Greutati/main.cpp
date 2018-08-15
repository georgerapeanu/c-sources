#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f = fopen("greutati.in","r");
FILE *g = fopen("greutati.out","w");
int frG1[100005];
int frG2[100005];
pair<int,int> V[100005];
int N,P;
const int MOD = (1e9) + 7;
long long lgpow(long long p,long long b,long long e){
    while(e){
        if(e & 1){
            p = min(((long long)((2e9) + 10)),b * p);
        }
        b = min(((long long)((2e9) + 10)),b * b);
        e >>= 1;
    }
    return p;
}
int lgpowMOD(int p,int b,int e){
    while(e){
        if(e & 1){
            p = 1LL * p * b % MOD;
        }
        b = 1LL * b * b % MOD;
        e >>= 1;
    }
    return p;
}
int main(){
    fscanf(f,"%d %d",&N,&P);
    for(int i = 1;i <= N;i++){
        fscanf(f,"%d %d",&V[i].first,&V[i].second);
    }
    sort(V + 1,V + 1 + N);
    long long demand = 0;
    for(int i = N;i;i--){
        if(i != N){
            demand = lgpow(demand,2,V[i + 1].first - V[i].first);
        }
        if(!demand){
            frG1[i] += (V[i].second >> 1) + (V[i].second & 1);
            frG2[i] += (V[i].second >> 1);
            demand = (V[i].second & 1);
        }
        else if(demand <= V[i].second){
            V[i].second -= demand;
            frG1[i] += (V[i].second >> 1) + (V[i].second & 1);
            frG2[i] += (V[i].second >> 1) + demand;
            demand = (V[i].second & 1);
        }
        else{
            demand -= V[i].second;
            frG2[i] += V[i].second;
        }
    }
    int rez = 0;
    for(int i = 1;i <= N;i++){
        rez += lgpowMOD(frG1[i],2,V[i].first);
        if(rez >= MOD){
            rez -= MOD;
        }
        rez -= lgpowMOD(frG2[i],2,V[i].first);
        if(rez < 0){
            rez += MOD;
        }
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
