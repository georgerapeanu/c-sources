#include <fstream>
#include <cstdio>
#include <vector>
using namespace std;
FILE *f=fopen("text4.in","r");
ofstream g("text4.out");
int Max;
char C[1005];
vector<string> cuvinte;
void alineaza()
{
    int i=1;
    cuvinte.clear();
    string a;a.clear();
    for(int i=1;C[i]!='\n';i++)
    {
        if(C[i]==' ')
        {
            if(!a.empty()) cuvinte.push_back(a);
            a.clear();continue;
        }
        a+=C[i];
    }
    if(!a.empty()) cuvinte.push_back(a);
    i=0;
    int nrchar=0,nrcuv=0;
    int N=cuvinte.size();
    int nrspatii,nrsup;
    while(i<N)
    {
        while(i<N&&nrchar+cuvinte[i].size()+nrcuv<=Max)
        {
            nrchar+=cuvinte[i].size();
            i++;
            nrcuv++;
        }
        if(i==N) break;
        nrspatii=(Max-nrchar)/(nrcuv-1);
        nrsup=(Max-nrchar)%(nrcuv-1);
        for(int j=i-nrcuv;j<i-1;j++)
        {
            g<<cuvinte[j];
            for(int k=0;k<nrspatii;k++) g<<" ";
            if(j-i+nrcuv<nrsup)
                g<<" ";
        }
        g<<cuvinte[i-1]<<"\n";
        nrchar=nrcuv=0;
    }
    if(nrcuv)
    {
        for(int j=i-nrcuv;j<=i-1;j++)
        {
            g<<cuvinte[j];
            g<<" ";
        }
        g<<"\n";
    }
}
int main()
{
    fscanf(f,"%d\n",&Max);
    while(fgets(C+1,1005,f)!=NULL)
    {
        alineaza();
    }
    fclose(f);
    g.close();
    return 0;
}
