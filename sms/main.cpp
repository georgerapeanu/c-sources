#include <cstdio>
using namespace std;
FILE *f=fopen("sms.in","r");
FILE *g=fopen("sms.out","w");
int cod[]={2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9},last,mid,st,dr,nr,j;
char dic[105][105];
int val,i,N,M,cuv[105];
char rez[105];
int comp(char c[])
{
    int i=0;
    while(cod[c[i]-'A']==cuv[i+1]&&i+1<=cuv[0])
        i++;
    if(c[i]=='\n'&&cuv[i+1]==0)
    return 0;
    if(cod[c[i]-'A']>cuv[i+1])
        return 1;
    return -1;
}
int main()
{
    fscanf(f,"%d\n",&M);
    for(i=1;i<=M;i++)
        fgets(dic[i],105,f);
    fscanf(f,"%d",&N);
    for(i=1;i<=N+1;i++)
    {
        if(i!=N+1)
        fscanf(f,"%d",&val);
        if(val==1||i==N+1)
        {
            st=1;dr=M;
            last=-1;
            while(st<=dr)
            {
                mid=(st+dr)/2;
                nr=comp(dic[mid]);
                if(nr==0)
                {
                    last=mid;
                    dr=mid-1;
                }
                else if(nr==1)
                 dr=mid-1;
                else
                 st=mid+1;
            }
            if(last!=-1)
                {j=0;while(dic[last][j]!='\n'){fputc(dic[last][j],g);j++;}}
            else
            {
                for(j=1;j<=cuv[0];j++)
                    fputc('*',g);
            }
            fputc(' ',g);
            cuv[0]=0;
        }
        else
            cuv[++cuv[0]]=val;
    }
    fclose(f);
    fclose(g);
    return 0;
}
