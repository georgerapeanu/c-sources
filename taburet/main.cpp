#include <cstdio>
#define nmax 10005
using namespace std;
FILE *f=fopen("taburet.in","r");
FILE *g=fopen("taburet.out","w");
int tipuri[nmax][7],maxim;
int ctr[nmax];
int V[7];
int i,j,nrtipuri,N;
bool lafel(int A[],int B[])
{
    if(A[1]==B[1])
    {
        if(A[6]==B[6])
           {
               if(A[2]==B[2]&&A[3]==B[3]&&A[4]==B[4]&&A[5]==B[5])
                    return 1;
                else if(A[2]==B[3]&&A[3]==B[4]&&A[4]==B[5]&&A[5]==B[2])
                    return 1;
                else if(A[2]==B[4]&&A[3]==B[5]&&A[4]==B[2]&&A[5]==B[3])
                    return 1;
                else if(A[2]==B[5]&&A[5]==B[4]&&A[4]==B[3]&&A[3]==B[2])
                    return 1;
           }
    }
    if(A[1]==B[2])
    {
        if(A[6]==B[4])
        {
           if(A[4]==B[1]&&A[3]==B[3]&&A[2]==B[6]&&A[5]==B[5])
                return 1;
           if(A[5]==B[1]&&A[4]==B[3]&&A[3]==B[6]&&A[2]==B[5])
                return 1;
           if(A[2]==B[1]&&A[5]==B[3]&&A[4]==B[6]&&A[3]==B[5])
                return 1;
           if(A[3]==B[1]&&A[2]==B[3]&&A[5]==B[6]&&A[4]==B[5])
                return 1;
        }
    }
    if(A[1]==B[3])
    {
        if(A[6]==B[5])
        {
            if(A[4]==B[4]&&A[3]==B[6]&&A[2]==B[2]&&A[5]==B[1])
                return 1;
            if(A[5]==B[4]&&A[4]==B[6]&&A[3]==B[2]&&A[2]==B[1])
                return 1;
            if(A[2]==B[4]&&A[5]==B[6]&&A[4]==B[2]&&A[3]==B[1])
                return 1;
            if(A[3]==B[4]&&A[2]==B[6]&&A[5]==B[2]&&A[4]==B[1])
                return 1;
        }
    }
    if(A[1]==B[4])
    {
        if(A[6]==B[2])
        {
            if(A[4]==B[6]&&A[3]==B[3]&&A[2]==B[1]&&A[5]==B[5])
                return 1;
            if(A[5]==B[6]&&A[4]==B[3]&&A[3]==B[1]&&A[2]==B[5])
                return 1;
            if(A[2]==B[6]&&A[5]==B[3]&&A[4]==B[1]&&A[3]==B[5])
                return 1;
            if(A[3]==B[6]&&A[2]==B[3]&&A[5]==B[1]&&A[4]==B[5])
                return 1;
        }
    }
    if(A[1]==B[5])
    {
        if(A[6]==B[3])
        {
            if(A[4]==B[6]&&A[3]==B[4]&&A[2]==B[1]&&A[5]==B[2])
                return 1;
            if(A[5]==B[6]&&A[4]==B[4]&&A[3]==B[1]&&A[2]==B[2])
                return 1;
            if(A[2]==B[6]&&A[5]==B[4]&&A[4]==B[1]&&A[3]==B[2])
                return 1;
            if(A[3]==B[6]&&A[2]==B[4]&&A[5]==B[1]&&A[4]==B[2])
                return 1;
        }
    }
    if(A[1]==B[6])
    {
        if(A[6]==B[1])
        {
            if(A[4]==B[2]&&A[3]==B[3]&&A[2]==B[4]&&A[5]==B[5])
                return 1;
            if(A[5]==B[2]&&A[4]==B[3]&&A[3]==B[4]&&A[2]==B[5])
                return 1;
            if(A[2]==B[2]&&A[5]==B[3]&&A[4]==B[4]&&A[3]==B[5])
                return 1;
            if(A[3]==B[2]&&A[2]==B[3]&&A[5]==B[4]&&A[4]==B[5])
                return 1;
        }
    }
    return 0;
}
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d%d%d%d%d%d",&V[1],&V[2],&V[3],&V[4],&V[5],&V[6]);
        for(j=1;j<=nrtipuri;j++)
        {
            if(lafel(tipuri[j],V)==1)
            {
                ctr[j]++;
                if(ctr[j]>maxim)
                    maxim=ctr[j];
                break;
            }
        }
        if(j>nrtipuri)
        {
            ctr[j]++;
              if(ctr[j]>maxim)
                    maxim=ctr[j];
            nrtipuri++;
            tipuri[j][1]=V[1];
            tipuri[j][2]=V[2];
            tipuri[j][3]=V[3];
            tipuri[j][4]=V[4];
            tipuri[j][5]=V[5];
            tipuri[j][6]=V[6];
        }
    }
    fprintf(g,"%d\n%d",nrtipuri,maxim);
    fclose(f);
    fclose(g);
    return 0;
}
