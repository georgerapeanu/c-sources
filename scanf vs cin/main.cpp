#include <fstream>
using namespace std;
ifstream f("test.in");
long long val;
int N;
int main()
{
    f>>N;
    for(int i=1;i<=N;i++)
    {
        f>>val;
    }
    f.close();
    return 0;
}
/*
#include <cstdio>
using namespace std;
FILE *f=fopen("test.in","r");
long long val;
int N;
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%lld",&val);
    }
    fclose(f);
    return 0;
}
*/
