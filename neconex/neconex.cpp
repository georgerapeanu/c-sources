#include <cstdio>

using namespace std;

FILE *f = fopen("neconex.in","r");
FILE *g = fopen("neconex.out","w");

int t;

int main(){

    fscanf(f,"%d",&t);
    while(t--){
        int n,m;
        
        fscanf(f,"%d %d",&n,&m);

        for(int i = 1;i <= m;i++){
            int a,b;
            fscanf(f,"%d %d",&a,&b);
        }

        fprintf(g,"%d\n",((n * (n - 1) / 2) - m) & 1);
    }

    fclose(f);
    fclose(g);

    return 0;
}
///cred ca merge deoarce
///1.daca n e impar,atunci la final vor fi 2 componente,una para alta impara
///deci vor fi maxim n * (n - 1) / 2 - par * impar - m mutari pana atunci,si modulo 2 e doar n * (n - 1) / 2 - m
///2.n e par
///acuma se poate termina fie in par par,fie impar impar
///daca incepi cu nr de mutari par,putem presupune ca asta e stare de pierdere. atunci vei dori sa unesti 2 impare,ca sa adaugi un nr de mutari i * i -1 par de mutari,si si oponentul sa fie in aceasti stare de pierdere
///dar acuma in mod garantat avem cel putin una para,pe care o putem forta pana la final
///daca primul este in stare de pierdere ar trebui atunci sa incerce sa scape de pare,dar asa ramane intr-o stare para(unind par cu impar),iar oponentul impar poate doar sa lege o muchie random dintr-o componenta. astfel vei ramane primul vara mutari si vei fi fortat sa legi 2 impare,ceea ce ii va conveni la adversar si o va forta pe aia pana la final
///sunt cateva exceptii, dar cumva toate au o strategie care sa se potriveasca cu rezultatul
