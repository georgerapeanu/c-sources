#include <iostream>
#include <algorithm>
using namespace std;
long long m[40],st,dr;
/*
sa o luam pe rand
prima observaite:
definim traversarea unui subarbore de nivel i,ca mergand din cel mai mic nod din subarborele din stanga si cel mai mare din subarborele din dreapta
 +-----+4+----+
  +            +
++2++        ++6++
+   +        +   +
1   3        5   7
adica m[3]-costul minim de a merge din 1 in 7
este clar ca m[nivel]=2*m[nivel-1]+2*(i-1)
        are 2 subarbori de nivel -1   drumul dinte ultima val din primul si prima din al doilea este de doua ori nivelul -1
adica,aici cost(3,5)=2*1(nivelele se numeroteaza de la 0)
daca nivel =0,nu se ia in considerare 2*(i-1)
vrem sa parcurgem de la c la d
vrem sa mergem cat mai sus din c,ca sa eliminam mai multe valori de odata
adica,daca destinatia e 5 si plecam din 1,vrem sa mergem in 2 si apoi in 4,neavand rost sa mergem in 3,apoi 4
se observa ca formula primului stramos mai mare decat nodul nostru este nodcurent+2^(nivel)
formula este asta pt ca gandestete:suntem in nodul c,subarborele din stanga e vizitat complet,cel din dreapta de loc
in dreapta sunt 2^(nivel-1)-1 noduri
si cel de deasupra ta este 2^(nivel-1)-1+1
aceasta merge si daca de exemplu nodul este 7,deoare urmatoarea valoare nevizitata si care ne intereseaza este 8
deci stim stramosul la care am vrea sa ajungem in pasul urmator
noi ne aflam in subarborele stang lui,deoarece avem valoarea mai mica

definim functia cost(nr) costul de a ajunge dintr-un nod la nivelul 0 din subarborele nr la nr,care se observa ca e nivel-1(daca nivel>0)


daca d>=acel stramos,putem exclude linistiti subarborele din dreapta noastra(noi am vizitat nodurile pana la c,adica fara subarborele din dreapta lui c,acesta avand val mai mari)
deci cost=cost(cat am avut pana acum)+m[nivelc-1](rezolvam subarborele din dr)+cost(c)(trebuie sa ajungem din c in primul nod al subarborelui dr,distanta fiind egala cu cea de la nod la c)+cost(stramos)(dupa ce terminam,vrem sa ajungem in stramos
daca d<acel stramos,vrem sa pergem in c+1,adica primul nod al subarborelui drept
cost=cost+cost(c)(cat avem de la c la nodul c+1,aflat pe nivelul 0)
daca nu ma crezi,fa niste teste pe hartie si o sa iti dai seama
si faci algoritmul cat timp c!=d
*/
long long lvl(long long nr)
{
    long long i=0;
    while(nr%2==0)
    {
        i++;
        nr/=2;
    }
    return i;
}
long long cost(long long nr)
{
    long long c=lvl(nr);
    if(c>1)
        return c-1;
    return 0;
}
long long sol(long long c,long long d)
{
    long long stramosmaimare=0,nivel=lvl(c),costdetraversaresubarbore=0,rez=0;
    while(c!=d)
    {
        nivel=lvl(c);
        costdetraversaresubarbore=0;
        if(nivel>0)
            costdetraversaresubarbore=m[nivel-1];
        stramosmaimare=c+(1<<nivel);
        if(stramosmaimare<=d)
        {
            rez+=costdetraversaresubarbore+cost(c)+cost(stramosmaimare);
            c=stramosmaimare;
        }
        else
        {
            rez+=cost(c);
            c++;
        }
    }
    return rez;
}
int main()
{
    for(int i=1;i<=35;i++)
        m[i]=2*m[i-1]+2*(i-1);
    cin>>st>>dr;
    if(st>dr)
        swap(st,dr);
    cout<<sol(st,dr);
    return 0;
}
