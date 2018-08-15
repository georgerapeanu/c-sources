#include <cstdio>
#include <cstring>
using namespace std;
int T,N,S;
int rez[1000005];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        memset(rez,0,sizeof(rez));
        scanf("%d%d",&N,&S);
        if((N%2==0&&S%2==1)||S>9*N||(S==0||(N!=1&&S<=1))){printf("-1\n");continue;}
        else
        {
            int st=1,dr=N;
            for(st=1,dr=N;st<dr&&S>=18;st++,dr--)
            {
                rez[st]=rez[dr]=9;
                S-=18;
            }
            if(st<=dr)
            {
                if(st!=dr){rez[st]=rez[dr]=S/2;if(N%2)rez[N/2+(N%2)]=S%2;}
                else rez[st]=S;
            }
            for(int i=1;i<=N;i++)printf("%d",rez[i]);printf("\n");
        }
    }
    return 0;
}
