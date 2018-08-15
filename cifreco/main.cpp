/*#include <cstdio>
using namespace std;
FILE *f=fopen("cifreco.in","r");
FILE *g=fopen("cifreco.out","w");
long long N,x,y,minim,i,sol,c,w,cf;
int main()
{
    fscanf(f,"%lld%lld%lld",&N,&x,&y);
    for(i=1;i<=N-1;i++)
        minim=minim*10+1;
    minim=minim*10+9;
    for(i=(x-minim)/9;i<=(y-minim)/9;i++)
    {
        sol++;
        w=i;
        c=0;
        while(w%10==8) {w/=10;c++;}
        if(i%10==8&&w==0)
        {
            i=0;
            for(w=1;w<=c+1;w++)
                i=i*10+1;
            i--;
        }
        else if(i%10==8)
        {
            cf=(i/10)%10;
            i=0;
            for(w=1;w<=c;w++)
                i=i*10+cf;
            i--;
        }
    }
    fprintf(g,"%lld",sol);
    fclose(f);
    fclose(g);
}*/
// varianta cu multiplii de 9
#include <fstream>

using namespace std;

ifstream f("cifreco.in");
ofstream g("cifreco.out");

int main()
{
long long i,n,w,s,x,y,min,sol=0;;
int k,c,ucw;
f>>n>>x>>y;

min=1;
for(i=1;i<n-1;i++)
	min=min*10+1;
min=min*10+9;

for(i=(x-min)/9;i<=(y-min)/9;i++)
	{

	sol++;

	// cand apare un multiplu care se termina cu 8 determin succesorul dupa algoritmul de mai jos
	// 8->11,18->22,28->33,...,88->111,118->222,etc

	w=i;c=0;
	while (w%10==8) {w/=10;c++;}
	if (w!=i)
		{
		if (w==0)
			for(s=1,k=1;k<=c;k++) s=s*10+1;
			 else
			 {
			 ucw=w%10+1;w++;
			 for(k=1;k<=c;k++) w=w*10+ucw;
			 s=w;
			 }
		i=--s;
		}
	}
g<<sol<<"\n";
f.close();
g.close();

return 0;
}
