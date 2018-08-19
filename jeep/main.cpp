#include <iostream>
#include <cmath>
using namespace std;
long long N,M,a;
double d,o,w;
/// a-popasul curent
/// d-distanta de la ultimul popas laurmatorul
/// w-distanta de la inceput pana la ultimul popas
/// se tot adauga popase pana cand putem ajunge la N
///la final ne intereseaza doar distanta dintre ultimul si N
///daca stai sa te gandesti,noi am inceput popasul de la coada la inceput,deci primul popas va fi la d distanta
///si o parcurgem de 2*a-1 ori
int main()
{
    cin>>N>>M;
    do
    {
        a++;
        d=((double)M)/((a<<1)-1);
        if(w+d>=N)
            break;
        w+=d;
        o+=M;
    }
    while(true);
    d=N-w;
    o+=d*((a<<1)-1);
    if(o!=(long long)o)
        cout<<(long long)o + 1;
    else
        cout << (long long)o;
    return 0;
}
