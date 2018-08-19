#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f = fopen("zigzag2.in","r");
FILE *g = fopen("zigzag2.out","w");
int N,K;
int V[1000005];
int main(){
    fscanf(f,"%d %d",&N,&K);
    for(int i = 1;i <= N;i++){
        fscanf(f,"%d",&V[i]);
    }
    int num = 0,j = 2;
    long long rez = 0;
    for(int i = 1;i <= N - 2;i++){
        j = max(i + 1,j);
        while(j <= N && num <= K){
            j++;
            num += (!((V[j - 1] < V[j] && V[j - 2] > V[j - 1]) || (V[j - 1] > V[j] && V[j - 1] > V[j - 2])));
        }
        rez += j - i - 2;
        num -= (!((V[i] < V[i + 1] && V[i + 1] > V[i + 2]) || (V[i] > V[i + 1] && V[i + 1] < V[i + 2])));
    }
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
