#include <cstdio>
using namespace std;
FILE *f=fopen("calandrinon.in","r");
FILE *g=fopen("calandrinon.out","w");
int N;
char C[1000005];
char rez[34],ind;
int M[30];
bool u[30];
int tmp[30];
int main()
{
    fscanf(f,"%d\n",&N);
    fgets(C+1,1000005,f);
    for(int i=1;i<=N;i++)
        M[C[i]-'a']++;
    C[0]='z'+2;
    for(int i=1;i<=N;i++)
    {
        int ri=0,ni=i;
        for(int j=0;j<30;j++) tmp[j]=M[j];
        while(ni<=N)
        {
            if(u[C[ni]-'a']) {ni++;continue;}
            if(C[ri]>C[ni]) ri=ni;
            tmp[C[ni]-'a']--;
            if(!tmp[C[ni]-'a']) break;
            ni++;
        }
        if(!ri) break;
        while(i<=ri)
        {
            M[C[i]-'a']--;
            i++;
        }
        rez[++ind]=C[ri];
        u[C[ri]-'a']=1;
        i--;
    }
    fputs(rez+1,g);
    fclose(f);
    fclose(g);
    return 0;
}
