#include <fstream>
using namespace std;
ifstream f("2am.in");
ofstream g("2am.out");
char v[100],ok=1;
int main()
{
//dacaonly1
     f>>v;
     for(i=0;i<strlen(v);i++)
     {
         if((v[i]>='a'&&v[i]<='z')||(v[i]>='0'&&v[i]<='9')||(v[i]=='B'||v[i]=='D'||v[i]=='I'||v[i]=='P'||v[i]=='S'||v[i]=='X'||v[i]=='+'||v[i]=='-'||v[i]=='['||v[i]==']'))
         {
             continue;
         }
         else
         {
             ok=0;g<<"ERROR";break;
         }
         if(v[i]=='[')
         {
             if(v[i+1]==)
         }
     }
    return 0;
}
