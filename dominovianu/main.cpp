#include <cstdio>
#include <deque>
using namespace std;
FILE *f=fopen("domino.in","r");
FILE *g=fopen("domino.out","w");
int dq[10005];
bool rotit[10005];
int E,R,e;
int N,i;
int a,b,j;
int nr;
bool ro;
///rotit[i]=1 daca elementul i din deque a trebuit rotit
int main()
{
    fscanf(f,"%d %d %d",&N,&R,&E);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d %d",&a,&b);
        if(a*10+b>=b*10+a)///daca numarul ar fi mai bun rotit incercam sa il rotim
        {
            nr=a*10+b;
            ro=0;
        }
        else
        {
            nr=b*10+a;
            ro=1;
        }
        j=dq[0];
        e=E;
        while(dq[j]<nr&&j>0&&e)///numarul mai bun vedem cat de sus in deque poate ajunge
        {
            R+=rotit[j];///recuperam rotirile
            j--;
            e--;///avem mai putine eliminari
        }
        if(R>0&&ro)///daca e mai bun rotit
        {
            R--;///il putem roti,deci o sa o facem
            E=e;///facem eliminariile pentru al duce cat mai sus in deque
            dq[j+1]=nr;
            rotit[j+1]=1;
            dq[0]=j+1;
        }
        else if(ro==0)
        {
            E=e;///daca nu mai avem rotiri,dar nici nu am avut nevoie sa il rotim,facem eliminarile si il inseram
            dq[j+1]=nr;
            dq[0]=j+1;
            rotit[dq[0]]=0;
            if(rotit[dq[0]-1]&&dq[dq[0]]==dq[dq[0]-1])///daca cel de dinaintea lui a fost rotit,si asta e egal cu cel vechi,e ca si cum pe cel de dinainte l-am fi primit asa,si pe cel nou l-am rotit
            {
                rotit[dq[0]]=1;
                rotit[dq[0]-1]=0;
            }///asta evita cazurile cand ramanem fare eliminari,iar numerele de sus au fost rotite
            ///mai exact cazul
            ///3 1 1
            ///2 4
            ///4 2
            ///1 9
        }
        else///daca nu il putem roti,reluam de la inceput algoritmul de al duce cat mai sus in deque
        {
            nr=a*10+b;
            j=dq[0];
            e=E;
            while(dq[j]<nr&&j>0&&e)
            {
                R+=rotit[j];
                j--;
                e--;
            }
            dq[j+1]=nr;
            dq[0]=j+1;
            rotit[dq[0]]=0;
             if(rotit[dq[0]-1]&&dq[dq[0]]==dq[dq[0]-1])///aceasi chestie ca si if-ul anterior
            {
                rotit[dq[0]]=1;
                rotit[dq[0]-1]=0;
            }
            E=e;
        }
    }
    while(E)///daca au mai ramas eliminari,le facem pe ultimele elemente
    {dq[0]--;E--;}
    if(dq[0]==0)///daca nu mai avem domino-uri,afisam 0
        fputc('0',g);
    for(i=1;i<=dq[0];i++)///altfel afisam deque-ul
        fprintf(g,"%d",dq[i]);
    fclose(f);
    fclose(g);
    return 0;
}
