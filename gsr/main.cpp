#include <cstdio>
#include <unordered_map>
#include <cstring>
using namespace std;
FILE *f=fopen("gsr.in","r");
FILE *g=fopen("gsr.out","w");
long long B;
long long K;
long long rez;
long long val=1;
char c;
unordered_map<char,int> M;
int N,i;
int main()
{
    fscanf(f,"%lld %lld\n",&B,&K);
    N=1;
      M['0']=0;
    M['1']=1;
    M['2']=2;
    M['3']=3;
    M['4']=4;
    M['5']=5;
    M['6']=6;
    M['7']=7;
    M['8']=8;
    M['9']=9;
    M['A']=10;
    M['B']=11;
    M['C']=12;
    M['D']=13;
    M['E']=14;
    M['F']=15;
    while(fscanf(f,"%c",&c)!=EOF&&c!='\n')
    {
        rez=((rez*B)%K+M[c])%K;
    }
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
