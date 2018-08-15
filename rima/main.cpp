#include <cstdio>
#include <cstring>
using namespace std;
FILE *f=fopen("rima.in","r");
FILE *g=fopen("rima.out","w");
int N,i,j;
char C[5][55];
int V[5];
char low(char c)
{
    if(c>='A'&&c<='Z')
        return c-'A'+'a';
    return c;
}
bool isvowel(char c)
{
    c=low(c);
    if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u')
        return 1;
    return 0;
}
int mycmp(char A[],char B[])
{
    int i;
    i=0;
    while(low(A[i])==low(B[i])&&A[i]!='\n')
        i++;
    if(A[i]=='\n')
        return 0;
    else
    {
        if(A[i]<B[i])
            return -1;
        else
            return 1;
    }
}
int main()
{
    fscanf(f,"%d\n",&N);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=4;j++)
            fgets(C[j]+1,55,f);
        for(j=1;j<=4;j++)
        {
            V[j]=strlen(C[j]+1);
            while(!isvowel(C[j][V[j]])&&V[j]&&C[j][V[j]-1]!=' ')
                V[j]--;
            if(V[j]==0)
                V[j]++;
        }
        mycmp(C[2]+V[2],C[3]+V[3]);
        if(mycmp(C[1]+V[1],C[2]+V[2])==0&&mycmp(C[2]+V[2],C[3]+V[3])==0&&mycmp(C[3]+V[3],C[4]+V[4])==0)
            fprintf(g,"perfecta\n");
        else if(mycmp(C[1]+V[1],C[2]+V[2])==0&&mycmp(C[3]+V[3],C[4]+V[4])==0)
            fprintf(g,"uniforma\n");
        else if(mycmp(C[1]+V[1],C[3]+V[3])==0&&mycmp(C[2]+V[2],C[4]+V[4])==0)
            fprintf(g,"incrucisata\n");
        else if(mycmp(C[1]+V[1],C[4]+V[4])==0&&mycmp(C[2]+V[2],C[3]+V[3])==0)
            fprintf(g,"imbricata\n");
        else
            fprintf(g,"alba\n");
    }
    fclose(f);
    fclose(g);
    return 0;
}
