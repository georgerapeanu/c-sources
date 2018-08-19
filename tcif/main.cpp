#include <cstdio>
#include <fstream>
#include <algorithm>
#include <cstring>
#define val first
#define nr second
using namespace std;
FILE *f=fopen("tcif.in","r");
FILE *g=fopen("tcif.out","w");
char N[1005];
char rez[1005];
int dim,u;
int frecv[10],st;
pair<int,int> V[4];
int main()
{
    fscanf(f,"%d %d %d %d %d %d\n",&V[1].nr,&V[2].nr,&V[3].nr,&V[1].val,&V[2].val,&V[3].val);
    fgets(N+1,1005,f);
    sort(V+1,V+4);
    u=V[3].val;
    dim=strlen(N+1);
    if(N[dim]=='\n')
        dim--;
    frecv[V[1].val]+=V[1].nr;
    frecv[V[2].val]+=V[2].nr;
    frecv[V[3].val]+=V[3].nr;
    if(V[1].nr+V[2].nr+V[3].nr>dim)
    {
        if(V[1].val==0)
        {
           fprintf(g,"%d",V[2].val);
           V[2].nr--;
        }
        for(int i=1;i<=3;i++)
            while(V[i].nr)
            {
                V[i].nr--;
                fprintf(g,"%d",V[i].val);
            }
        return 0;
    }
    for(int i=1;i<=dim;i++)
    {
        if(frecv[N[i]-'0'])
        {
            frecv[N[i]-'0']--;
            rez[i]=N[i];
        }
        else
        {
            while(!frecv[u])
                u--;
            if(u>N[i]-'0')
            {
                int cu=0;
                for(cu=N[i]-'0'+1;cu<=9;cu++)
                    if(frecv[cu])
                        break;
                if(cu<u)
                    u=cu;
                rez[i]=u+'0';
                frecv[u]--;
            }
            else
            {
                while(u<=N[i]-'0')
                {
                    i--;
                    frecv[N[i]-'0']++;
                    u=max(u,N[i]-'0');
                }
                int cu=0;
                for(cu=N[i]-'0'+1;cu<=9;cu++)
                    if(frecv[cu])
                        break;
                if(cu<u)
                    u=cu;
                rez[i]=u+'0';
                frecv[u]--;
            }
            st=i+1;
            break;
        }
    }
    for(int i=0;i<=9;i++)
            while(frecv[i])
            {
                frecv[i]--;
                rez[st++]=i+'0';
            }
    fputs(rez+1,g);
    return 0;
}
