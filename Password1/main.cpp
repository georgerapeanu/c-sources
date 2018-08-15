#include <cstdio>
#include <cstring>
using namespace std;
FILE *f=fopen("password1.in","r");
FILE *g=fopen("password1.out","w");
char A[30000005];
char B[3000005];
int frA[256];
int frB[256];
int N,M;
int top;
char st[3000005];
int main()
{
    fscanf(f,"%s %s",A+1,B+1);
    N=strlen(A+1);N-=(A[N]=='\n');
    M=strlen(B+1);M-=(B[M]=='\n');
    for(int i=1;i<=N;i++)frA[A[i]]++;
    for(int i=1;i<=M;i++)frB[B[i]]++;
    for(int i=1;i<=N;i++)
    {
        if(frB[A[i]])
        {
            while(top&&A[i]<st[top]&&frA[st[top]]>frB[st[top]])
            {
                frB[st[top]]++;
                top--;
            }
            st[++top]=A[i];
            frB[A[i]]--;
        }
        frA[A[i]]--;
    }
    if(top==M)fputs(st+1,g);
    else fprintf(g,"impossible");
    fclose(f);
    fclose(g);
    return 0;
}
