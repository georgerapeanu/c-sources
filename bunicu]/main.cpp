#include <cstdio>
#include <bitset>
using namespace std;
FILE *f=fopen("bunicu.in","r");
FILE *g=fopen("bunicu.out","w");
int T,N;
int ind;
bitset<2049> B;
char c;
int main()
{
    fscanf(f,"%d",&T);
    for(;T;T--)
    {
        fscanf(f,"%d\n",&N);
        if(N==1)
        {
            char c=fgetc(f);
            fgetc(f);
            fputc('0'+'1'-c,g);
            fputc('\n',g);
            continue;
        }
        if(N==2)
        {
            char c1,c2,c3,c4;
            c1=fgetc(f);c2=fgetc(f);fgetc(f);c3=fgetc(f);c4=fgetc(f);fgetc(f);
            int a,b;a=(c1-'0')*2+(c2-'0');b=(c3-'0')*2+(c4-'0');
            if(a&&b) fputs("00\n",g);
            else if(a!=1&&b!=1) fputs("01\n",g);
            else if(a!=2&&b!=2) fputs("10\n",g);
            else fputs("11\n",g);
            continue;
        }
        B.reset();
        ind=0;
        int nr=0;
        while((1<<ind)<=N)
            ind++;
        for(int i=1;i<=N;i++)
        {
            bool valid=1;nr=0;
            for(int j=ind+1;j<N;j++)
            {
                char c=fgetc(f);
                valid&=(c=='0');
            }
            for(int j=ind;j>=0;j--)
            {
                char c=fgetc(f);
                nr=(nr<<1)+(c-'0');
            }
            if(valid)
                B[nr]=1;
            fgetc(f);
        }
        for(int i=ind+1;i<N;i++) fputc('0',g);
        int i=0;
        for(;B[i];i++);
        for(int j=(1<<ind);j;j>>=1)
            fputc((j&i)!=0 ? '1':'0',g);
        fputc('\n',g);
    }
    fclose(f);
    fclose(g);
    return 0;
}
