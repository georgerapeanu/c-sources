#include <iostream>
#include <cstring>
using namespace std;
char S[1000005];
char C[1000005];
char rez[1000005];
int i,j,l,u;
int N,M;
int main()
{
    while(cin.getline(S,1000005))
    {
        M=strlen(S);
        i=0;
        j=0;
        l=0;
        u=0;
        while(i<M)
        {
            for(j=u;C[j]!='\0';j++)
            {
                if(C[j]==S[i])
                {
                    for(int k=u;k<=j;k++)
                        rez[l++]=C[k];
                    i++;
                    u=j+1;
                }
            }
            rez[l++]=S[i];
            i++;
        }
        for(i=u;C[i]!='\0';i++)
            rez[l++]=C[i];
        for(i=0;i<l;i++)
            C[i]=rez[i];
    }
    cout<<C;
    return 0;
}
