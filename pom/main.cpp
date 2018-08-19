#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stack>
using namespace std;
FILE *f=fopen("pom.in","r");
FILE *g=fopen("pom.out","w");
stack <int> S;
int N,L,cnt;
int M[27],i,j,val;
char c;
char C[100005];
char rez[100005];
bool ok;
bool used[30];
bool parantezare()
{
    int i=1;
    bool ofost;
    for(i=1;i<=L;i++)
    {
        if(C[i]=='(')
            {
                S.push(i);
                ofost=1;
                if(C[i-1]=='('||C[i-1]==','||C[i+1]==','||C[i+1]==')'||C[i+1]=='('||C[i-1]==')')
                    return 0;
            }
        else if(C[i]==')')
        {
            if(S.empty())
                return 0;
            S.pop();
        }
        if(S.empty()&&i<L&&ofost)
            return 0;
    }
    if(!S.empty())
        return 0;
    return 1;
}
void dfs(char c)
{
    int nrcomp=0;
    while(C[i]!=')'&&ok==1&&i<=L)
    {
        if(C[i]>='a'&&C[i]<='z'&&C[i+1]!='('&&ok==1)
                if(M[C[i]-'a']==0)
                    rez[cnt++]=C[i];
                else
                    ok=0;
        else if(C[i]=='('&&ok==1)
            {
                i++;
                dfs(C[i-2]);
            }
        else if(C[i]==','&&ok==1)
           nrcomp++;
        else if(!(C[i]>='a'&&C[i]<='z'))
            ok=0;
        i++;
    }
    if(nrcomp+1!=M[c-'a']&&i<=L)
        {ok=0;}
    rez[cnt++]=c;
}
int main()
{
    fscanf(f,"%d\n",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%c",&c);
        fscanf(f,"%d\n",&val);
        if(c>='a'&&c<='z')
        {
            M[c-'a']=val;
            used[c-'a']=1;
        }
    }
    if(fgets(C+1,100005,f)==NULL)
         {
        fprintf(g,"-1\n");
        return 0;
    }
    L=strlen(C+1)-1;
    for(i=1;i<=L;i++)
    {
        while(C[i]==' ')
        {
            for(j=i;j<L;j++)
                C[j]=C[j+1];
            C[L]='\0';
            L--;
        }
    }
    if(!parantezare())
    {
        fprintf(g,"-1\n");
        return 0;
    }
    i=1;
    ok=1;
    dfs(C[i]);
    if(C[2]=='(')
        rez[cnt-1]='\0';
    for(i=1;i<=cnt;i++)
        used[rez[i]-'a']=0;
    for(i=1;i<=cnt;i++)
    if(used[rez[i]-'a'])
    {
        fprintf(g,"-1\n");
        return 0;
    }
    if(ok==0)
    {
        fprintf(g,"-1\n");
        return 0;
    }
    fputs(rez,g);
    fputc('\n',g);
    fclose(f);
    fclose(g);
    return 0;
}
