#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
FILE *f=fopen("joc6.in","r");
FILE *g=fopen("joc6.out","w");
int st,mval;
long long maxsum,S;
int frecv[500005];
int N,K,P,i,j;
int V[500005];
int nr0,ramase,c;
int main()
{
    fscanf(f,"%d %d %d",&N,&K,&P);
    for(i=1;i<=K;i++)
    {
        mval=0;
        V[0]=0;
        for(j=1;j<=P;j++)
        {
            fscanf(f,"%d",&V[j]);
            frecv[V[j]]++;
            if(V[j]>mval)
                mval=V[j];
        }
        for(j=0;j<=mval;j++)
        {
            while(frecv[j])
            {
                V[++V[0]]=j;
                frecv[j]--;
            }
        }
        j=1;
        while(V[j]==0)
            j++;
        nr0=j-1;
        for(st=j,ramase=nr0,S=0;st<=P;st++)
        {
            for(j=st;j<=P;j++)
            {
                if(V[j]-1>V[j-1]&&j!=st)
                {
                    if(V[j]-V[j-1]-1>ramase)
                    {
                        ramase=nr0;
                        if(S>maxsum)
                        {maxsum=S;c=i;}
                        S=0;
                        break;
                    }
                    else
                    {
                        ramase-=(V[j]-V[j-1]-1);
                    }
                }
                S+=V[j];
            }
            ramase=nr0;
            if(S>maxsum)
            {maxsum=S;c=i;}
            S=0;
        }
    }
    fprintf(g,"%d %lld",c,maxsum);
    fclose(f);
    fclose(g);
    return 0;
}
