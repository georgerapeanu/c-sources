#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("superp.in","r");
FILE *g=fopen("superp.out","w");
short F[4];
long long A;
int N;
bool C1,C2;
long long rez;
bool tp(long long V)
{
    for(int i=3;i*i<=V;i+=2)
    {
        if(V%i==0)
            return 0;
    }
    return 1;
}
void btr(long long A,short V[])
{
    if(!tp(A))
        return ;
    rez=max(rez,A);
    if(V[0]<F[0])
    {
        V[0]++;
        btr(A*10+1,V);
        V[0]--;
    }
    if(V[1]<F[1])
    {
        V[1]++;
        btr(A*10+3,V);
        V[1]--;
    }
    if(V[2]<F[2])
    {
        V[2]++;
        btr(A*10+7,V);
        V[2]--;
    }
    if(V[3]<F[3])
    {
        V[3]++;
        btr(A*10+9,V);
        V[3]--;
    }
}
int main()
{
    fscanf(f,"%d",&N);
    while(N)
    {
        fscanf(f,"%lld",&A);
        F[0]=F[1]=F[2]=F[3]=0;
        C1=C2=0;
        while(A)
        {
            switch(A%10)
            {
                case 2:C1=1;break;
                case 5:C2=1;break;
                case 1:F[0]++;break;
                case 3:F[1]++;break;
                case 7:F[2]++;break;
                case 9:F[3]++;break;
            }
            A/=10;
        }
        rez=0;
        short V[4]={0,0,0,0};
        if(C1)
            btr(2,V);
        V[0]=0;V[1]=0;V[2]=0;V[3]=0;
        if(C2)
            btr(5,V);
        V[0]=0;V[1]=1;V[2]=0;V[3]=0;
        if(F[1])
            btr(3,V);
        V[0]=0;V[1]=0;V[2]=1;V[3]=0;
        if(F[2])
            btr(7,V);
        fprintf(g,"%lld\n",rez);
        N--;
    }
    return 0;
}
