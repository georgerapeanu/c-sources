#include <cstdio>
#include <bitset>
#include <algorithm>
using namespace std;
FILE *f=fopen("ultimulcartus.in","r");
FILE *g=fopen("ultimulcartus.out","w");
int N,M;
int V[1000005];
int A[1000005];
int B[1000005];
int i;
int O;
int ops;
void Bubble(int gap) {
    bool ok = true;
    while (ok) {
        ok = false;
        for (int i = 1; i <= N - gap; ++ i)
            if (A[i] > A[i + gap]) {
                swap(A[i], A[i + gap]);
                ++ ops;
                ok = true;
            }
    }
}

void BubbleSort() {
    int gap = N;
    while (gap) {
        Bubble(gap);
        gap /= 2;
    }
}
bitset<5000> val;
void btr(int pas)
{
    if(pas>N)
    {
        ops=0;
        for(int i=1;i<=N;i++)
            A[i]=B[i];
        BubbleSort();
        if(ops>O)
            for(int i=1;i<=N;i++)
                V[i]=B[i];
        O=max(ops,O);
    }
    else
    {
        for(int i=1;i<=N;i++)
        {
            if(val[i]==0)
            {
                val[i]=1;
                B[pas]=i;
                btr(pas+1);
                val[i]=0;
            }
        }
    }
}
int main()
{
    int val;
    fscanf(f,"%d",&N);
    btr(1);
    fprintf(g,"%d\n1\n",O);
    fscanf(f,"%d",&M);
    for(i=1;i<=M;i++)
    {fscanf(f,"%d",&val);fprintf(g,"%d ",V[val]);}
    fclose(f);
    fclose(g);
    return 0;
}
/*
void rez(int st,int dr,int p2)
{
    if(st<dr)
    {
        int mid=(st+dr)/2;
        int j=mid+1;
        for(int i=st;i<=mid;i++)
        {
            if((V[i]/(p2/2))%2)
            {
                while((V[j]/(p2/2))%2==1)
                    j++;
                swap(V[i],V[j]);
            }
        }
        rez(st,mid,p2*2);
        rez(mid+1,dr,p2*2);
    }
}
*/
