#include <cstdio>
#define min(a,b) a<b ? a:b
#define max(a,b) a>b ? a:b
using namespace std;
FILE *f,*g;
bool gasit=0;
int st[400],i,fn[400],nr,t,j,k;
short op[400];
char c;
int main()
{
    f=fopen("opmult.in","r");
    g=fopen("opmult.out","w");
    fscanf(f,"%d",&t);
    for(i=1;i<=t;i++)
    {
        fscanf(f,"%d ",&nr);
        c='\0';st[0]=0;gasit=0;
        while(c!='\n')
        {
            fscanf(f,"%c",&c);
            fscanf(f,"%d",&st[++st[0]]);
            if(c=='(')
               st[st[0]]++;
            fscanf(f,"%c%d",&c,&fn[st[0]]);
            fscanf(f,"%c",&c);
            if(c==')')
            fn[st[0]]--;
            fscanf(f,"%c",&c);
            if(c!='\n')
            {
                if(c=='n')
                op[st[0]]=0;
                else if(c=='u')
                op[st[0]]=1;
                else
                op[st[0]]=2;
            }
        }
        for(j=1;j<st[0];j++)
            if(op[j]==0)
            {
                st[j]=max(st[j],st[j+1]);
                fn[j]=min(fn[j],fn[j+1]);
                for(k=j+1;k<st[0];k++)
                {
                    st[k]=st[k+1];
                    fn[k]=fn[k+1];
                    op[k-1]=op[k];
                }
                st[0]--;
                op[st[0]]=op[st[0]+1];
                j--;
            }
            if(nr>=st[1]&&nr<=fn[1])
            gasit=1;
            for(j=1;j<st[0];j++)
            {
                    if(op[j]==1&&gasit==0)
                    {
                        if(nr>=st[j+1]&&nr<=fn[j+1])
                        gasit=1;
                    }
                    else if(op[j]==2&&gasit==1)
                    {
                        if(nr>=st[j+1]&&nr<=fn[j+1])
                        gasit=0;
                    }
            }
        fprintf(g,"%s\n",gasit==1 ? "DA":"NU");
    }
    fclose(f);
    fclose(g);
    return 0;
}
