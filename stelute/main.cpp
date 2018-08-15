#include <cstdio>
#include <cmath>
using namespace std;
FILE *f,*g;
int n,i,mid;
long long nr,maxrad,maxdist,dist,nrap=1,temp;
int main()
{
    f=fopen("stelute.in","r");
    fscanf(f,"%d",&n);
    for(i=1;i<=n;i++)
    {
        fscanf(f,"%lu",&nr);
        if(sqrt(double(nr))==int(sqrt(double(nr))))
        {
            temp=sqrt(double(nr));
            temp=(temp-1)*2+1;
            if(nr!=1)
            dist=temp/2;
            else
            dist=0;
            if(maxdist==dist)
            nrap++;
            if(maxdist<dist)
            {
                maxdist=dist;
                nrap=1;
            }
        }
        else
        {
            temp=int(sqrt(double(nr)))+1;
            temp=(temp-1)*2+1;
             mid=int(sqrt(double(nr)))*int(sqrt(double(nr)))+1+(temp/2);
             dist=mid-nr;
             if(dist<0)
             dist*=-1;
            if(maxdist<dist)
            {
                maxdist=dist;
                nrap=1;
            }
            else if(maxdist==dist)
            nrap++;
        }
    }
    fclose(f);
    g=fopen("stelute.out","w");
    fprintf(g,"%lu",nrap);
    fclose(g);
    return 0;
}
