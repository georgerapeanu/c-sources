#include <cstdio>

using namespace std;

FILE *f = fopen("cmmdc.in","r");
FILE *g = fopen("cmmdc.out","w");

int gcd(int a,int b){
    if(!b)return a;
    return gcd(b,a % b);
}

int main(){
    int x,y;
    fscanf(f,"%d %d",&x,&y);

    fprintf(g,"%d",gcd(x,y) == 1 ? 0 : gcd(x,y));

    fclose(f);
    fclose(g);

    return 0;
}
