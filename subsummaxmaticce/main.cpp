#include <cstdio>
#include <iostream>
using namespace std;
typedef pair<int,int> topleft;
typedef pair<int,int> downright;
typedef pair<topleft,downright> rasp;
FILE *f,*g;
int m[100][100],v[100],i,dreapta,stanga,n,m1,j,s,maxs,st,fn;
int reset()
{
    for(i=1;i<=(m1+1)/2;i++)
    v[i]=v[m1-i+1]=0;
}
int kadame(int arr[],int *first,int *final)
{
    int suma=0,maxsuma=0,localstart=1;
    for(i=1;i<=n;i++)
    {
        suma+=arr[i];
        if(suma<0)
        {
            localstart=i+1;
            suma=0;
        }
        else if(suma>maxsuma)
        {
            maxsuma=suma;
            *first=localstart;
            *final=i;
        }
    }
    if(maxsuma>0)
    return maxsuma;
    for(i=1;i<=n;i++)
    {
        if(arr[i]>maxsuma)
        {
            *first=i;
            *final=i;
        }
    }
    return maxsuma;
}
int main()
{
    f=fopen("input.in","r");
    g=fopen("output.out","w");
    fscanf(f,"%d %d",&n,&m1);
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m1;j++)
        fscanf(f,"%d",&m[i][j]);
    }
    rasp p;
    for(stanga=1;stanga<=m1;stanga++)
    {
        reset();
        for(dreapta=stanga;dreapta<=m1;dreapta++)
        {
            for(i=1;i<=n;i++)
            v[i]+=m[i][dreapta];
            s=kadame(v,&st,&fn);
            if(s>maxs)
            {
                maxs=s;
                p=rasp(topleft(st,stanga),downright(fn,dreapta));
            }
        }
    }
    fprintf(g,"%d\n%d %d\n%d %d",maxs,p.first.first,p.first.second,p.second.first,p.second.second);
    fclose(f);
    fclose(g);
    return 0;
}
