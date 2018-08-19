#include <fstream>
#include <stdlib.h>
#include <math.h>
using namespace std;
ifstream fin("cladiri2.in");
ofstream fout("cladiri2.out");

int main()
{
    int i,n,k,sir[20],j;
    int max_inaltime=0,max_turn=0,apare=0,sunt_identice;
    int nr_Crina,s=0,aux;
    int nr_bilete_identice=0;

fin>>n;
for(i=1;i<=n;i++)
{
    fin>>nr_Crina;aux=nr_Crina;
    k=0;max_inaltime=0;
    while(nr_Crina)
    { k++; sir[k]=nr_Crina%10;nr_Crina=nr_Crina/10;
      if (max_inaltime<sir[k])
      max_inaltime=sir[k];
    }
     if (max_inaltime>max_turn)
     {max_turn=max_inaltime; apare=1;}
     else
      if (max_inaltime==max_turn)
        apare++;

    sunt_identice=1;
    for(j=1;j<=k/2;j++)
    if (sir[j]!=sir[k-j+1])
       sunt_identice=0;
    if(sunt_identice) nr_bilete_identice++;
    for(j=1;j<=k/2;j++)
     s=s+labs(sir[j]-sir[k-j+1]);
}
fin.close();
fout<<max_turn<<" "<<apare<<endl<<nr_bilete_identice<<endl<<s<<endl;


    return 0;
}

