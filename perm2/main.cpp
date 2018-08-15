#include <cstdio>

using namespace std;

FILE *f = fopen("perm2.in","r");
FILE *g = fopen("perm2.out","w");

int N;
int V[100005];
bool viz[100005];
long long rez = 1;

long long gcd(long long a,long long b){
    if(!b){
        return a;
    }
    return gcd(b,a % b);
}

int main(){
    fscanf(f,"%d",&N);
    for(int i = 1;i <= N;i++){
        fscanf(f,"%d",&V[i]);
    }

    for(int i = 1;i <= N;i++){
        if(!viz[i]){
            int len = 0;
            int nod = i;
            while(!viz[nod]){
                viz[nod] = 1;
                nod = V[nod];
                len++;
            }
            int d = gcd(rez,len);
            rez /= d;
            rez *= len;
        }
    }

    fprintf(g,"%lld",rez);

    fclose(f);
    fclose(g);

    return 0;
}
