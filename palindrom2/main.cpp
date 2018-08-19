#include <cstdio>
#include <cstring>
using namespace std;
FILE *f=fopen("palindrom2.in","r");
FILE *g=fopen("palindrom2.out","w");
char C[2005];
int ind;
int main()
{
    int N;
    fgets(C+1,2005,f);
    N=strlen(C+1);
    N=N-(C[N]=='\n');
    for(int i=0;i<=N;i++)
    {
        int st=i+1,dr=N;
        while(st<dr&&C[st]==C[dr]){st++;dr--;}
        if(st>=dr)
        {
            ind=i;break;
        }
    }
    for(int i=ind;i;i--)
        C[++N]=C[i];
    fputs(C+1,g);
    fclose(f);
    fclose(g);
    return 0;
}
