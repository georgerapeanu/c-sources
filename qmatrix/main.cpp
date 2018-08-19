#include <cstdio>
using namespace std;
FILE *f=fopen("qmatrix.in","r");
FILE *g=fopen("qmatrix.out","w");
int v1,v2,v3;
int N,Q,i,j,k,L[4005][10],C[4005][10],maxk,st,dr,last,p,mid;
char ch;
int main()
{
    fscanf(f,"%d %d %d %d\n",&N,&v1,&v2,&Q);
    maxk=(N-1)*N+N+2;
    for(k=3;k<=maxk;k++)
    {
        i=(k/N)+1;
        j=(k%N)-2;
        if(j<=0)
        {
            j+=N;
            i--;
        }
        v3=(v1*i+v2*j+1)%10;
        L[i][v3]++;
        C[j][v3]++;
        v1=v2;
        v2=v3;
    }
    for(i=1;i<=N;i++)
    {
        for(j=0;j<=9;j++)
            {L[i][j]=L[i-1][j]+L[i][j];C[i][j]=C[i-1][j]+C[i][j];}
    }
    for(i=1;i<=Q;i++)
    {
        fscanf(f,"%c %d %d\n",&ch,&k,&p);
        if(ch=='L')
        {
            st=1;dr=N;last=0;
            while(st<=dr)
            {
                mid=(st+dr)/2;
                if(L[mid][p]<k)
                {
                    st=mid+1;
                }
                else
                {
                    last=mid;
                    dr=mid-1;
                }
            }
        }
        else
        {
           st=1;dr=N;last=0;
            while(st<=dr)
            {
                mid=(st+dr)/2;
                if(C[mid][p]<k)
                {
                    st=mid+1;
                }
                else
                {
                    last=mid;
                    dr=mid-1;
                }
            }
        }
        fprintf(g,"%d\n",last);
    }
    fclose(f);
    fclose(g);
    return 0;
}
