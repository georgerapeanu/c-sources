#include<fstream>
#include<cstring>
#include<iostream>
using namespace std;
ifstream f("alfabetar.in");
ofstream g("alfabetar.out");
char c[200][200],v[2100];
int n,i,nrmax,j,k,o;
int main()
{
    f>>n;
    for(i=0;i<=n;i++)
    {
        f.getline(c[i],200);
        if(strlen(c[i])>nrmax)
            nrmax=strlen(c[i]);
    }
    nrmax--;
    for(j=nrmax;j>=0;j--)
    {
        for(i=1;i<=n;i++)
        {
            if('a'<=c[i][j]&&c[i][j]<='z')
            {
                v[o]=c[i][j];
                o++;
            }
            else if('A'<=c[i][j]&&c[i][j]<='Z')
            {
                v[o]=c[i][j];
                o++;
            }
            else if('0'<=c[i][j]&&c[i][j]<='9')
            {
                v[o]=c[i][j];
                o++;
            }
            else
                {
                    v[o]=' ';
                    o++;
                }
        }
        v[o]='\n';
        o++;
    }
    g<<v;
    f.close();g.close();
    return 0;
}
