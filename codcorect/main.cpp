#include <fstream>
#include <iostream>
using namespace std;
ifstream f("codcorect.in");
ofstream g("codcorect.out");
unsigned long long int n,i,ctr,fctr,j;
char s[181],tmp;
int main()
{
      f>>n;
      f>>s[0];
      f.getline(s+1,181);
      for(i=1;i<=n;i++)
      {
          fctr=ctr;
            while(s[ctr]>='0'&&s[ctr]<='9')ctr++;
            if((ctr-fctr)%2==1)
            {
                if(s[fctr]<s[ctr-1])
                {
                    tmp=s[fctr];
                    s[fctr]=s[ctr-1];
                    s[ctr-1]=tmp;
                }
            }
            for(j=fctr;j<=ctr-1;j++)
            g<<(int(s[j])-'0');
            g<<" ";
            ctr++;
        }
      f.close();g.close();
        return 0;
}
