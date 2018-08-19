#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
FILE *f=fopen("echer.in","r");
FILE *g=fopen("echer.out","w");
int L1,L2,N,M,P;
int X,Y;
int dim;
int main()
{
    fscanf(f,"%d",&P);
    fscanf(f,"%d %d %d %d",&L1,&L2,&N,&M);
    X=N/L1;
    Y=M/L2;
    dim=3*(min(X,Y)-1)+max((abs(X-Y))/2,0)*4+1+((X-Y)%2!=0);
    if(P==1){fprintf(g,"%d",dim);return 0;}
    for(int i=1;i<X&&i<Y;i++){
        fprintf(g,"%c ",'1');
        fprintf(g,"%c ",'2');
        fprintf(g,"%c ",'3');
    }
    if(X>=Y)
    {
        for(int i=1;i<X-Y;i+=2){
            fprintf(g,"%c ",'1');
            fprintf(g,"%c ",'4');
            fprintf(g,"%c ",'6');
            fprintf(g,"%c ",'3');
        }
        if((X-Y)%2==0){
            fprintf(g,"%c ",'1');
        }
        else{
            fprintf(g,"%c ",'1');
            fprintf(g,"%c ",'4');
        }
    }
    else
    {
        for(int i=1;i<Y-X;i+=2){
            fprintf(g,"%c ",'1');
            fprintf(g,"%c ",'2');
            fprintf(g,"%c ",'7');
            fprintf(g,"%c ",'5');
        }
        if((Y-X)%2==0)
        {
            fprintf(g,"%c ",'1');
        }
        else
        {
            fprintf(g,"%c ",'1');
            fprintf(g,"%c ",'2');
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
