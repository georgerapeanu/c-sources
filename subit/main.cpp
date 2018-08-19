#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
FILE *f=fopen("subbit.in","r");
FILE *g=fopen("subbit.out","w");
vector <short> A;
char B[5000005];
int lung,ctr,N,i;
long long rez;
vector <short> ::iterator it;
void add()
{
    A[lung]++;
    for(int i=lung;i>1&&A[i]/2;i--)
    {
        A[i-1]+=A[i]/2;
        A[i]%=2;
    }
    while(A[1]/2)
    {
        it=A.begin();
        A.insert(it+1,A[1]/2);
        A[2]%=2;
        lung++;
    }
}
int main()
{
    A.push_back(0);
    A.push_back(0);
    lung=1;
    ctr=1;
    fgets(B+1,5000005,f);
    B[0]='.';
    N=strlen(B)-1;
    while(ctr<N)
    {
        rez+=lung;
        for(i=1;i<=lung;i++)
           {
               if(B[ctr]-'0'==A[i])
                ctr++;
            if(ctr==N)
            {
                rez=rez-lung+i;
                break;
            }
           }
        add();
    }
    fprintf(g,"%lld",rez);
    return 0;
}
