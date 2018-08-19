#include <cstdio>
using namespace std;
FILE *f=fopen("teatru.in","r");
FILE *g=fopen("teatru.out","w");
int Z,C,N,i,dr,nr,st,j;
int frecv[30];
char S[55005];
int main()
{
    fscanf(f,"%d %d\n",&Z,&C);
    fgets(S+1,55005,f);
    j=1;
    for(i=1;i<=Z&&dr<=Z;i++)
    {
        while(j<=Z)
        {
            if(frecv[S[j]-'A']==0)
            {
                if(nr<C)
                    {nr++;frecv[S[j]-'A']++;}
                else
                    break;
            }
            else
            {
                frecv[S[j]-'A']++;
            }
            j++;
        }
        if(dr-st+1<j-i+1)
        {
            dr=j;
            st=i;
        }
        frecv[S[i]-'A']--;
        if(frecv[S[i]-'A']==0)
            nr--;
    }
    fprintf(g,"%d\n",dr-st);
    S[dr]='\0';
    fputs(S+st,g);
    fclose(f);
    fclose(g);
    return 0;
}
