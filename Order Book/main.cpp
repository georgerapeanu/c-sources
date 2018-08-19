#include <iostream>
using namespace std;
long ps[1001],pb[1001],vb[1001],vs[1001],n,nrb,nrs,ordb[1001],ords[1001],selb[51],sels[51];
short s;
char d;
void quickb(long left,long right)
{
    long i=left,j=right,pivot=pb[(left+right)/2],tmp=0;
    while(i<=j)
    {
        while(pb[i]<pivot)
        i++;
        while(pb[j]>pivot)
        j--;
        if(i<=j)
        {
            tmp=pb[i];
            pb[i]=pb[j];
            pb[j]=tmp;
            tmp=vb[i];
            vb[i]=vb[j];
            vb[j]=tmp;
            tmp=ordb[i];
            ordb[i]=ordb[j];
            p=ordb[j]=tmp;
            i++;j--;
        }
    }
    if(i<right)
    quickb(i,right);
    if(j>left)
    quickb(left,j);
}
void quicks(long left,long right)
{
    long i=left,j=right,pivot=ps[(left+right)/2],tmp=0;
    while(i<=j)
    {
        while(ps[i]<pivot)
        i++;
        while(ps[j]>pivot)
        j--;
        if(i<=j)
        {
            tmp=ps[i];
            ps[i]=ps[j];
            ps[j]=tmp;
            tmp=vs[i];
            vs[i]=vs[j];
            vs[j]=tmp;
            tmp=ords[i];
            ords[i]=ords[j];
            p=ords[j]=tmp;
            i++;j--;
        }
    }
    if(i<right)
    quickb(i,right);
    if(j>left)
    quickb(left,j);
}
int main()
{
    long i=0,ci=0;
    std::cin>>n>>s;
    for(i=1;i<=n;i++)
    {
        std::cin>>d;
        if(d=='B')
        {
            std::cin>>pb[++vb[0]];
            std::cin>>vb[vb[0]];
            ordb[vb[0]]=i;
        }
        else
        {
            std::cin>>ps[++vs[0]];
            std::cin>>vs[vs[0]];
             ords[vs[0]]=i;
        }
    }
    quickb(1,vb[0]);
    quicks(1,vs[0]);

    return 0;
}
