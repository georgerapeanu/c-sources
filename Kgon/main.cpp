#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
FILE *f = fopen("kgon.in","r");
FILE *g = fopen("kgon.out","w");
const double PI = acos(-1);
const double eps = (1e-5);
double D[100005];
double dist,R;
int num[100005];
int N,K;
int rez;
int main(){
    fscanf(f,"%d %d %lf",&N,&K,&R);
    for(int i = 1;i <=  N;i++){
        fscanf(f,"%lf",&D[i]);
    }
    dist = 2 * PI * R / K;
    int j = 1;
    for(int i = 1;i <= N;i++){
        num[i] = 1;
        while(D[i] - D[j] - dist > eps){
            j++;
        }
        if(abs(D[i] - D[j] - dist) <= eps){
            num[i] += num[j];
        }
        rez += (num[i] == K);
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
