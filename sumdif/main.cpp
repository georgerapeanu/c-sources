#include <cstdio>
using namespace std;
int n=0,k=0,a[1001],b[1001],c[1001];
void quick(int left,int right)
{
        int i=left,j=right,pivot;
        pivot=c[(left+right)/2];
        while(i<=j)
        {
            while(c[i]<pivot)
            i++;
            while(c[j]>pivot)
            j--;
            if(i<=j)
            {
                int tmp=0;
                tmp=c[i];
                c[i]=c[j];
                c[j]=tmp;
                tmp=a[i];
                a[i]=a[j];
                a[j]=tmp;
                tmp=b[i];
                b[i]=b[j];
                b[j]=tmp;
                i++;
                j--;
            }
        }
        if(i<right)
        quick(i,right);
        if(j>left)
        quick(left,j);
}
int main()
{
    FILE *f;
    f=fopen("sumdif.in","r");
    fscanf(f,"%d %d",&n,&k);
    int i=0;
    long suma=0;
    for(i=1;i<=n;i++)
    {
        fscanf(f,"%d %d",&a[i],&b[i]);
        c[i]=a[i]+b[i];
    }
    fclose(f);
    quick(1,n);
    for(i=n;i>=n-k+1;i--)
    {
        suma+=a[i]>b[i] ? a[i]:b[i];
    }
    for(i=n-k;i>=1;i--)
    {
        suma-=a[i]<b[i] ? a[i]:b[i];
    }
    f=fopen("sumdif.out","w");
    fprintf(f,"%ld",suma);
    fclose(f);
    return 0;
}
