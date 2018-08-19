#include <cstdio>
#include <bitset>
using namespace std;
FILE *f=fopen("bowling.in","r");
FILE *g=fopen("bowling.out","w");
FILE *deg=fopen("bowling","w");
int SG[1005];
int SG2[]={4,1,2,8,1,4,7,2,1,8,2,7};
bitset<1005> B;
int N,T;
int ceva(int &a)
{
    int rez=0;
    if(a<=72)rez=SG[a];
    else {a-=72;rez=SG2[a%12];}
    a=0;
    return rez;
}
int main()
{
    for(int i=1;i<=995;i++)
    {
        B.reset();
        for(int j=1;j<=i;j++)
            B[SG[j-1]^SG[i-j]]=1;
        for(int j=1;j<i;j++)
            B[SG[j-1]^SG[i-j-1]]=1;
        while(B[SG[i]])
            SG[i]++;
        fprintf(deg,"%d,",SG[i]);
    }
    fscanf(f,"%d\n",&T);
    while(T--)
    {
        fscanf(f,"%d",&N);
        int con=0,val,rez=0;
        for(int i=1;i<=N;i++)
        {
            fscanf(f,"%d",&val);
            if(val)con++;
            else rez^=ceva(con);
        }
        rez^=ceva(con);
        if(rez==0)fputs("Fumeanu\n",g);
        else fputs("Nargy\n",g);
    }
    ///for(int i=1;i<=10000;i++){int tmp=i;fprintf(deg,"%d,",ceva(tmp));}
    fclose(f);
    fclose(g);
    return 0;
}
